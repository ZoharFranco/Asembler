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
#define INSTRUCTION_KEY_MAX_SIZE 30
#define INSTRUCTION_ARGS_MAX_SIZE 50


/*!
 * Enum of instruction types
 */
typedef enum InstructionType {
    OPCODE_INSTRUCTION, DIRECTIVE_INSTRUCTION, INSTRUCTION_TYPES_LENGTH
} InstructionType;


/*!
 * OpcodeInstruction struct contain string label, Opcode opcode and InstructionArg array agrs
 */
typedef struct OpcodeInstruction {
    int assembly_line;
    char *label;
    Opcode opcode;
    OpcodeInstructionArg source_arg;
    OpcodeInstructionArg destination_arg;
    int number_of_args;
} OpcodeInstruction;


/*!
 * DirectiveInstruction struct contain string label, Directive directive and string agrs
 */
typedef struct DirectiveInstruction {
    int assembly_line;
    char *label;
    Directive directive;
    char *args;
} DirectiveInstruction;


/*!
 * MachineCodeLine strict contains is_label if the line is label to insert it's address and content of line as string of bits
 */
typedef struct MachineCodeLine {
    int is_label;
    char *label;
    unsigned int line;
} MachineCodeLine;


/*!
 * MachineCodeContent struct contain machine code lines, length, error if got error through process to machine code content
 */
typedef struct MachineCodeContent {
    MachineCodeLine *lines;
    int line_count;
    ErrorNumber error;
} MachineCodeContent;


/*!
 * Parse instruction label form line
 * @param file_line : the file line to parse from
 * @return the instruction label
 */
char *parse_instruction_label(FileLine file_line);


/*!
 * Parse instruction key form line
 * @param file_line : the file line to parse from
 * @return the instruction key
 */
char *parse_instruction_key(FileLine file_line);


/*!
 * Parse instruction args form line
 * @param file_line : the file line to parse from
 * @return the instruction args
 */
char *parse_instruction_args(FileLine file_line);


/*!
 * Parse instruction type form line, by instruction key gets the type (InstructionType)
 * @param file_line : the file line to parse from
 * @return the instruction type
 */
InstructionType get_instruction_type(FileLine file_line);


/*!
 * Parse opcode instruction form line
 * @param file_line : the file line to parse
 * @return the opcode instruction object
 */
OpcodeInstruction parse_opcode_instruction(FileLine file_line);

/*!
 * Parse directive instruction form line
 * @param file_line : the file line to parse
 * @return the directive instruction object
 */
DirectiveInstruction parse_directive_instruction(FileLine file_line);

/*!
 * Check if the string label is legal label (not opcode key, not directive key, not macros keywords, string)
 * @param label : label to check
 * @return returns 1 if  valid and 0 otherwise
 */
int is_valid_label(char *label);


/*!
 * Check if the opcode instruction is legal (legal label, legal number of args, legal source and dst addressing)
 * @param instruction : instruction to check
 * @return returns 1 if  valid and 0 otherwise
 */
int is_valid_opcode_instruction(OpcodeInstruction instruction);


/*!
 * Function that gets opcode instruction and process it to get the representative machine code content
 * @param instruction : instruction to process
 * @return the machine code content from the instruction
 */
MachineCodeContent opcode_instruction_to_machine_code_content(OpcodeInstruction instruction);


/*!
 * Function that gets data directive instruction and process it to get the representative machine code content
 * @param instruction : instruction to process
 * @return the machine code content from the instruction
 */
MachineCodeContent data_directive_instruction_to_machine_code_content(DirectiveInstruction instruction);


/*!
 * Function that gets string directive instruction and process it to get the representative machine code content
 * @param instruction : instruction to process
 * @return the machine code content from the instruction
 */
MachineCodeContent string_directive_instruction_to_machine_code_content(DirectiveInstruction instruction);


#endif // INSTRUCTIONS_H
