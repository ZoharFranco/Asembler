#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include "../utils/file_utils.h"

#include "addressing.h"
#include "encoding.h"
#include "directives.h"
#include "opcodes.h"


#define LABEL_MAX_SIZE 30
#define INSTRUCTION_KEY_MAX_SIZE 100
#define INSTRUCTION_ARGS_MAX_SIZE 200
#define INSTRUCTION_ARGS_LENGTH 3


// Enum of instruction types
typedef enum InstructionType {
    OPCODE_INSTRUCTION, DIRECTIVE_INSTRUCTION, INSTRUCTION_TYPES_LENGTH
} InstructionType;


// OpcodeInstruction struct contain string label, Opcode opcode and InstructionArg array agrs
typedef struct OpcodeInstruction {
    int assembly_line;
    char *label;
    Opcode opcode;
    OpcodeInstructionArg source_arg;
    OpcodeInstructionArg destination_arg;
    int number_of_args;
} OpcodeInstruction;

// DirectiveInstruction struct contain string label, Directive directive and string agrs
typedef struct DirectiveInstruction {
    int assembly_line;
    char *label;
    Directive directive;
    char *args;
} DirectiveInstruction;


// MachineCodeLine strict contians is_label if the line is label to insert it's address and content of line as string of bits
typedef struct MachineCodeLine {
    int is_label;
    char *line;
} MachineCodeLine;

// MachineCodeContent struct contain machine code lines, length, error if got error through process to machine code content
typedef struct MachineCodeContent {
    MachineCodeLine *lines;
    int line_count;
    ErrorNumber error;
} MachineCodeContent;


char *parse_instruction_label(FileLine file_line);

char *parse_instruction_key(FileLine file_line);

char *parse_instruction_args(FileLine file_line);

InstructionType get_instruction_type(FileLine file_line);

OpcodeInstruction parse_opcode_instruction(FileLine file_line);

DirectiveInstruction parse_directive_instruction(FileLine file_line);

int is_valid_label(char *label);

int is_valid_opcode_instruction(OpcodeInstruction instruction);

MachineCodeContent opcode_instruction_to_machine_code_content(OpcodeInstruction instruction);

MachineCodeContent data_directive_instruction_to_machine_code_content(DirectiveInstruction instruction);

MachineCodeContent string_directive_instruction_to_machine_code_content(DirectiveInstruction instruction);


#endif // INSTRUCTIONS_H
