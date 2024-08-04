/*
 ============================================================================
 Name        : file_utils.c
 Author      : zoharfranco
 Version     :
 Copyright   : Your copyright notice
 Description : File utils file, variety of functions on files \ with files contents
 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_utils.h"


FileContent read_file_content(char *file_path) {
    FileContent file_content;
    file_content.line_count = 0;
    file_content.error = 0;
    file_content.file_name = file_path;

    file_content.lines = (FileLine *) malloc(INITIAL_LINES_IN_FILE * sizeof(FileLine));
    if (file_content.lines == NULL) {
        file_content.error = ALLOCATION_FAILED_TO_ALLOCATE_MEMORY;
        return file_content;
    }

    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        free(file_content.lines);
        file_content.error = FILE_FAILED_TO_OPEN_FILE_FOR_READING;
        return file_content;
    }

    char buffer[MAX_LINE_LENGTH];
    int current_array_size = INITIAL_LINES_IN_FILE;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (file_content.line_count >= current_array_size) {
            current_array_size *= 2;
            FileLine *new_lines = (FileLine *) realloc(file_content.lines, current_array_size * sizeof(FileLine));
            if (new_lines == NULL) {
                for (int i = 0; i < file_content.line_count; i++) {
                    free(file_content.lines[i].line);
                }
                free(file_content.lines);
                fclose(file);
                file_content.error = ALLOCATION_FAILED_TO_ALLOCATE_MEMORY;
                return file_content;
            }
            file_content.lines = new_lines;
        }

        file_content.lines[file_content.line_count].line = strdup(buffer);
        file_content.lines[file_content.line_count].line_number = file_content.line_count;
        if (file_content.lines[file_content.line_count].line == NULL) {
            for (int i = 0; i < file_content.line_count; i++) {
                free(file_content.lines[i].line);
            }
            free(file_content.lines);
            fclose(file);
            file_content.error = ALLOCATION_FAILED_TO_ALLOCATE_MEMORY;
            return file_content;
        }

        file_content.line_count++;
    }

    fclose(file);
    return file_content;
}

int write_file_content(FileContent file_content, char *file_path) {
    FILE *file = fopen(file_path, "w");
    if (file == NULL) {
        return FILE_FAILED_TO_OPEN_NEW_FILE_FOR_WRITING;
    }

    for (int i = 0; i < file_content.line_count; i++) {
        fprintf(file, "%s", file_content.lines[i].line);
    }

    fclose(file);
    return SUCCESS;
}

void free_file_content(FileContent file_content) {
    for (int i = 0; i < file_content.line_count; i++) {
        FileLine line = file_content.lines[i];
        free(line.line);
    }
    free(file_content.lines);
}


void add_line_to_file_start(const char *file_path, const char *new_line) {
    FILE *file = fopen(file_path, "r");


    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *content = malloc(file_size + 1);
    fread(content, 1, file_size, file);
    content[file_size] = '\0';
    fclose(file);


    file = fopen(file_path, "w");

    fprintf(file, "%s\n", new_line);
    fprintf(file, "%s", content);
    fclose(file);
    free(content);
}