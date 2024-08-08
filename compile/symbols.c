/*
 ============================================================================
 Name        : symbols.c
 Author      : Zohar Franco
 Version     :
 Copyright   : Your copyright notice
 Description : Symbols file - to create function and declarations of errors handling
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "../data_structures/table.h"

#include "symbols.h"

Table *init_symbol_table() {
    return init_table();
}

int add_symbol(Table *symbols_table, Symbol *symbol) {
    return add_entry(symbols_table, symbol, symbol->label, sizeof(Symbol));
}

void update_symbol_type(Table *symbols_table, char *label, SymbolType new_type) {
    Symbol *symbol = get_symbol_by_label(symbols_table, label);
    symbol->type = new_type;
}

Symbol *get_symbol_by_label(Table *symbols_table, char *label) {
    return (Symbol *) (get_entry_by_key(symbols_table, label)->data);
}

int is_symbol_label_exist(Table *symbols_table, char *label) {
    return is_key_exist(symbols_table, label);
}
