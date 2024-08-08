/*
 ============================================================================
 Name        : comments.c
 Author      : Zohar Franco
 Version     :
 Copyright   : Your copyright notice
 Description : Comments file - functions to handle comments in source files
 ============================================================================
 */


#include "comments.h"


int remove_comments(FileContent *file_content) {
    for (int i = 0; i < file_content->line_count; i++) {
        if (file_content->lines[i].line[0] == COMMENT_CHAR) file_content->lines[i].line = "";
    }
    return SUCCESS;
}
