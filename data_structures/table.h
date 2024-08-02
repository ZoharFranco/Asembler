#ifndef TABLE_H
#define TABLE_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*!
 * TableEntry struct
 * key: string as key
 * data: pointer to that wanted save data of entry
 */
typedef struct {
    char *key;
    void *data;
} TableEntry;


/*!
 * Table struct
 * entries: list of entries - TableEntry
 * size: current number of entries
 * capacity: max number of entries
 */
typedef struct {
    TableEntry *entries;
    int size;
    int capacity;
} Table;


/*!
 * Function to initialize the table
 * @return the new table
 */
Table *init_table();


/*!
 * Function to add an entry to the table
 * @param table : table to add to
 * @param data : data of the new entry
 * @param key : key of the new entry
 * @param data_size : the data size
 * @return status of operation
 */
int add_entry(Table *table, void *data, char *key, size_t data_size);


/*!
 * Function to get an entry from the table
 * @param table : table to get entry from
 * @param key : key to get entry by
 * @return the entry that associated with the key
 */
TableEntry *get_entry_by_key(Table *table, char *key);


/*!
 * Function to check if key exist
 * @param table : table to check
 * @param key : key to check if exist
 * @return returns 1 if key is in the table keys and 0 otherwise
 */
int is_key_exist(Table *table, char *key);


/*!
 * Function to free the table
 * @param table : table to free
 */
void free_table(Table *table);



#endif // TABLE_H
