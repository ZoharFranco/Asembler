/*
 ============================================================================
 Name        : errors_handler.c
 Author      : zoharfranco
 Version     :
 Copyright   : Your copyright notice
 Description : Errors handling file - to create function and declarations of errors handling
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "errors.h"
#include "errors_handling.h"


void log_internal_error(int error_code) {
	Error error = get_error_from_error_number(error_code);
	printf("\033[1;31m");
    printf("~~INTERNAL ERROR: ID:%d TYPE: %d~~ | %s\n", error.error_id, error.type, error.name);
    printf("\033[0m");
}

void log_external_error(int error_code, int line_number, char * file_name) {
	Error error = get_error_from_error_number(error_code);
	printf("\033[1;33m");
    printf("~~EXTERNAL ERROR: ID:%d TYPE: %d~~ in %s at line:%d | %s\n", error.error_id, error.type,
    file_name, line_number, error.name);
    printf("\033[0m");
}
