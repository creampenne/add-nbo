#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void run() {
    printf("syntax : add-nbo <file1> <file2>\n");
    printf("sample : add-nbo a.bin c.bin\n");
}

uint32_t readI(char* fileName) {
    FILE* fp = fopen(fileName, "rb");

    if (fp == nullptr) {
        fprintf(stderr, "fopen returns nullptr %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    uint32_t num;
    size_t readL = fread(&num, 1, sizeof(num), fp);

    if (readL != sizeof(num)) {
        fprintf(stderr, "fread returns %lu\n", readL);
        exit(EXIT_FAILURE);
    }
    num = ntohl(num);
    fclose(fp);

    return num;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        run();
        exit(EXIT_FAILURE);
    }

    uint32_t num1 = readI(argv[1]);
    uint32_t num2 = readI(argv[2]);
    uint32_t num3 = num1 + num2;

    printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", num1, num1, num2, num2, num3, num3);
}
