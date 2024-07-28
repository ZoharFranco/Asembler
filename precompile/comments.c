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

#include "comments.h"


int remove_comments(FileContent *file_content) {
    for (int i = 0; i < file_content->line_count; i++) {
        if (file_content->lines[i].line[0] == COMMENT_CHAR) file_content->lines[i].line = "";
    }
    return SUCCESS;
}
