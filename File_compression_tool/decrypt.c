#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------------- NODE ----------------
typedef struct Node {
    int byte;
    struct Node *left, *right;
} Node;

Node* newNode() {
    Node* node = (Node*)malloc(sizeof(Node));
    node->byte = -1;
    node->left = node->right = NULL;
    return node;
}

// ---------------- BUILD TREE FROM META ----------------
Node* rebuildTree(const char* meta_file) {
    FILE* f = fopen(meta_file, "r");
    if (!f) {
        printf("Meta file not found\n");
        exit(1);
    }

    Node* root = newNode();

    int byte;
    char code[256];

    while (fscanf(f, "%d %s", &byte, code) != EOF) {
        Node* curr = root;

        for (int i = 0; code[i]; i++) {
            if (code[i] == '0') {
                if (!curr->left)
                    curr->left = newNode();
                curr = curr->left;
            } else {
                if (!curr->right)
                    curr->right = newNode();
                curr = curr->right;
            }
        }
        curr->byte = byte;
    }

    fclose(f);
    return root;
}

// ---------------- XOR ----------------
void xorData(unsigned char* data, int size, unsigned char key) {
    for (int i = 0; i < size; i++)
        data[i] ^= key;
}

// ---------------- DECOMPRESS ----------------
void decompressFile(const char* input, const char* output, const char* meta, unsigned char key) {
    FILE* f = fopen(input, "rb");
    if (!f) {
        printf("Encrypted file not found\n");
        return;
    }

    fseek(f, 0, SEEK_END);
    int size = ftell(f);
    rewind(f);

    unsigned char* data = (unsigned char*)malloc(size);
    fread(data, 1, size, f);
    fclose(f);

    // decrypt
    xorData(data, size, key);

    Node* root = rebuildTree(meta);

    FILE* out = fopen(output, "wb");

    Node* curr = root;

    for (int i = 0; i < size; i++) {
        for (int bit = 7; bit >= 0; bit--) {
            int b = (data[i] >> bit) & 1;

            if (b == 0)
                curr = curr->left;
            else
                curr = curr->right;

            if (!curr->left && !curr->right) {
                fputc(curr->byte, out);
                curr = root;
            }
        }
    }

    fclose(out);
    printf("Decryption + Decompression Done\n");
}

// ---------------- MAIN ----------------
int main(int argc, char* argv[]) {
    if (argc < 5) {
        printf("Usage:\n");
        printf("Decrypt: %s input output meta key\n", argv[0]);
        return 1;
    }

    unsigned char key = atoi(argv[4]);

    decompressFile(argv[1], argv[2], argv[3], key);

    return 0;
}