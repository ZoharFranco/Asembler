#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include "../utils/file_utils.h"
#include "../data_structures/table.h"

#include "../commands/opcodes.h"
#include "../commands/directives.h"
#include "../commands/instructions.h"


// First transaction flow

// handle 6-7 lines
int handle_store_directive_first_transaction(int *DC, Table *data_segment, Table *symbols_table,
                                             DirectiveInstruction directive_instruction);

// handle 9-10 lines
int handle_link_directive_first_transaction(Table *symbols_table, DirectiveInstruction directive_instruction);

// handle 11-13 lines
int handle_opcode_instruction_first_transaction(int *IC, Table *code_segment, Table *symbols_table,
                                                OpcodeInstruction opcode_instruction);

void handle_data_segment_addresses_updates(const int *IC, Table *symbols_table);

// Run the first transaction by the project algorithm
int run_first_transaction(FileContent file_content, int *IC, int *DC, Table *code_segment, Table *data_segment,
                          Table *symbols_table);


// Second transaction flow

void build_output_files(int *IC, int *DC, Table *code_segment, Table *data_segment, Table *symbols_table);

int handle_entry_directive_updates(Table *symbol_table, DirectiveInstruction directive_instruction);

int handle_opcodes_missing_addresses(int *IC, Table *code_segment, Table *symbol_table,
                                     OpcodeInstruction opcode_instruction);

// Run the second transaction by the project algorithm
int run_second_transaction(FileContent file_content, int *IC, int *DC, Table *code_segment, Table *data_segment,
                           Table *symbol_table);

#endif // TRANSACTIONS_H
