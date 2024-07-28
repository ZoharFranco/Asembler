#ifndef TABLE_H
#define TABLE_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    void *data;
} TableEntry;

typedef struct {
    TableEntry *entries;
    int size;
    int capacity;
} Table;


Table *init_table(); // Function to initialize the table
int add_entry(Table *table, void *data, char *key, size_t data_size); // Function to add an entry to the table
TableEntry *get_entry_by_key(Table *table, char *key); // Function to get an entry from the table
int is_key_exist(Table *table, char *key);// Function to check if key exist
void free_table(Table *table); // Function to free the table



#endif // TABLE_H
