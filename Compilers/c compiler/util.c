//
// Created on 16.02.2022.
//

#include <stdio.h>
#include <stdlib.h>
#include "util.h"

char *read_file(char *fileName, bool skipSpacing) {
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("ERROR, compiler doesnt like your file. (or just cannot find it) \"%s\"", fileName);
        return NULL;
    }
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);
    long file_data_len = size * sizeof(char);
    char *buffer = malloc(file_data_len);
    int position = 0;
    char read;
    while ((read = fgetc(fp)) != EOF) {
        if (!skipSpacing || (read != ' ' && read != '\n'))
            buffer[position++] = read;
    }
    if (skipSpacing) {
        char *result = malloc(position * sizeof(char));
        for (int i = 0; i < position; i++) {
            result[i] = buffer[i];
        }
        free(buffer);
        fclose(fp);
        return result;
    } else {
        fclose(fp);
        return buffer;
    }
}

void write_file(char *fileName, char *data) {
    FILE *fp = fopen(fileName, "w");
    int errCode = fputs(data, fp);
    if (errCode == EOF) {
        printf("");
    }
    fclose(fp);
}