/*
 ============================================================================
 Name        : stack.c
 Author      : zoharfranco
 Version     :
 Copyright   : Your copyright notice
 Description : Stack file, stack struct and useful stack functions
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "../errors/errors_handling.h"

#include "table.h"


Table * init_table() {
	Table *table = (Table *)malloc(sizeof(Table));
		if (table == NULL) {
			return ALLOCATION_FAILED_TO_ALLOCATE_MEMORY;
		}

		table->entries = (TableEntry *)malloc(1 * sizeof(TableEntry));
		if (table->entries == NULL) {
			free(table);
			return ALLOCATION_FAILED_TO_ALLOCATE_MEMORY;
		}

		table->size = 0;
		table->capacity = 1;

		return table;
}

int add_entry(Table *table, void *data, char* key, size_t data_size) {
    if (table->entries == NULL) {
        return ALLOCATION_FAILED_TO_ALLOCATE_MEMORY;
    }

    if (table->size == table->capacity) {
        table->capacity *= 2;
        TableEntry *new_entries = (TableEntry *)realloc(table->entries, table->capacity * sizeof(TableEntry));
        if (new_entries == NULL) {
            return ALLOCATION_FAILED_TO_ALLOCATE_MEMORY;
        }
        table->entries = new_entries;
    }

    table->entries[table->size].data = malloc(data_size);
    if (table->entries[table->size].data == NULL) {
        return ALLOCATION_FAILED_TO_ALLOCATE_MEMORY;
    }

    memcpy(table->entries[table->size].data, data, data_size);

    table->entries[table->size].key = strdup(key);
    if (table->entries[table->size].key == NULL) {
        free(table->entries[table->size].data);
        return ALLOCATION_FAILED_TO_ALLOCATE_MEMORY;
    }

    table->size++;
    return SUCCESS;
}

void free_table(Table *table) {
    for (int i = 0; i < table->size; i++) {
        free(table->entries[i].data);
        free(table->entries[i].key);
    }
    free(table->entries);
    table->entries = NULL;
    table->size = 0;
    table->capacity = 0;
}

TableEntry * get_entry_by_key(Table *table, char* key) {
	for (int i = 0; i < table->size; i++) {
	        if (strcmp(table->entries[i].key, key) == 0) return &table->entries[i];
	    }
	return -1;
}

int is_key_exist(Table *table, char* key){
	for (int i = 0; i < table->size; i++) {
			if (strcmp(table->entries[i].key, key) == 0) return 1;
		}
	return 0;
}

