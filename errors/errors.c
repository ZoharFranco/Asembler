/*
 ============================================================================
 Name        : errors.c
 Author      : zoharfranco
 Version     :
 Copyright   : Your copyright notice
 Description : Errors file - to create function and declarations of errors utils
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "errors.h"


Error ErrorsArray[] = {
        {SUCCESS,                                  GENERAL,        "Success",                                       0},
        {EXTERNAL_FATAL_ERROR,                     GENERAL,        "External fatal error",                          0},

        {ALLOCATION_FAILED_TO_ALLOCATE_MEMORY,     GENERAL,        "Allocation failed to allocate memory",          0},
        {FILE_FAILED_TO_OPEN_FILE_FOR_READING,     GENERAL,        "File failed to open file for reading",          0},
        {FILE_FAILED_TO_OPEN_NEW_FILE_FOR_WRITING, GENERAL,        "File failed to open file for writing",          0},
        {FILE_NAME_IS_MISSING,                     GENERAL,        "File name is missing",                          0},
        {FILE_NAME_IS_TOO_LONG,                    GENERAL,        "File name is too long",                         0},

        {PRECOMPILATION_ERROR,                     PRECOMPILATION, "Precompilation generic error",                  0},
        {PRECOMPILATION_COMMENTS_ERROR,            PRECOMPILATION, "Precompilation comments error",                 0},
        {PRECOMPILATION_MACROS_ERROR,              PRECOMPILATION, "Precompilation macros error",                   0},
        {PRECOMPILATION_MACROS_READING_ERROR,      PRECOMPILATION, "Precompilation macros reading error",           0},
        {PRECOMPILATION_MACROS_REPLACING_ERROR,    PRECOMPILATION, "Precompilation macros replacing error",         0},
        {ILLEGAL_MACRO_NAME,                       PRECOMPILATION, "Illegal macro name",                            1},


        {FIRST_TRANSACTION_ERROR,                  COMPILATION,    "First transaction error",                       0},
        {INSTRUCTION_NOT_EXIST,                    COMPILATION,    "Instruction not exist",                         1},
        {ILLEGAL_LABEL,                            COMPILATION,    "Illegal label name",                            1},
        {STRING_BAD_FORMAT,                        COMPILATION,    "Illegal string format",                         1},
        {DATA_BAD_FORMAT,                          COMPILATION,    "Illegal data format",                           1},

        {OPCODE_ILLEGAL_NUMBER_OF_ARGS,            COMPILATION,    "Opcode illegal number of args",                 1},
        {OPCODE_ILLEGAL_SOURCE_ADDRESSING,         COMPILATION,    "Opcode illegal source addressing",              1},
        {OPCODE_ILLEGAL_DESTINATION_ADDRESSING,    COMPILATION,    "Opcode illegal destination addressing",         1},
        {SYMBOL_ALREADY_EXIST,                     COMPILATION,    "Symbol label already exist in symbols table",   1},
        {ENTRY_SYMBOL_NOT_CREATED,                 COMPILATION,    "Entry symbol label not exist in symbols table", 1},


};


Error get_error_from_error_number(ErrorNumber e) {
    return ErrorsArray[e];
}
