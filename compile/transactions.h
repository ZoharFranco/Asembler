#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include "../utils/file_utils.h"
#include "../data_structures/table.h"

#include "../commands/opcodes.h"
#include "../commands/directives.h"
#include "../commands/instructions.h"

#define OBJECT_FILE_EXTENSION ".ob"
#define ENTRY_FILE_EXTENSION ".ent"
#define EXTERN_FILE_EXTENSION ".ext"
#define MASK_LAST_5_OCTAL_DIGITS 077777u


// First transaction flow

/*!
 * Function that handles first transaction 6-7 lines - store directive handling
 * @param DC : Data counter
 * @param data_segment : Data segment of all the data machine code that the assembly code create
 * @param symbols_table : Symbol table with symbols and their address
 * @param directive_instruction : The store directive instruction to handle
 * @return the status of the operation
 */
int handle_store_directive_first_transaction(int *DC, Table *data_segment, Table *symbols_table,
                                             DirectiveInstruction directive_instruction);


/*!
 * Function that handles first transaction, 9-10 lines - link directive handling
 * @param symbols_table : Symbol table with symbols and their address
 * @param directive_instruction : The link directive instruction to handle
 * @return the status of the operation
 */
int handle_link_directive_first_transaction(Table *symbols_table, DirectiveInstruction directive_instruction);


/*!
 * Function that handles first transaction, 11-13 lines - link directive handling
 * @param IC : Instruction counter
 * @param code_segment : Code segment of all the machine code that the assembly code create
 * @param symbols_table : Symbol table with symbols and their address
 * @param opcode_instruction : The opcode instruction to handle
 * @return the status of the operation
 */
int handle_opcode_instruction_first_transaction(int *IC, Table *code_segment, Table *symbols_table,
                                                OpcodeInstruction opcode_instruction);


/*!
 * Function that handles first transaction, 15 line - data segment addresses update by final IC
 * @param IC : Instruction counter
 * @param symbols_table : Symbol table with symbols and their address
 * @param data_segment : Data segment of all the data machine code that the assembly code create
 */
void handle_data_segment_addresses_updates(const int *IC, Table *symbols_table, Table *data_segment);


/*!
 * Run the first transaction by the project algorithm
 * @param file_content : the file content object to compile
 * @param IC : Instruction counter
 * @param DC : Data counter
 * @param code_segment : Code segment of all the machine code that the assembly code create
 * @param data_segment : Data segment of all the data machine code that the assembly code create
 * @param symbols_table : Symbol table with symbols and their address
 * @return the status of the operation
 */
int run_first_transaction(FileContent file_content, int *IC, int *DC, Table *code_segment, Table *data_segment,
                          Table *symbols_table);


// Second transaction flow

/*!
 * Function that handles second transaction, steps 4-6 - handle entry directive updates in symbol table
 * @param symbols_table : Symbol table with symbols and their address
 * @param directive_instruction : The link directive instruction to handle its symbols updates
 * @return the status of the operation
 */
int handle_entry_directive_updates(Table *symbol_table, DirectiveInstruction directive_instruction);


/*!
 * Function that handles second transaction, step 7 - handle opcode missing labels addresses updates
 * @param IC : Instruction counter
 * @param code_segment : Code segment of all the machine code that the assembly code create
 * @param symbols_table : Symbol table with symbols and their address
 * @param opcode_instruction : The opcode instruction to handle
 * @return the status of the operation
 */
int handle_opcodes_missing_addresses(int *IC, Table *code_segment, Table *symbol_table,
                                     OpcodeInstruction opcode_instruction);


/*!
 *  Function that handles second transaction, step 10 - build the ob, ent, ext files based on segments and symbols table
 * @param file_name : file name of the processed file
 * @param code_segment : Code segment of all the machine code that the assembly code create
 * @param data_segment : Data segment of all the data machine code that the assembly code create
 * @param symbols_table : Symbol table with symbols and their address
 */
void build_output_files(char *file_name, Table *code_segment, Table *data_segment, Table *symbols_table);


/*!
 * Run the second transaction by the project algorithm
 * @param file_content : the file content object to compile
 * @param IC : Instruction counter
 * @param DC : Data counter
 * @param code_segment : Code segment of all the machine code that the assembly code create
 * @param data_segment : Data segment of all the data machine code that the assembly code create
 * @param symbols_table : Symbol table with symbols and their address
 * @return the status of the operation
 */
int run_second_transaction(FileContent file_content, int *IC, int *DC, Table *code_segment, Table *data_segment,
                           Table *symbol_table);


#endif // TRANSACTIONS_H
