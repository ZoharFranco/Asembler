/*
 ============================================================================
 Name        : errors_handler.c
 Author      : zohar franco
 Version     :
 Copyright   : Your copyright notice
 Description : Errors handling file - to create function and declarations of errors handling
 ============================================================================
 */


#include "segments.h"
#include "transactions.h"
#include "instructions.h"
#include "strings_utils.h"
#include "symbols.h"
#include "errors_handling.h"


int handle_store_directive_first_transaction(int *DC, Table *data_segment,
                                             Table *symbols_table, DirectiveInstruction directive_instruction) {

    // Handle label (step 6)
    if (!is_empty_string(directive_instruction.label)) {
        if (!is_valid_label(directive_instruction.label)) {
            return ILLEGAL_LABEL;
        }
        if (is_symbol_label_exist(symbols_table, directive_instruction.label)) {
            return SYMBOL_ALREADY_EXIST;
        }

        Symbol symbol = {directive_instruction.label, DATA_SYMBOL, *DC};
        add_symbol(symbols_table, &symbol);
    }

    // Handle data (step 7)
    MachineCodeContent machine_code_content;
    if (directive_instruction.directive.type == DATA_DIRECTIVE) {
        machine_code_content = data_directive_instruction_to_machine_code_content(directive_instruction);
    } else {
        machine_code_content = string_directive_instruction_to_machine_code_content(directive_instruction);
    }
    SegmentEntry segment_entry = (SegmentEntry) {machine_code_content, DATA_SEGMENT, *DC,
                                                 directive_instruction.assembly_line, directive_instruction.label};
    add_segment_entry(data_segment, &segment_entry);
    *DC += machine_code_content.line_count;
    return SUCCESS;
}

int handle_link_directive_first_transaction(Table *symbols_table, DirectiveInstruction directive_instruction) {

    // Handle extern (step 9)
    if (directive_instruction.directive.type == EXTERN_DIRECTIVE) {
        remove_whitespace(directive_instruction.args);
        Symbol symbol = {directive_instruction.args, EXTERNAL_SYMBOL, 0};
        add_symbol(symbols_table, &symbol);
    }
    return SUCCESS;
}

int handle_opcode_instruction_first_transaction(int *IC, Table *code_segment, Table *symbols_table,
                                                OpcodeInstruction opcode_instruction) {

    // Handle label (step 10)
    if (!is_empty_string(opcode_instruction.label)) {
        if (!is_valid_label(opcode_instruction.label)) {
            return ILLEGAL_LABEL;
        }
        if (is_symbol_label_exist(symbols_table, opcode_instruction.label)) {
            return SYMBOL_ALREADY_EXIST;
        }

        Symbol symbol = {opcode_instruction.label, CODE_SYMBOL, *IC + CODE_SEGMENT_START};
        add_symbol(symbols_table, &symbol);
    }

    // Handle data (step 11-12)
    MachineCodeContent machine_code_content = opcode_instruction_to_machine_code_content(opcode_instruction);
    SegmentEntry segment_entry = (SegmentEntry) {machine_code_content, CODE_SEGMENT, *IC,
                                                 opcode_instruction.assembly_line, opcode_instruction.label};
    add_segment_entry(code_segment, &segment_entry);
    *IC += machine_code_content.line_count;
    return SUCCESS;
}

void handle_data_segment_addresses_updates(const int *IC, Table *symbols_table) {

    for (int i = 0; i < symbols_table->size; ++i) {
        Symbol *s = symbols_table->entries[i].data;
        s->address += *IC + 100;
    }
}

int run_first_transaction(FileContent file_content, int *IC, int *DC, Table *code_segment, Table *data_segment,
                          Table *symbols_table) {

    int was_transaction_error = 0;

    // Handle running on instruction lines (steps 2-13)
    for (int i = 0; i < file_content.line_count; i++) {
        ErrorNumber line_status = SUCCESS;

        if (is_empty_string(file_content.lines[i].line)) {
            continue;
        }

        InstructionType instruction_type = get_instruction_type(file_content.lines[i]);
        switch (instruction_type) {

            // Handle directive instruction (steps 5-10)
            case (DIRECTIVE_INSTRUCTION): {
                DirectiveInstruction directive_instruction = parse_directive_instruction(file_content.lines[i]);

                if (directive_instruction.directive.type == DATA_DIRECTIVE ||
                    directive_instruction.directive.type == STRING_DIRECTIVE) {
                    // Handle store directive instruction (steps 5-7)
                    line_status = handle_store_directive_first_transaction(DC, data_segment, symbols_table,
                                                                           directive_instruction);
                } else {
                    // Handle link directive instruction (steps 8-10)
                    line_status = handle_link_directive_first_transaction(symbols_table, directive_instruction);
                }
                break;
            }

                // Handle opcode instruction (steps 11-13)
            case (OPCODE_INSTRUCTION): {
                OpcodeInstruction opcode_instruction = parse_opcode_instruction(file_content.lines[i]);
                line_status = handle_opcode_instruction_first_transaction(IC, code_segment, symbols_table,
                                                                          opcode_instruction);
                break;
            }

            default:
                line_status = INSTRUCTION_NOT_EXIST;
                break;
        }

        if (line_status != SUCCESS) {
            was_transaction_error = 1;
            log_external_error(line_status, i, file_content.file_name);
        }
    }

    // Handle first transaction error check (step 14)
    if (was_transaction_error) {
        return EXTERNAL_FATAL_ERROR;
    }

    // Handle data segment addresses updates (step 15)
    handle_data_segment_addresses_updates(IC, symbols_table);

    return SUCCESS;
}



