//
// Created on 15.02.2022.
//

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    NUMBER, ARRAY
} VarType;

typedef struct Variable {

};

int main(int argc, char *argv[]) {

    printf("\n");
    for (int i = 1; i < argc; i++) {
        printf("%s\n", argv[i]);
    }


}

char *readFile(char *fileName) {
    FILE *fp = fopen(fileName, "r");
    if(fp == NULL)
    {
        printf("ERROR, compiler doesnt like your file. (or just cannot find it) \"%s\"", fileName);
        return NULL;
    }
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);
    long file_data_len = size * sizeof(char);
    char* buffer = malloc(file_data_len);
    //TODO
}