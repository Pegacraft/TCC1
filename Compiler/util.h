//
// Created on 16.02.2022.
//

#ifndef TURING_COMPLETE_UTIL_H
#define TURING_COMPLETE_UTIL_H

typedef enum {
    false, true
} bool;

typedef enum {
    NUMBER, BOOLEAN, ARRAY
} VarType;

char *read_file(char *fileName, bool skipSpacing);

void write_file(char *fileName, char *data);

#endif //TURING_COMPLETE_UTIL_H
