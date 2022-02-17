//
// Created on 15.02.2022.
//

#include "util.h"
#include "instr.h"

int main(int argc, char *argv[]) {

    instruction *lio = instr_io_read(10L,1,0);
    instruction *add = create_instruction(ADDI, 1, 0, 1, 5L);
    instruction *sio = instr_io_write(9L, 1, 0);
    instruction instr[] = {*lio, *add, *sio};
    write_all("T:/test.code", instr, 3, false);
    return 0;
}