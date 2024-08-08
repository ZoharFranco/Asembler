/*
 ============================================================================
 Name        : opcode.c
 Author      : Zohar Franco
 Version     :
 Copyright   : Your copyright notice
 Description : Opcode file - declare all opcodes and + functions and declarations of opcodes utils
 ============================================================================
 */


#include <stdlib.h>
#include "../utils/array_utils.h"
#include "opcodes.h"
#include "registers.h"


Opcode OpcodesArray[] = {
        {MOV,  "mov",  2, {IMMEDIATE_ADDRESSING, DIRECT_ADDRESSING, REGISTRY_INDIRECT_ADDRESSING, REGISTRY_DIRECT_ADDRESSING}, {DIRECT_ADDRESSING,    REGISTRY_INDIRECT_ADDRESSING, REGISTRY_DIRECT_ADDRESSING}},
        {CMP,  "cmp",  2, {IMMEDIATE_ADDRESSING, DIRECT_ADDRESSING, REGISTRY_INDIRECT_ADDRESSING, REGISTRY_DIRECT_ADDRESSING}, {IMMEDIATE_ADDRESSING, DIRECT_ADDRESSING,            REGISTRY_INDIRECT_ADDRESSING, REGISTRY_DIRECT_ADDRESSING}},
        {ADD,  "add",  2, {IMMEDIATE_ADDRESSING, DIRECT_ADDRESSING, REGISTRY_INDIRECT_ADDRESSING, REGISTRY_DIRECT_ADDRESSING}, {DIRECT_ADDRESSING,    REGISTRY_INDIRECT_ADDRESSING, REGISTRY_DIRECT_ADDRESSING}},
        {SUB,  "sub",  2, {IMMEDIATE_ADDRESSING, DIRECT_ADDRESSING, REGISTRY_INDIRECT_ADDRESSING, REGISTRY_DIRECT_ADDRESSING}, {DIRECT_ADDRESSING,    REGISTRY_INDIRECT_ADDRESSING, REGISTRY_DIRECT_ADDRESSING}},
        {LEA,  "lea",  2, {DIRECT_ADDRESSING},                                                                                 {DIRECT_ADDRESSING,    REGISTRY_INDIRECT_ADDRESSING, REGISTRY_DIRECT_ADDRESSING}},
        {CLR,  "clr",  1, {},                                                                                                  {DIRECT_ADDRESSING,    REGISTRY_INDIRECT_ADDRESSING, REGISTRY_DIRECT_ADDRESSING}},
        {NOT,  "not",  1, {},                                                                                                  {DIRECT_ADDRESSING,    REGISTRY_INDIRECT_ADDRESSING, REGISTRY_DIRECT_ADDRESSING}},
        {INC,  "inc",  1, {},                                                                                                  {DIRECT_ADDRESSING,    REGISTRY_INDIRECT_ADDRESSING, REGISTRY_DIRECT_ADDRESSING}},
        {DEC,  "dec",  1, {},                                                                                                  {DIRECT_ADDRESSING,    REGISTRY_INDIRECT_ADDRESSING, REGISTRY_DIRECT_ADDRESSING}},
        {JMP,  "jmp",  1, {},                                                                                                  {DIRECT_ADDRESSING,    REGISTRY_INDIRECT_ADDRESSING}},
        {BNE,  "bne",  1, {},                                                                                                  {DIRECT_ADDRESSING,    REGISTRY_INDIRECT_ADDRESSING}},
        {RED,  "red",  1, {},                                                                                                  {DIRECT_ADDRESSING,    REGISTRY_INDIRECT_ADDRESSING, REGISTRY_DIRECT_ADDRESSING}},
        {PRN,  "prn",  1, {},                                                                                                  {IMMEDIATE_ADDRESSING, DIRECT_ADDRESSING,            REGISTRY_INDIRECT_ADDRESSING, REGISTRY_DIRECT_ADDRESSING}},
        {JSR,  "jsr",  1, {},                                                                                                  {DIRECT_ADDRESSING,    REGISTRY_INDIRECT_ADDRESSING}},
        {RTS,  "rts",  0, {},                                                                                                  {}},
        {STOP, "stop", 0, {},                                                                                                  {}}
};


char **get_opcodes_names() {
    char **OpcodesNames = (char **) malloc(OPCODES_LENGTH * sizeof(char *));
    for (int i = 0; i < OPCODES_LENGTH; i++) {
        OpcodesNames[i] = OpcodesArray[i].name;
    }
    return OpcodesNames;
}

int is_opcode_exist(char *opcode) {
    return is_in_array_string(opcode, get_opcodes_names(), OPCODES_LENGTH);
}

Opcode get_opcode_from_opcode_string(char *opcode) {
    return OpcodesArray[get_index_in_array_string(opcode, get_opcodes_names(), OPCODES_LENGTH)];
}

unsigned int get_opcode_bits(Opcode opcode) {
    return opcode.type << OPCODE_BITS_SHIFT;
}


OpcodeInstructionArg parse_opcode_instruction_arg(char *arg) {
    switch (arg[0]) {
        case (IMMEDIATE_ADDRESSING_CHAR): {
            arg += 1;
            return (OpcodeInstructionArg) {arg, NUMBER_OPCODE_ARG, IMMEDIATE_ADDRESSING};
        }

        case (REGISTRY_INDIRECT_ADDRESSING_CHAR): {
            arg += 1;
            return (OpcodeInstructionArg) {arg, REGISTRY_OPCODE_ARG, REGISTRY_INDIRECT_ADDRESSING};
        }

        default:
            if (is_register_exist(arg)) {
                return (OpcodeInstructionArg) {arg, REGISTRY_OPCODE_ARG, REGISTRY_DIRECT_ADDRESSING};
            } else {
                return (OpcodeInstructionArg) {arg, LABEL_OPCODE_ARG, DIRECT_ADDRESSING};
            }

    }
}



