#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define WINDOW_SIZE 1024
#define LOOKAHEAD_BUFFER_SIZE 32
#define MIN_MATCH 3

typedef struct {
    uint16_t offset;
    uint16_t length;
    char next;
} Token;

void Compress_File(const char* inputPath, FILE* out) {
    FILE* in = fopen(inputPath, "rb");
    if (!in) {
        perror("Failed to open input file");
        return;
    }

    fseek(in, 0, SEEK_END);
    long size = ftell(in);
    rewind(in);

    char* buffer = (char*)malloc(size + 1);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(in);
        return;
    }

    fread(buffer, 1, size, in);
    buffer[size] = '\0';
    fclose(in);

    int pos = 0;

    while (pos < size) {
        int best_offset = 0;
        int best_length = 0;

        int search_start = (pos - WINDOW_SIZE > 0) ? (pos - WINDOW_SIZE) : 0;

        for (int i = search_start; i < pos; ++i) {
            int length = 0;

            while (length < LOOKAHEAD_BUFFER_SIZE &&
                   pos + length < size &&
                   buffer[i + length] == buffer[pos + length]) {
                length++;
            }

            if (length > best_length) {
                best_length = length;
                best_offset = pos - i;
            }
        }

        Token token;

        if (best_length >= MIN_MATCH) {
            token.offset = best_offset;
            token.length = best_length;
            token.next = buffer[pos + best_length];
            pos += best_length + 1;
        }
        
        else {
            token.offset = 0;
            token.length = 0;
            token.next = buffer[pos];
            pos += 1;
        }

        fwrite(&token, sizeof(Token), 1, out);
    }

    free(buffer);
}

int main(int argc, const char* argv[]) {
    if (argc != 3) {
        printf("Usage: Compressor.exe <input.txt> <output.lz77>\n");
        return 1;
    }

    const char* inputPath = argv[1];
    const char* outputPath = argv[2];

    FILE* out = fopen(outputPath, "wb");

    if (!out) {
        perror("Failed to open output file");
        return 1;
    }

    printf("[+] Compressing: %s → %s\n", inputPath, outputPath);

    Compress_File(inputPath, out);

    fclose(out);

    printf("[+] Compression finished.\n");

    return 0;
}