// Second transaction flow

int handle_entry_directive_updates(Table *symbols_table, DirectiveInstruction directive_instruction) {
    remove_whitespace(directive_instruction.args);
    if (is_symbol_label_exist(symbols_table, directive_instruction.args)) {
        Symbol *symbol = get_symbol_by_label(symbols_table, directive_instruction.args);
        symbol->type = ENTRY_SYMBOL;
        return SUCCESS;
    } else {
        return ENTRY_SYMBOL_NOT_CREATED;
    }

}

int handle_opcodes_missing_addresses(int *IC, Table *code_segment, Table *symbols_table,
                                     OpcodeInstruction opcode_instruction) {
    SegmentEntry *segment_entry = get_segment_entry_by_assembly_line(code_segment, opcode_instruction.assembly_line);
    for (int i = 0; i < segment_entry->machine_code_content.line_count; ++i) {
        MachineCodeLine machine_code_line = segment_entry->machine_code_content.lines[i];
        if (machine_code_line.is_label) {
            Symbol *symbol = get_symbol_by_label(symbols_table, machine_code_line.label);
            machine_code_line.line = symbol->address;
        }
        *IC += segment_entry->machine_code_content.line_count;
    }
    return SUCCESS;

}

void build_output_files(char *file_name, Table *code_segment, Table *data_segment, Table *symbols_table) {

    // Build ob file
    FILE *ob_file = NULL;
    ob_file = fopen("output.ob", "w");

    // Code segment
    for (int i = 0; i < code_segment->size; ++i) {
        SegmentEntry *segment = (SegmentEntry *) code_segment->entries[i].data;
        int start_address = segment->start_address;

        for (int j = 0; j < segment->machine_code_content.line_count; ++j) {
            MachineCodeLine line = segment->machine_code_content.lines[i];
            fprintf(ob_file, "%d %o\n", start_address + j, line.line);
        }

    }

    // Data segment
    for (int i = 0; i < data_segment->size; ++i) {
        SegmentEntry *segment = (SegmentEntry *) data_segment->entries[i].data;
        int start_address = segment->start_address;

        for (int j = 0; j < segment->machine_code_content.line_count; ++j) {
            MachineCodeLine line = segment->machine_code_content.lines[i];
            fprintf(ob_file, "%d %o\n", start_address + j, line.line);
        }

    }

    if (ob_file != NULL) {
        fclose(ob_file);
    }

    // Build ent file
    FILE *ent_file = NULL;
    for (int i = 0; i < symbols_table->size; ++i) {
        Symbol *symbol = (Symbol *) symbols_table->entries[i].data;
        if (symbol->type == ENTRY_SYMBOL) {
            if (ent_file == NULL) {
                ent_file = fopen("output.ent", "w");
            }
            fprintf(ent_file, "%s %d\n", symbol->label, symbol->address);
        }
    }
    if (ent_file != NULL) {
        fclose(ent_file);
    }

    // Build ext file
    FILE *ext_file = NULL;
    for (int i = 0; i < symbols_table->size; ++i) {
        Symbol *symbol = (Symbol *) symbols_table->entries[i].data;
        if (symbol->type == EXTERNAL_SYMBOL) {
            if (ext_file == NULL) {
                ext_file = fopen("output.ext", "w");
            }
            fprintf(ext_file, "%s %d\n", symbol->label, symbol->address);
        }
    }

    // Close the file if it was opened
    if (ext_file != NULL) {
        fclose(ext_file);
    }


}

int run_second_transaction(FileContent file_content, int *IC, int *DC, Table *code_segment, Table *data_segment,
                           Table *symbols_table) {

    int was_transaction_error = 0;
    ErrorNumber line_status;

    // Handle running on instruction lines (steps 2-9)
    for (int i = 0; i < file_content.line_count; i++) {

        line_status = SUCCESS;

        if (is_empty_string(file_content.lines[i].line)) {
            continue;
        }

        InstructionType instruction_type = get_instruction_type(file_content.lines[i]);
        switch (instruction_type) {

            // Handle directive instruction (steps 4-8)
            case (DIRECTIVE_INSTRUCTION): {
                DirectiveInstruction directive_instruction = parse_directive_instruction(file_content.lines[i]);
                if (directive_instruction.directive.type == ENTRY_DIRECTIVE) {
                    // Handle store directive instruction (steps 4-6)
                    line_status = handle_entry_directive_updates(symbols_table, directive_instruction);
                }
                break;
            }

                // Handle opcode instruction (steps 7)
            case (OPCODE_INSTRUCTION): {
                OpcodeInstruction opcode_instruction = parse_opcode_instruction(file_content.lines[i]);
                line_status = handle_opcodes_missing_addresses(IC, code_segment, symbols_table, opcode_instruction);
                break;
            }

            default:
                break;
        }

        if (line_status != SUCCESS) {
            was_transaction_error = 1;
            log_external_error(line_status, i, file_content.file_name);
        }
    }

    // Handle first transaction error check (step 14)
    if (was_transaction_error) {
        return EXTERNAL_FATAL_ERROR;
    }

    // Build output files
    build_output_files(file_content.file_name, code_segment, data_segment, symbols_table);
    return SUCCESS;
}



