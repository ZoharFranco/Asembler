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


typedef struct {
    char *name;
    char *value;
} Macro;


void handle_macros(FileContent *file_content); // Handle macros in file content object - replace macros
int read_and_remove_macros(FileContent *file_content, Macro **macros, int *macro_count);

int replace_macros(FileContent *file_content, Macro *macros, int macro_count);

void free_macros(Macro *macros, int macro_count);

#endif
