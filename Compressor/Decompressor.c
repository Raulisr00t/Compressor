#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define INITIAL_BUFFER_SIZE 4096

typedef struct {
    uint16_t offset;
    uint16_t length;
    char next;
} Token;

void Decompress_File(FILE* in, const char* outputPath) {
    FILE* out = fopen(outputPath, "wb");
    if (!out) {
        perror("Failed to open output file");
        return;
    }

    char* buffer = (char*)malloc(INITIAL_BUFFER_SIZE);
    int capacity = INITIAL_BUFFER_SIZE;
    int size = 0;

    if (!buffer) {
        perror("Memory allocation failed");
        fclose(out);
        return;
    }

    Token token;

    while (fread(&token, sizeof(Token), 1, in) == 1) {
        if (size + token.length + 1 > capacity) {
            capacity *= 2;
            buffer = (char*)realloc(buffer, capacity);
            if (!buffer) {
                perror("Reallocation failed");
                fclose(out);
                return;
            }
        }

        for (int i = 0; i < token.length; ++i) {
            buffer[size] = buffer[size - token.offset];
            size++;
        }

        buffer[size++] = token.next;
    }

    fwrite(buffer, 1, size, out);
    fclose(out);
    free(buffer);
}

int main(int argc, const char* argv[]) {
    if (argc != 3) {
        printf("Usage: Decompressor.exe <file.lz77> <output.txt>\n");
        return 1;
    }

    const char* inputPath = argv[1];
    const char* outputPath = argv[2];

    FILE* in = fopen(inputPath, "rb");
    if (!in) {
        perror("Failed to open compressed file");
        return 1;
    }

    printf("[+] Decompressing: %s → %s\n", inputPath, outputPath);
    Decompress_File(in, outputPath);
    fclose(in);
    printf("[+] Decompression completed.\n");

    return 0;
}
