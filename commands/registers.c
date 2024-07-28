/*
 ============================================================================
 Name        : registries.c
 Author      : zoharfranco
 Version     :
 Copyright   : Your copyright notice
 Description : registers file - declare all registers and + functions and declarations of opcodes utils
 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include "../utils/array_utils.h"

#include "addressing.h"

#include "registers.h"


Register RegistersArray[] = {
        {R1, "r1"},
        {R2, "r2"},
        {R3, "r3"},
        {R4, "r4"},
        {R5, "r5"},
        {R6, "r6"},
        {R7, "r7"}
};


char **get_registers_names() {
    char **RegistersNames = (char **) malloc(REGISTERS_LENGTH * sizeof(char *));
    for (int i = 0; i < REGISTERS_LENGTH; i++) {
        RegistersNames[i] = RegistersArray[i].name;
    }
    return RegistersNames;
}

int is_register_exist(char *reg) {
    return is_in_array_string(reg, get_registers_names(), REGISTERS_LENGTH);
}

Register get_register_from_register_string(char *reg) {
    return RegistersArray[get_index_in_array_string(reg, get_registers_names(), REGISTERS_LENGTH)];
}

unsigned short get_register_bits(Register reg, int is_src) {
    if (is_src) {
        return (unsigned int) (reg.number + 1) << REGISTER_SRC_BITS_SHIFT;
    } else {
        return (unsigned int) (reg.number + 1) << REGISTER_DST_BITS_SHIFT;
    }

}

unsigned short get_registers_bits(Register src_reg, Register dst_reg) {

    return ((unsigned int) (src_reg.number + 1) << REGISTER_SRC_BITS_SHIFT) +
           ((unsigned int) (dst_reg.number + 1) << REGISTER_DST_BITS_SHIFT);

}



