#ifndef COMMENTS_H
#define COMMENTS_H

#define COMMENT_CHAR ';'

#include "../utils/file_utils.h"

/*!
 * Remove comments by ; char from input file_content object
 * @param file_content : file content to remove content from it's content
 * @return status of the operation
 */
int remove_comments(FileContent *file_content);

#endif // COMMENTS_H
