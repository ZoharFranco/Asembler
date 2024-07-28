#ifndef SYMBOLS_H
#define SYMBOLS_H


#include "../data_structures/table.h"


/*!
 * Enum of all symbol types
 */
typedef enum {
    CODE_SYMBOL, DATA_SYMBOL, ENTRY_SYMBOL, EXTERNAL_SYMBOL, SYMBOL_TYPES_LENGTH
} SymbolType;


/*!
 * Symbol struct contain string label, SymbolType type, and address of the symbol
 */
typedef struct Symbol {
    char *label;
    SymbolType type;
    int address;
} Symbol;


/*!
 * Init table of all symbols
 * @return pointer to the table
 */
Table *init_symbol_table();


/*!
 * Add symbol to a symbols table
 * @param symbols_table: the symbols table to insert to
 * @param symbol: the symbol to add
 * @return status of operation
 */
int add_symbol(Table *symbols_table, Symbol *symbol);


/*!
 *
 * @param symbols_table
 * @param label
 * @param new_type
 */
void update_symbol_type(Table *symbols_table, char *label, SymbolType new_type);


/*!
 * Function that gets label and return the associated symbol
 * @param symbols_table: the symbols table to search in
 * @param label: the label to find the associated symbol
 * @return The symbol
 */
Symbol *get_symbol_by_label(Table *symbols_table, char *label);


/*!
 * Function that gets label and return if exist associated symbol
 * @param symbols_table: the symbols table to search in
 * @param label: the label to find if the associated symbol exist
 * @return returns 1 if label is in the symbol and 0 otherwise
 */
int is_symbol_label_exist(Table *symbols_table, char *label);


#endif // SYMBOLS_H
