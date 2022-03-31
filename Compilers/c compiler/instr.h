//
// Created on 17.02.2022.
//

#ifndef TURING_COMPLETE_INSTR
#define TURING_COMPLETE_INSTR

typedef struct instruction {
    unsigned char op_code;
    unsigned char arg1, arg2, arg3;
    unsigned long imm;
} instruction;

#endif //TURING_COMPLETE_INSTR

#ifndef TURING_COMPLETE_INSTR_H
#define TURING_COMPLETE_INSTR_H

#include "util.h"

#define IMMEDIATE_FLAG 0x10

typedef struct instr_node {
    instruction *instr;
    struct instr_node *next;
    struct instr_node *prev;
} instr_node;

typedef struct instruction_list {
    instr_node *head;
    instr_node *tail;
    int length;
} instruction_list;

typedef enum opcode {
    NOP = 0x00,
    //jumps
    JMP = 0x01, JE = 0x02, JNE = 0x03, JL = 0x04, JLE = 0x05, JG = 0x06, JGE = 0x07,
    B = 0x09, BE = 0x0A, BNE = 0x0B, BL = 0x0C, BLE = 0x0D, BG = 0x0E, BGE = 0x0F,
    //branches
    JEI = 0x12, JNEI = 0x13, JLI = 0x14, JLEI = 0x15, JGI = 0x16, JGEI = 0x17,
    BEI = 0x1A, BNEI = 0x1B, BLI = 0x1C, BLEI = 0x1D, BGI = 0x1E, BGEI = 0x1F,
    //memory
    LW = 0x40, LWI = 0x50, SW = 0x41, SWI = 0x51,
    //function
    CALL = 0x42, RET = 0x43,
    //io
    LIO = 0x44, SIO = 0x45,
    //alu
    ADD = 0x80, SUB = 0x81, MUL = 0x82, AND = 0x83, OR = 0x84, NOT = 0x85, XOR = 0x86, XNOR = 0x87, NOR = 0x88,
    CEQ = 0x89, CLT = 0x8A, CLTE = 0x8B, SHR = 0x8C, SHL = 0x8D, RR = 0x8E, RL = 0x8F, /* NOTI does not exist */
    ADDI = 0x90, SUBI = 0x91, MULI = 0x92, ANDI = 0x93, ORI = 0x94, XORI = 0x96, XNORI = 0x97, NORI = 0x98,
    CEQI = 0x99, CLTI = 0x9A, CLTEI = 0x9B, SHRI = 0x9C, SHLI = 0x9D, RRI = 0x9E, RLI = 0x9F,
    //r-type
    CP = 0xC0, CPEQ = 0xC2, CPNE = 0xC3, CPL = 0xC4, CPLE = 0xC5, CPG = 0xC6, CPGE = 0xC7,
    CPI = 0xD0, CPEQI = 0xD2, CPNEI = 0xD3, CPLI = 0xD4, CPLEI = 0xD5, CPGI = 0xD6, CPGEI = 0xD7,
    SWP = 0xC8, SWPEQ = 0xCA, SWPNE = 0xCB, SWPL = 0xCC, SWPLE = 0xCD, SWPG = 0xCE, SWPGE = 0xCF,
    SWPI = 0xD8, SWPEQI = 0xDA, SWPNEI = 0xDB, SWPLI = 0xDC, SWPLEI = 0xDD, SWPGI = 0xDE, SWPGEI = 0xDF
} opcode;

typedef enum comp_func {
    EQ = 0x02, NE = 0x03, LT = 0x04, LE = 0x05, GT = 0x06, GE = 0x07
} comp_func;

instr_node *create_instr_list_node(instruction *instr);

instruction_list *create_instr_list();

void instr_list_add(instruction_list *list, instruction *instr);

int instr_list_length(instruction_list *list);

instruction *instr_list_to_array(instruction_list *list);

void instr_list_clear(instruction_list *list);

instruction *create_instruction(opcode op_code, unsigned char arg1, unsigned char arg2, unsigned char arg3,
                                unsigned long imm);

void write_all(char *filename, instruction *instr, int amount, bool append);

instruction *instr_jump_no_cond(unsigned long long target, bool branch);

instruction *instr_jump_cond(comp_func condition, unsigned char regA, unsigned char regB, unsigned long target,
                             bool branch);

instruction *instr_jump_cond_imm(comp_func condition, unsigned char regA, unsigned short target,
                                 unsigned long compare_value, bool branch);

instruction *instr_memory_load(unsigned long addr, unsigned char target);

instruction *instr_memory_load_imm(unsigned long addr, unsigned char target, unsigned char reg);

instruction *instr_memory_store(unsigned long addr, unsigned char source);

instruction *instr_memory_store_imm(unsigned long addr, unsigned char source, unsigned char reg);

instruction *instr_io_read(unsigned long addr, unsigned char regA, unsigned char regB);

instruction *instr_io_write(unsigned long addr, unsigned char regA, unsigned char regB);

instruction *instr_call(unsigned long long addr);

instruction *instr_return();

instruction *instr_copy(unsigned char from, unsigned char to);

instruction *instr_copy_cond(comp_func condition, unsigned char from, unsigned char to, unsigned char regA,
                             unsigned long valueB);

instruction *instr_copy_imm(unsigned long imm, unsigned char to);

instruction *instr_copy_cond_imm(comp_func condition, unsigned long imm, unsigned char to, unsigned char regA,
                                 unsigned char regB);

instruction *instr_swap(unsigned char regA, unsigned char regB);

instruction *instr_swap_cond(comp_func condition, unsigned char regA, unsigned char regB);

#endif //TURING_COMPLETE_INSTR_H
