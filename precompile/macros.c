

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macros.h"
#include "instructions.h"
#include "strings_utils.h"


int read_and_remove_macros(FileContent *file_content, Macro **macros, int *macro_count) {
    int capacity = INITIAL_LINES_IN_FILE;
    *macro_count = 0;
    *macros = (Macro *) malloc(capacity * sizeof(Macro));

    if (*macros == NULL) {
        return ALLOCATION_FAILED_TO_ALLOCATE_MEMORY;
    }

    for (int i = 0; i < file_content->line_count; i++) {
        char *line = file_content->lines[i].line;
        if (strncmp(line, MACRO_START_LABEL, MACRO_START_LABEL_LENGTH) == 0) {
            char *name = strtok(line + MACRO_START_LABEL_LENGTH, " ");
            char *other_line = line + MACRO_START_LABEL_LENGTH + 1;
            if (strcmp(other_line, name) != 0) {
                log_external_error(NOT_IN_FORMAT_MACRO_NAME, i, file_content->file_name);
                return EXTERNAL_FATAL_ERROR;
            }
            strip_newline(name);
            char value[MACRO_MAX_LENGTH] = "";

            // Read and remove value until "endmacro" is found
            file_content->lines[i].line = "";
            i++;
            while (i < file_content->line_count &&
                   strncmp(file_content->lines[i].line, MACRO_END_LABEL, MACRO_END_LABEL_LENGTH) != 0) {
                strcat(value, file_content->lines[i].line);
                file_content->lines[i].line = "";
                i++;
            }
            file_content->lines[i].line = "";

            // Insert new macros
            if (name && strlen(value) > 0) {
                if (*macro_count >= capacity) {
                    capacity *= 2;
                    Macro *new_macros = (Macro *) realloc(*macros, capacity * sizeof(Macro));
                    if (new_macros == NULL) {
                        free(*macros);
                        return ALLOCATION_FAILED_TO_ALLOCATE_MEMORY;
                    }
                    *macros = new_macros;
                }

                if (is_empty_string(name) || !is_valid_label(name)) {
                    log_external_error(ILLEGAL_MACRO_NAME, i, file_content->file_name);
                    return EXTERNAL_FATAL_ERROR;
                }

                (*macros)[*macro_count].name = strdup(name);
                (*macros)[*macro_count].value = strdup(value);

                if ((*macros)[*macro_count].name == NULL || (*macros)[*macro_count].value == NULL) {
                    free(*macros);
                    return ALLOCATION_FAILED_TO_ALLOCATE_MEMORY;
                }
                (*macro_count)++;
            }
        }
    }

    return SUCCESS;
}

int replace_macros(FileContent *file_content, Macro *macros, int macro_count) {
    for (int i = 0; i < file_content->line_count; i++) {
        for (int j = 0; j < macro_count; j++) {
            char *pos;
            while ((pos = strstr(file_content->lines[i].line, macros[j].name)) != NULL) {
                int len_before = (int) (pos - file_content->lines[i].line);
                int len_name = (int) strlen(macros[j].name);
                int len_value = (int) strlen(macros[j].value);
                int len_after = (int) strlen(pos + len_name);

                char *new_line = (char *) malloc(len_before + len_value + len_after + 1);
                if (new_line == NULL) {
                    return ALLOCATION_FAILED_TO_ALLOCATE_MEMORY;
                }

                strncpy(new_line, file_content->lines[i].line, len_before);
                strcpy(new_line + len_before, macros[j].value);
                strcpy(new_line + len_before + len_value, pos + len_name);

                free(file_content->lines[i].line);
                file_content->lines[i].line = new_line;
            }
        }
    }
    return SUCCESS;
}

void free_macros(Macro *macros, int macro_count) {
    for (int i = 0; i < macro_count; i++) {
        free(macros[i].name);
        free(macros[i].value);
    }
    free(macros);
}

void handle_macros(FileContent *file_content) {
    file_content->error = SUCCESS;
    int macro_count;
    Macro *macros;

    int read_status = read_and_remove_macros(file_content, &macros, &macro_count);
    if (read_status != SUCCESS) {
        if (get_error_from_error_number(read_status).is_external == 0) {
            log_internal_error(read_status);
        }
        file_content->error = PRECOMPILATION_MACROS_READING_ERROR;
    }

    int replace_status = replace_macros(file_content, macros, macro_count);
    if (replace_status != SUCCESS) {
        if (get_error_from_error_number(read_status).is_external == 0) {
            log_internal_error(replace_status);
        }
        file_content->error = PRECOMPILATION_MACROS_REPLACING_ERROR;
    }

    free_macros(macros, macro_count);

}

