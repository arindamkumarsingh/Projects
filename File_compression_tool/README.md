# HuffmanXOR Tool (Compression + Decryption)

## Overview

This project is implemented in the **C programming language** and provides a **single-file workflow** for:

* Compressing data using **Huffman coding**
* Obfuscating it using a simple **XOR operation**
* Storing everything needed for recovery **inside the output file itself**

The compressed file is self-contained, so no external metadata files are required.

---

## Files

```bash id="dotcra"
huffman_xor.c   → Main tool (compress + decompress)
```

After compilation, you’ll use a single executable:

```bash id="w09cfq"
huffman_xor
```

---

## Compilation

```bash id="x9lsvc"
gcc huffman_xor.c -o huffman_xor
```

---

## Usage

### 🔹 Compress + Encrypt

```bash id="pzdhue"
./huffman_xor c input.txt output.hx 123
```

**Arguments:**

* `c` → compress mode
* `input.txt` → input file
* `output.hx` → output file
* `123` → XOR key (0–255)

---

### 🔹 Decrypt + Decompress

```bash id="o0ejn4"
./huffman_xor d output.hx recovered.txt 123
```

**Arguments:**

* `d` → decompress mode
* `output.hx` → compressed file
* `recovered.txt` → output file
* `123` → same XOR key

---

## Output Behavior

After compression:

* A single file (`.hx`) is generated
* It contains:

  * Encoded data
  * Huffman tree information
  * Padding details

After decompression:

* The original file is reconstructed

---

## How It Works

### 🔸 Compression Phase

1. Reads the input file as raw bytes
2. Calculates frequency of each byte
3. Builds a Huffman tree
4. Generates binary codes for each byte
5. Encodes the file into a bitstream
6. Packs bits into bytes
7. Stores:

   * Huffman structure
   * Padding info
   * Encoded data
8. Applies XOR on final byte stream

---

### 🔸 Decompression Phase

1. Reads the `.hx` file
2. Reverses XOR using the key
3. Extracts stored Huffman structure
4. Rebuilds the Huffman tree
5. Removes padding
6. Decodes bitstream back to original bytes

---

## Key Constraints

* The same key must be used for compression and decompression
* Works with any binary file (not just text)

---

## Summary

This tool demonstrates:

* Lossless compression using Huffman coding
* Reversible transformation using XOR
* Self-contained file format design
* Systems-level programming in C

It provides a clean, end-to-end pipeline for compressing and restoring files using a custom implementation.
