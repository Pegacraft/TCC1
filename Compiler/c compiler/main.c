//
// Created on 15.02.2022.
//

#include <stdlib.h>
#include <stdio.h>
#include "util.h"
#include "instr.h"
#include "parse.h"

int main(int argc, char *argv[]) {

    token *tok = tokenize("test=(1,2,3)");

    while (tok != NULL) {
        printf("(%d) %c ", tok->type, tok->value);
        tok = tok->next;
    }

//    instruction *lio = instr_io_read(10L, 1, 0);
//    instruction *add = create_instruction(ADDI, 1, 0, 1, 5L);
//    instruction *sio = instr_io_write(9L, 1, 0);
//    instruction_list *list = create_instr_list();
//    instr_list_add(list, lio);
//    instr_list_add(list, add);
//    instr_list_add(list, sio);
//    instruction *instructions = instr_list_to_array(list);
//    write_all("T:/test.code", instructions, 3, false);
//    instr_list_clear(list);
//    free(list);
//    free(lio);
//    free(add);
//    free(sio);
    return 0;
}