//
// Created on 17.02.2022.
//

#include <stdio.h>
#include <stdlib.h>
#include "instr.h"

instr_node *create_instr_list_node(instruction *instr) {
    instr_node *node = malloc(sizeof(struct instr_node));
    node->instr = instr;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

instruction_list *create_instr_list() {
    instruction_list *list = malloc(sizeof(struct instruction_list));
    list->length = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void instr_list_add(instruction_list *list, instruction *instr) {
    instr_node *node = create_instr_list_node(instr);
    if (list->tail != NULL) {
        instr_node *tail = list->tail;
        tail->next = node;
        node->prev = tail;
        list->tail = node;
    } else if (list->head != NULL) {
        list->head->next = node;
        node->prev = list->head;
        list->tail = node;
    } else {
        list->head = node;
    }
    list->length += 1;
}

int instr_list_length(instruction_list *list) {
    return list->length;
}

instruction *instr_list_to_array(instruction_list *list) {
    int length = instr_list_length(list);
    instruction *instructions = malloc(length * sizeof(struct instruction));
    instr_node *head = list->head;
    for (int i = 0; i < length; i++) {
        instructions[i] = *head->instr;
        head = head->next;
    }
    return instructions;
}

void instr_list_clear(instruction_list *list) {
    int length = instr_list_length(list);
    instr_node *head = list->head;
    for (int i = 0; i < length; i++) {
        instr_node *next = head->next;
        free(head);
        head = next;
    }
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
}

instruction *create_instruction(opcode op_code, unsigned char arg1, unsigned char arg2, unsigned char arg3,
                                unsigned long imm) {
    instruction *instr = (instruction *) malloc(sizeof(struct instruction));
    instr->op_code = op_code;
    instr->arg1 = arg1;
    instr->arg2 = arg2;
    instr->arg3 = arg3;
    instr->imm = imm;
    return instr;
}

void write_raw(FILE *fp, instruction *instr) {
    unsigned long n = instr->imm;
    unsigned char bytes[4];
    bytes[0] = (n >> 24) & 0xFF;
    bytes[1] = (n >> 16) & 0xFF;
    bytes[2] = (n >> 8) & 0xFF;
    bytes[3] = n & 0xFF;
    fwrite(&bytes[3], sizeof(unsigned char), 1, fp);
    fwrite(&bytes[2], sizeof(unsigned char), 1, fp);
    fwrite(&bytes[1], sizeof(unsigned char), 1, fp);
    fwrite(&bytes[0], sizeof(unsigned char), 1, fp);
    fwrite(&instr->arg3, sizeof(unsigned char), 1, fp);
    fwrite(&instr->arg2, sizeof(unsigned char), 1, fp);
    fwrite(&instr->arg1, sizeof(unsigned char), 1, fp);
    fwrite(&instr->op_code, sizeof(unsigned char), 1, fp);
}

void write_all(char *filename, instruction *instr, int amount, bool append) {
    FILE *fp = fopen(filename, append ? "ab" : "wb");
    if (fp == NULL) {
        printf("ERROR, compiler doesnt like your file. (or just cannot find it) \"%s\"", filename);
        return;
    }
    for (int i = 0; i < amount; i++) {
        write_raw(fp, &instr[i]);
    }
    fclose(fp);
}

instruction *instr_jump_no_cond(unsigned long long int target, bool branch) {
    return create_instruction(branch ? B : JMP, target >> 48 & 0xFF, target >> 40 & 0xFF, target >> 32 & 0xFF, target);
}

instruction *instr_jump_cond(comp_func condition, unsigned char regA, unsigned char regB, unsigned long target,
                             bool branch) {
    return create_instruction((branch ? B : JMP) + condition - 1, regA, regB, 0, target);
}

instruction *instr_jump_cond_imm(comp_func condition, unsigned char regA, unsigned short target,
                                 unsigned long compare_value, bool branch) {
    return create_instruction((branch ? B : JMP) + condition - 1 + IMMEDIATE_FLAG, regA, target >> 8 & 0xFF,
                              target & 0xFF,
                              compare_value);
}

instruction *instr_memory_load(unsigned long addr, unsigned char target) {
    return create_instruction(LW, 0, 0, target, addr);
}

instruction *instr_memory_load_imm(unsigned long addr, unsigned char target, unsigned char reg) {
    return create_instruction(LWI, 0, reg, target, addr);
}

instruction *instr_memory_store(unsigned long addr, unsigned char source) {
    return create_instruction(SW, 0, 0, source, addr);
}

instruction *instr_memory_store_imm(unsigned long addr, unsigned char source, unsigned char reg) {
    return create_instruction(SWI, 0, reg, source, addr);
}

instruction *instr_io_read(unsigned long addr, unsigned char regA, unsigned char regB) {
    return create_instruction(LIO, regA, regB, 0, addr);
}

instruction *instr_io_write(unsigned long addr, unsigned char regA, unsigned char regB) {
    return create_instruction(SIO, regA, regB, 0, addr);
}

instruction *instr_call(unsigned long long int target) {
    return create_instruction(CALL, target >> 48 & 0xFF, target >> 40 & 0xFF, target >> 32 & 0xFF, target);
}

instruction *instr_return() {
    return create_instruction(RET, 0, 0, 0, 0);
}

instruction *instr_copy(unsigned char from, unsigned char to) {
    return create_instruction(CP, from, 0, to, 0);
}

instruction *instr_copy_cond(comp_func condition, unsigned char from, unsigned char to, unsigned char regA,
                             unsigned long valueB) {
    return create_instruction(CP + condition, regA, from, to, valueB);
}

instruction *instr_copy_imm(unsigned long imm, unsigned char to) {
    return create_instruction(CPI, 0, 0, to, imm);
}

instruction *instr_copy_cond_imm(comp_func condition, unsigned long imm, unsigned char to, unsigned char regA,
                                 unsigned char regB) {
    return create_instruction(CPI + condition, regA, regB, to, imm);
}

instruction *instr_swap(unsigned char regA, unsigned char regB) {
    return create_instruction(SWP, regA, regB, 0, 0);
}

instruction *instr_swap_cond(comp_func condition, unsigned char regA, unsigned char regB) {
    return create_instruction(SWP + condition, regA, regB, 0, 0);
}
