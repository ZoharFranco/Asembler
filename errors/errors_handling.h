#ifndef ERRORS_HANDLING_H
#define ERRORS_HANDLING_H

#include "../utils/file_utils.h"
#include "errors.h"

#define ERROR_LOG_MAX_SIZE 200

/*!
 * Log an external error that occurred
 * @param error_code : error code to log
 * @param line_number : the line number that relevant to the error
 * @param file_name : the name of the file that was processed during error
 */
void log_external_error(int error_code, int line_number, char *file_name); // Print


/*!
 * Log an internal error that occurred
 * @param error_code : error code to log
 */
void log_internal_error(int error_code);


#endif // ERRORS_HANDLING_H
