#ifndef MACRO_H
#define MACRO_H

#include <stdio.h>
#include "../utils/file_utils.h"
#include "../errors/errors_handling.h"

#define MACRO_START_LABEL "macr"
#define MACRO_START_LABEL_LENGTH 4

#define MACRO_END_LABEL "end_macr"
#define MACRO_END_LABEL_LENGTH 8

#define MACRO_MAX_LENGTH 150

/*!
 * Macro struct
 * name: string of the name of the macro
 * value: string of the value of the macro
 */
typedef struct {
    char *name;
    char *value;
} Macro;


/*!
 * Handle macros in file content object - replace macros by their desire value
 * @param file_content
 */
void handle_macros(FileContent *file_content);


/*!
 * Read the macros name and values
 * @param file_content : file content to replace macros inside it's content
 * @param macros : the list of macros to free
 * @param macro_count : the length of the macros list
 * @return operation status
 */
int read_and_remove_macros(FileContent *file_content, Macro **macros, int *macro_count);


/*!
 * Replace macros with the wanted value
 * @param file_content : file content to replace macros inside it's content
 * @param macros : the list of macros to free
 * @param macro_count : the length of the macros list
 * @return operation status
 */
int replace_macros(FileContent *file_content, Macro *macros, int macro_count);


/*!
 * Free macros
 * @param macros : the list of macros to free
 * @param macro_count : the length of the macros list
 */
void free_macros(Macro *macros, int macro_count);

#endif
