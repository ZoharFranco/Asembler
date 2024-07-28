#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#define MAX_LINE_LENGTH 1024
#define INITIAL_LINES_IN_FILE 128

#include "../errors/errors.h"


/*!
 * File line object
 */
typedef struct {
    int line_number;
    char *line;
} FileLine;


/*!
 * File content object contain file content as lines
 */
typedef struct {
    char *file_name;
    FileLine *lines;
    int line_count;
    ErrorNumber error;
} FileContent;


/*!
 * Function that gets file path and read its content to a file content object
 * @param file_path: file path to write from
 * @return the file content object that represent the file
 */
FileContent read_file_content(char *file_path);


/*!
 * Function that gets file content and write its lines to a file
 * @param file_content: file content object to use its lines
 * @param file_path: file path to write into
 * @return status of the operation
 */
int write_file_content(FileContent file_content, char *file_path);


/*!
 * Free file content object (deep)
 * @param file_content: the file content object to free
 */
void free_file_content(FileContent file_content);


#endif // FILE_UTILS_H
