#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 256

// ---------------- NODE ----------------
typedef struct Node {
    unsigned char byte;
    int freq;
    struct Node *left, *right;
} Node;

// ---------------- MIN HEAP ----------------
typedef struct {
    int size;
    int capacity;
    Node **array;
} MinHeap;

Node* newNode(unsigned char byte, int freq) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->byte = byte;
    temp->freq = freq;
    temp->left = temp->right = NULL;
    return temp;
}

MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->array = (Node**)malloc(capacity * sizeof(Node*));
    return heap;
}

void swapNode(Node** a, Node** b) {
    Node* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->array[left]->freq < heap->array[smallest]->freq)
        smallest = left;

    if (right < heap->size && heap->array[right]->freq < heap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapNode(&heap->array[smallest], &heap->array[idx]);
        minHeapify(heap, smallest);
    }
}

Node* extractMin(MinHeap* heap) {
    Node* temp = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    minHeapify(heap, 0);
    return temp;
}

void insertMinHeap(MinHeap* heap, Node* node) {
    heap->size++;
    int i = heap->size - 1;

    while (i && node->freq < heap->array[(i - 1) / 2]->freq) {
        heap->array[i] = heap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap->array[i] = node;
}

// ---------------- BUILD TREE ----------------
Node* buildHuffmanTree(unsigned char* data, int size) {
    int freq[256] = {0};

    for (int i = 0; i < size; i++)
        freq[data[i]]++;

    MinHeap* heap = createMinHeap(256);

    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0)
            insertMinHeap(heap, newNode(i, freq[i]));
    }

    while (heap->size > 1) {
        Node* left = extractMin(heap);
        Node* right = extractMin(heap);

        Node* top = newNode(0, left->freq + right->freq);
        top->left = left;
        top->right = right;

        insertMinHeap(heap, top);
    }

    return extractMin(heap);
}

// ---------------- GENERATE CODES ----------------
void generateCodes(Node* root, char* code, int top, char codes[256][256]) {
    if (root->left) {
        code[top] = '0';
        generateCodes(root->left, code, top + 1, codes);
    }
    if (root->right) {
        code[top] = '1';
        generateCodes(root->right, code, top + 1, codes);
    }

    if (!root->left && !root->right) {
        code[top] = '\0';
        strcpy(codes[root->byte], code);
    }
}

// ---------------- XOR ----------------
void xorData(unsigned char* data, int size, unsigned char key) {
    for (int i = 0; i < size; i++)
        data[i] ^= key;
}

// ---------------- COMPRESS ----------------
void compressFile(const char* input, const char* output, unsigned char key) {
    FILE* f = fopen(input, "rb");
    if (!f) return;

    fseek(f, 0, SEEK_END);
    int size = ftell(f);
    rewind(f);

    unsigned char* data = (unsigned char*)malloc(size);
    fread(data, 1, size, f);
    fclose(f);

    Node* root = buildHuffmanTree(data, size);

    char codes[256][256] = {{0}};
    char buffer[256];
    generateCodes(root, buffer, 0, codes);

    FILE* out = fopen(output, "wb");

    // write metadata
    FILE* meta = fopen("meta.txt", "w");
    for (int i = 0; i < 256; i++) {
        if (strlen(codes[i]) > 0)
            fprintf(meta, "%d %s\n", i, codes[i]);
    }
    fclose(meta);

    // encode
    char bitstream[1000000] = {0};
    for (int i = 0; i < size; i++)
        strcat(bitstream, codes[data[i]]);

    int bitlen = strlen(bitstream);
    int byteCount = (bitlen + 7) / 8;

    unsigned char* compressed = (unsigned char*)calloc(byteCount, 1);

    for (int i = 0; i < bitlen; i++) {
        if (bitstream[i] == '1')
            compressed[i / 8] |= (1 << (7 - (i % 8)));
    }

    xorData(compressed, byteCount, key);

    fwrite(compressed, 1, byteCount, out);
    fclose(out);

    printf("Compression + Encryption Done\n");
}

// ---------------- MAIN ----------------
int main(int argc, char* argv[]) {
    if (argc < 5) {
        printf("Usage:\n");
        printf("Compress: %s c input output key\n", argv[0]);
        return 1;
    }

    char mode = argv[1][0];
    unsigned char key = atoi(argv[4]);

    if (mode == 'c') {
        compressFile(argv[2], argv[3], key);
    }

    return 0;
}