/*
 ============================================================================
 Name        : instructions.c
 Author      : zohar franco
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
#include "array_utils.h"
#include "errors_handling.h"


char *parse_instruction_label(FileLine file_line) {
    char *label;
    label = (char *) malloc(LABEL_MAX_SIZE * sizeof(char));
    if (label == NULL) {
        log_internal_error(ALLOCATION_FAILED_TO_ALLOCATE_MEMORY);
        return NULL;
    }

    if (strchr(file_line.line, ':')) {
        if (sscanf(file_line.line, "%[^:]:", label) != 1) {
            free(label);  // Free allocated memory on error
            log_internal_error(ALLOCATION_FAILED_TO_ALLOCATE_MEMORY);
            return "";
        }
    } else {
        label = "";
    }
    return label;
}

char *parse_instruction_key(FileLine file_line) {
    char *instruction_key = (char *) malloc(INSTRUCTION_KEY_MAX_SIZE * sizeof(char));
    if (instruction_key == NULL) {
        log_internal_error(ALLOCATION_FAILED_TO_ALLOCATE_MEMORY);
        return NULL;
    }

    // Check if there's a colon in the line
    if (strchr(file_line.line, ':')) {
        if (sscanf(file_line.line, "%*[^:]: %s", instruction_key) != 1) {
            free(instruction_key);  // Free allocated memory on error
            log_internal_error(ALLOCATION_FAILED_TO_ALLOCATE_MEMORY);
            return "";
        }
    } else {
        // If no colon, just copy the entire line
        if (sscanf(file_line.line, "%s", instruction_key) != 1) {
            free(instruction_key);  // Free allocated memory on error
            log_internal_error(ALLOCATION_FAILED_TO_ALLOCATE_MEMORY);
            return "";
        }
    }
    return instruction_key;
}

char *parse_instruction_args(FileLine file_line) {
    char *args = (char *) malloc(INSTRUCTION_ARGS_MAX_SIZE * sizeof(char));
    if (args == NULL) {
        log_internal_error(ALLOCATION_FAILED_TO_ALLOCATE_MEMORY);
        return NULL;
    }


    // Check if there's a colon in the line
    if (strchr(file_line.line, ':')) {
        if (sscanf(file_line.line, "%*[^:]: %*s %[^:^\n]", args) != 1) {
            free(args);  // Free allocated memory on error
            log_internal_error(ALLOCATION_FAILED_TO_ALLOCATE_MEMORY);
            return "";
        }
    } else {
        // If no colon, just copy the entire line
        if (sscanf(file_line.line, "%*s %[^:^\n]", args) != 1) {
            free(args);  // Free allocated memory on error
            log_internal_error(ALLOCATION_FAILED_TO_ALLOCATE_MEMORY);
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
    int number_of_args;
    char **split_args = split_string(args, " ", &number_of_args);

    OpcodeInstructionArg source_arg = {};
    OpcodeInstructionArg destination_arg = {};

    if (number_of_args >= 1) {
        source_arg = parse_opcode_instruction_arg(split_args[0]);
        if (number_of_args == 2) {
            destination_arg = parse_opcode_instruction_arg(split_args[1]);
        }
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
    return (is_empty_string(label)) || (!is_opcode_exist(label) && !is_directive_exist(label));
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
    int opcode_line = get_opcode_bits(instruction.opcode);
    opcode_line += get_addressing_bits(instruction.source_arg.addressing) << SOURCE_ADDRESSING_BITS_SHIFT;
    opcode_line += get_addressing_bits(instruction.destination_arg.addressing) << DESTINATION_ADDRESSING_BITS_SHIFT;
    opcode_line += get_encoding_bits(A);
    machine_code_lines[0] = (MachineCodeLine) {!is_empty_string(instruction.label), number_int_to_binary(opcode_line)};
    machine_code_content.line_count++;

    if (instruction.number_of_args == 1) {
        if (instruction.source_arg.type == REGISTRY_OPCODE_ARG) {

        } else if (instruction.source_arg.type == LABEL_OPCODE_ARG) {

        } else if (instruction.source_arg.type == NUMBER_OPCODE_ARG) {

        } else {
            machine_code_content.error = 1;
        }

    }

    if (instruction.number_of_args == 2) {
        if (instruction.source_arg.type == REGISTRY_OPCODE_ARG) {

        } else if (instruction.source_arg.type == LABEL_OPCODE_ARG) {

        } else if (instruction.source_arg.type == NUMBER_OPCODE_ARG) {

        } else {
            machine_code_content.error = 1;
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

    remove_whitespace(instruction.args);
    int count;
    char **split_args = split_string(instruction.args, ",", &count);
    MachineCodeLine *machine_code_lines = malloc(count * sizeof(MachineCodeLine));
    char **numbers_bits = numbers_to_binary_list(split_args, count);

    for (int i = 0; i < count; i++) {
        if (!is_valid_number(numbers_bits[i])) {
            machine_code_content.error = DATA_BAD_FORMAT;
            return machine_code_content;
        }
        machine_code_lines[i] = (MachineCodeLine) {0, numbers_bits[i]};
    }

    machine_code_content.lines = machine_code_lines;
    machine_code_content.line_count = count;
    return machine_code_content;
}

MachineCodeContent string_directive_instruction_to_machine_code_content(DirectiveInstruction instruction) {
    MachineCodeContent machine_code_content;
    machine_code_content.error = 0;

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
    for (int i = 0; i < machine_code_content.line_count; i++) {
        char char_string[] = {instruction.args[i], '\0'};
        machine_code_lines[i] = (MachineCodeLine) {0, char_string};
    }
    machine_code_content.lines = machine_code_lines;

    return machine_code_content;
}







