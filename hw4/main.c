#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int copyFile(const char *srcFile, const char *destFile) {
    FILE *src_fp = fopen(srcFile, "r");
    if (src_fp == NULL) {
        printf("Не удалось открыть исходный файл: %s\n", srcFile);
        return 1;
    }

    FILE *dest_fp = fopen(destFile, "w");
    if (dest_fp == NULL) {
        printf("Не удалось открыть целевой файл: %s\n", destFile);
        fclose(src_fp);
        return 1;
    }

    char buffer[BUFFER_SIZE];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, sizeof(char), BUFFER_SIZE, src_fp)) > 0) {
        fwrite(buffer, sizeof(char), bytesRead, dest_fp);
    }

    fclose(src_fp);
    fclose(dest_fp);

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Использование: %s <исходный_файл> <целевой_файл>\n", argv[0]);
        return 1;
    }

    const char *sourceFile = argv[1];
    const char *destinationFile = argv[2];

    int result = copyFile(sourceFile, destinationFile);

    if (result == 0) {
        printf("Файл успешно скопирован.\n");
    }

    return result;
}
