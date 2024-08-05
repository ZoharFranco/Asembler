#ifndef ERRORS_H
#define ERRORS_H

/*!
 * Enum of all error types
 */
typedef enum ErrorType {
    GENERAL, PRECOMPILATION, COMPILATION
} ErrorType;


/*!
 * Enum of all error numbers.
 * error numbers, every error number is a error instance that contain more data on the error.
 */
typedef enum ErrorNumber {

    // GENERAL
    SUCCESS,
    EXTERNAL_FATAL_ERROR,

    ALLOCATION_FAILED_TO_ALLOCATE_MEMORY,
    FILE_FAILED_TO_OPEN_FILE_FOR_READING,
    FILE_FAILED_TO_OPEN_NEW_FILE_FOR_WRITING,
    FILE_NAME_IS_MISSING,
    FILE_NAME_IS_TOO_LONG,

    // PRECOMPLATION

    PRECOMPILATION_ERROR,
    PRECOMPILATION_COMMENTS_ERROR,
    PRECOMPILATION_MACROS_ERROR,
    PRECOMPILATION_MACROS_READING_ERROR,
    PRECOMPILATION_MACROS_REPLACING_ERROR,
    ILLEGAL_MACRO_NAME,
    NOT_IN_FORMAT_MACRO_NAME,


    // FIRST_TRANSACTION
    FIRST_TRANSACTION_ERROR,
    INSTRUCTION_NOT_EXIST,
    ILLEGAL_LABEL,
    STRING_BAD_FORMAT,
    DATA_BAD_FORMAT,
    TOO_LONG_INSTRUCTION_LINE,

    // OPCODES
    OPCODE_ILLEGAL_NUMBER_OF_ARGS,
    OPCODE_ILLEGAL_SOURCE_ADDRESSING,
    OPCODE_ILLEGAL_DESTINATION_ADDRESSING,

    // SECOND_TRANSACTION

    SECOND_TRANSACTION_ERROR,

    // SYMBOLS
    SYMBOL_ALREADY_EXIST,
    ENTRY_SYMBOL_NOT_CREATED,
    USED_LABEL_NOT_EXIST,


    ILLEGAL_LABEL_LENGTH,
    ILLEGAL_INSTRUCTION_LENGTH,
    ILLEGAL_STRING_LENGTH,
    ILLEGAL_DATA_LENGTH,
    ILLEGAL_ARGS_LENGTH,


    LINE_IS_TOO_LONG,
    MACRO_WITHOUT_NAME_DEFINITION,
    MACRO_TEXT_AFTER_NAME_DEFINITION,
    SETTING_A_POSITION_IN_A_FILE_FAILED,
    MACRO_HAS_MORE_THAN_ONE_DEFINITION,


// PROCESSING_INSTRUCTIONS

// RUNNING_INSTRUCTIONS

} ErrorNumber;


/*!
 * Error object
 */
typedef struct Error {
    ErrorNumber error_id;
    ErrorType type;
    char *name;
    int is_external;
} Error;


/*!
 * Array of all errors
 */
extern Error ErrorsArray[];


/*!
 * Function that gets ErrorNumber error and return the relevant error
 * @param e : error number
 * @return error object of the wanted error number
 */
Error get_error_from_error_number(ErrorNumber e);


#endif // ERRORS_H
