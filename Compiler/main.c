//
// Created on 15.02.2022.
//

#include <stdio.h>
#include "util.h"

typedef enum {
    NUMBER, ARRAY
} VarType;

int main(int argc, char *argv[]) {

    char *data = readFile("T:/MadDevs.xml", true);
    printf("%s", data);

}