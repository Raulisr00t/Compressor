# LZ77 Compressor & Decompressor (C)

This project is a simple implementation of the **LZ77 compression algorithm** in pure C, featuring both a `compressor` and a matching `decompressor`. It reads text files, compresses repeated patterns into compact tokens, and can fully reconstruct the original file.

---

## 🔧 Features

- 📦 File-based compression using LZ77-style sliding window
- 🔁 Full decompression support to reconstruct original files
- 🧪 Simple and clean C code for educational purposes
- 🖥️ Command-line interface for usage flexibility
- 💡 Binary-safe I/O with support for repeated patterns

---

## 📁 Files

| File             | Description                           |
|------------------|---------------------------------------|
| `Compressor.c`   | Compresses `.txt` into `.lz77` format |
| `Decompressor.c` | Decompresses `.lz77` back to `.txt`   |
| `Makefile`       | Builds both executables               |
| `test.txt`       | Sample input for testing              |
| `output.lz77`    | Compressed binary output              |
| `recovered.txt`  | Output after decompression            |

---

## 🚀 Build

### Using Make (Recommended)

```powershell
make
```

This will produce:

compressor.exe
decompressor.exe

### Manual Compilation (Windows)

```powershell
gcc Compressor.c -o compressor.exe
gcc Decompressor.c -o decompressor.exe
```

## 🧪 Usage
Compress a File

```powershell
Compressor.exe test.txt output.lz77
```

Decompress a File

```powershell
Decompressor.exe output.lz77 recovered.txt
```

## Format Description

Each compressed token is 5 bytes:
offset (2 bytes)
length (2 bytes)
next character (1 byte)

When no match is found, offset/length are 0, and only the next char is stored.

## 📚 Notes
This implementation is for educational and demonstration purposes.
For small files or random data, compression may result in larger size.
Best results come from files with high redundancy or repeated patterns.

# 🧑‍💻 Author

Created by Raulisr00t — feel free to fork, improve, or ask questions.
