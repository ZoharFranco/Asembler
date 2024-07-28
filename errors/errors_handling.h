#ifndef ERRORS_HANDLING_H
#define ERRORS_HANDLING_H

#include "../utils/file_utils.h"
#include "errors.h"

#define ERROR_LOG_MAX_SIZE 200

char *get_error_string_from_error_number(
        Error e); // Function that gets ErrorNumber error and return the relevant error description string
void log_external_error(int error_code, int line_number, char *file_name); // Print
void log_internal_error(int error_code);


#endif // ERRORS_HANDLING_H
