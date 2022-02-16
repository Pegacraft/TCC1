//
// Created on 16.02.2022.
//

#include <stdio.h>
#include <stdlib.h>
#include "util.h"

char *readFile(char *fileName, bool skipSpacing) {
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
        return result;
    } else return buffer;
}