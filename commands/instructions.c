/*
 ============================================================================
 Name        : instructions.c
 Author      : Zohar Franco
 Version     :
 Copyright   : Your copyright notice
 Description : Instructions file - declare all instructions parse and logic functions
 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/strings_utils.h"
#include "instructions.h"
#include "opcodes.h"
#include "addressing.h"
#include "encoding.h"
#include "../utils/array_utils.h"
#include "../errors/errors_handling.h"
#include "registers.h"
#include "../precompile/macros.h"


char *parse_instruction_label(FileLine file_line) {
    char *label;
    label = (char *) malloc(LABEL_BUFFER_SIZE * sizeof(char));
    if (label == NULL) {
        log_internal_error(ALLOCATION_FAILED_TO_ALLOCATE_MEMORY);
        return NULL;
    }

    if (strchr(file_line.line, ':')) {
        if (sscanf(file_line.line, "%[^:]:", label) != 1) {
            free(label);  // Free allocated memory on error
            return "";
        }
    } else {
        label = "";
    }
    return label;
}

char *parse_instruction_key(FileLine file_line) {
    char *instruction_key = (char *) malloc(INSTRUCTION_KEY_BUFFER_SIZE * sizeof(char));
    if (instruction_key == NULL) {
        log_internal_error(ALLOCATION_FAILED_TO_ALLOCATE_MEMORY);
        return NULL;
    }

    // Check if there's a colon in the line
    if (strchr(file_line.line, ':')) {
        if (sscanf(file_line.line, "%*[^:]: %s", instruction_key) != 1) {
            free(instruction_key);  // Free allocated memory on error
            return "";
        }
    } else {
        // If no colon, just copy the entire line
        if (sscanf(file_line.line, "%s", instruction_key) != 1) {
            free(instruction_key);  // Free allocated memory on error
            return "";
        }
    }
    return instruction_key;
}

char *parse_instruction_args(FileLine file_line) {
    char *args = (char *) malloc(INSTRUCTION_ARGS_BUFFER_SIZE * sizeof(char));
    if (args == NULL) {
        log_internal_error(ALLOCATION_FAILED_TO_ALLOCATE_MEMORY);
        return NULL;
    }

    // Check if there's a colon in the line
    if (strchr(file_line.line, ':')) {
        if (sscanf(file_line.line, "%*[^:]: %*s %[^:^\n]", args) != 1) {
            free(args);  // Free allocated memory on error
            return "";
        }
    } else {
        // If no colon, just copy the entire line
        if (sscanf(file_line.line, "%*s %[^:^\n]", args) != 1) {
            free(args);  // Free allocated memory on error
            return "";
        }
    }

    return args;

}

InstructionType get_instruction_type(FileLine file_line) {
    char *instruction_key = parse_instruction_key(file_line);
    if (is_opcode_exist(instruction_key)) return OPCODE_INSTRUCTION;
    if (is_directive_exist(instruction_key)) return DIRECTIVE_INSTRUCTION;
    return -1;
}

OpcodeInstruction parse_opcode_instruction(FileLine file_line) {
    char *label = parse_instruction_label(file_line);
    Opcode opcode = get_opcode_from_opcode_string(parse_instruction_key(file_line));
    char *args = parse_instruction_args(file_line);
    remove_whitespace(args);

    int number_of_args;
    char **split_args = split_string(args, ",", &number_of_args);

    OpcodeInstructionArg source_arg = {};
    OpcodeInstructionArg destination_arg = {};

    if (number_of_args == 1) {
        destination_arg = parse_opcode_instruction_arg(split_args[0]);
    }
    if (number_of_args == 2) {
        source_arg = parse_opcode_instruction_arg(split_args[0]);
        destination_arg = parse_opcode_instruction_arg(split_args[1]);
    }


    OpcodeInstruction opcode_instruction;
    opcode_instruction.number_of_args = number_of_args;
    opcode_instruction.opcode = opcode;
    opcode_instruction.source_arg = source_arg;
    opcode_instruction.destination_arg = destination_arg;
    opcode_instruction.assembly_line = file_line.line_number;
    opcode_instruction.label = label;
    return opcode_instruction;
}

DirectiveInstruction parse_directive_instruction(FileLine file_line) {
    char *label = parse_instruction_label(file_line);
    Directive directive = get_directive_from_directive_string(parse_instruction_key(file_line));
    char *args = parse_instruction_args(file_line);

    DirectiveInstruction directive_instruction;
    directive_instruction.assembly_line = file_line.line_number;
    directive_instruction.label = label;
    directive_instruction.directive = directive;
    directive_instruction.args = args;
    return directive_instruction;
}


int is_valid_label(char *label) {
    return (is_empty_string(label)) ||
           (!is_opcode_exist(label) && !is_directive_exist(label) && is_alphabet_digits_no_spaces_string(label)
            && strcmp(label, MACRO_END_LABEL) != 0 && strcmp(label, MACRO_START_LABEL) != 0);
}

int is_valid_opcode_instruction(OpcodeInstruction instruction) {
    if (!is_valid_label(instruction.label)) {
        return ILLEGAL_LABEL;
    }
    if (instruction.number_of_args != instruction.opcode.number_of_args) {
        return OPCODE_ILLEGAL_NUMBER_OF_ARGS;
    }
    if (!is_in_array_int(instruction.source_arg.addressing, (int *) instruction.opcode.source_addressings,
                         ADDRESSINGS_LENGTH)) {
        return OPCODE_ILLEGAL_SOURCE_ADDRESSING;
    }
    if (!is_in_array_int(instruction.destination_arg.addressing, (int *) instruction.opcode.destination_addressings,
                         ADDRESSINGS_LENGTH)) {
        return OPCODE_ILLEGAL_DESTINATION_ADDRESSING;
    }
    return SUCCESS;
}

MachineCodeContent opcode_instruction_to_machine_code_content(OpcodeInstruction instruction) {
    MachineCodeContent machine_code_content;
    machine_code_content.error = 0;
    machine_code_content.line_count = 0;

    int is_valid_opcode = is_valid_opcode_instruction(instruction);
    if (is_valid_opcode != SUCCESS) {
        machine_code_content.error = is_valid_opcode;
        return machine_code_content;
    }

    MachineCodeLine *machine_code_lines = malloc((instruction.number_of_args + 1) * sizeof(MachineCodeLine));

    // Create opcode machine code line
    unsigned int opcode_bits = get_opcode_bits(instruction.opcode);

    if (instruction.number_of_args == 1) {
        opcode_bits += get_addressing_bits(instruction.destination_arg.addressing) << DESTINATION_ADDRESSING_BITS_SHIFT;
    }
    if (instruction.number_of_args == 2) {
        opcode_bits += get_addressing_bits(instruction.source_arg.addressing) << SOURCE_ADDRESSING_BITS_SHIFT;
        opcode_bits += get_addressing_bits(instruction.destination_arg.addressing) << DESTINATION_ADDRESSING_BITS_SHIFT;
    }

    opcode_bits += get_encoding_bits(A);
    machine_code_lines[0] = (MachineCodeLine) {0, instruction.label, opcode_bits};
    machine_code_content.line_count++;

    unsigned int bits;
    // Create opcode args machine code lines
    if (instruction.number_of_args == 2 &&
        instruction.source_arg.type == REGISTRY_OPCODE_ARG &&
        instruction.destination_arg.type == REGISTRY_OPCODE_ARG) {
        // Handle two registers args
        machine_code_content.line_count++;
        Register reg1 = get_register_from_register_string(instruction.source_arg.data);
        Register reg2 = get_register_from_register_string(instruction.destination_arg.data);
        bits = get_registers_bits(reg1, reg2) + get_encoding_bits(A);
        machine_code_lines[1] = (MachineCodeLine) {0, "", bits};

    } else {

        // Handle one argument
        if (instruction.number_of_args == 1) {
            machine_code_content.line_count++;
            MachineCodeLine arg1_machine_code_line;
            if (instruction.destination_arg.type == REGISTRY_OPCODE_ARG) {
                arg1_machine_code_line.is_label = 0;
                Register reg = get_register_from_register_string(instruction.destination_arg.data);
                bits = get_register_bits(reg, 0) + get_encoding_bits(A);
                arg1_machine_code_line.line = bits;
            } else if (instruction.destination_arg.type == LABEL_OPCODE_ARG) {
                arg1_machine_code_line.is_label = 1;
                arg1_machine_code_line.label = instruction.destination_arg.data;
            } else {
                // Number argument
                arg1_machine_code_line.is_label = 0;
                arg1_machine_code_line.line =
                        (atoi(instruction.destination_arg.data) << ENCODINGS_BITS) + get_encoding_bits(A);
            }
            machine_code_lines[1] = arg1_machine_code_line;

        }

        // Handle second argument (must be register)
        if (instruction.number_of_args == 2) {
            machine_code_content.line_count++;
            MachineCodeLine arg1_machine_code_line;
            if (instruction.source_arg.type == REGISTRY_OPCODE_ARG) {
                arg1_machine_code_line.is_label = 0;
                Register reg = get_register_from_register_string(instruction.source_arg.data);
                bits = get_register_bits(reg, 1) + get_encoding_bits(A);
                arg1_machine_code_line.line = bits;
            } else if (instruction.source_arg.type == LABEL_OPCODE_ARG) {
                arg1_machine_code_line.is_label = 1;
                arg1_machine_code_line.label = instruction.source_arg.data;
            } else {
                // Number argument
                arg1_machine_code_line.is_label = 0;
                arg1_machine_code_line.line =
                        (atoi(instruction.source_arg.data) << ENCODINGS_BITS) + get_encoding_bits(A);
            }
            machine_code_lines[1] = arg1_machine_code_line;

            machine_code_content.line_count++;
            MachineCodeLine arg2_machine_code_line;
            if (instruction.destination_arg.type == REGISTRY_OPCODE_ARG) {
                arg2_machine_code_line.is_label = 0;
                Register reg = get_register_from_register_string(instruction.destination_arg.data);
                bits = get_register_bits(reg, 0) + get_encoding_bits(A);
                arg2_machine_code_line.line = bits;
            } else if (instruction.destination_arg.type == LABEL_OPCODE_ARG) {
                arg2_machine_code_line.is_label = 1;
                arg2_machine_code_line.label = instruction.destination_arg.data;
            } else {
                // Number argument
                arg2_machine_code_line.is_label = 0;
                arg2_machine_code_line.line =
                        (atoi(instruction.destination_arg.data) << ENCODINGS_BITS) + get_encoding_bits(A);
            }
            machine_code_lines[2] = arg2_machine_code_line;
        }
    }


    machine_code_content.lines = machine_code_lines;
    return machine_code_content;
}

MachineCodeContent data_directive_instruction_to_machine_code_content(DirectiveInstruction instruction) {
    MachineCodeContent machine_code_content;
    machine_code_content.error = 0;

    if (!is_valid_label(instruction.label)) {
        machine_code_content.error = ILLEGAL_LABEL;
        return machine_code_content;
    }


    int count;
    char **split_args = split_string(instruction.args, ",", &count);

    MachineCodeLine *machine_code_lines = malloc(count * sizeof(MachineCodeLine));

    for (int i = 0; i < count; i++) {
        remove_whitespace(split_args[i]);
        if (!is_valid_number(split_args[i])) {
            machine_code_content.error = DATA_BAD_FORMAT;
            return machine_code_content;
        }
        machine_code_lines[i] = (MachineCodeLine) {0, "", atoi(split_args[i])};
    }

    machine_code_content.lines = machine_code_lines;
    machine_code_content.line_count = count;
    return machine_code_content;
}

MachineCodeContent string_directive_instruction_to_machine_code_content(DirectiveInstruction instruction) {
    MachineCodeContent machine_code_content;
    machine_code_content.error = 0;
    machine_code_content.line_count = 0;

    if (!is_valid_label(instruction.label)) {
        machine_code_content.error = ILLEGAL_LABEL;
        return machine_code_content;
    }

    if (!is_valid_string(instruction.args)) {
        machine_code_content.error = STRING_BAD_FORMAT;
        return machine_code_content;
    }

    machine_code_content.line_count = (int) strlen(instruction.args) - 1;
    MachineCodeLine *machine_code_lines = malloc(machine_code_content.line_count * sizeof(MachineCodeLine));
    for (int i = 0; i < machine_code_content.line_count - 1; i++) {
        machine_code_lines[i] = (MachineCodeLine) {0, "", (int) instruction.args[i + 1]};
    }
    machine_code_lines[machine_code_content.line_count-1] = (MachineCodeLine) {0, "", 0};
    machine_code_content.lines = machine_code_lines;

    return machine_code_content;
}







