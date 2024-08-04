/*
 ============================================================================
 Name        : assembler.c
 Author      : zohar franco
 Version     :
 Copyright   : Your copyright notice
 Description : Main code, Ansi-style
 ============================================================================
 */


#include "utils/file_utils.h"
#include "utils/strings_utils.h"
#include "errors/errors.h"
#include "errors/errors_handling.h"


#include "precompile/comments.h"
#include "precompile/macros.h"

#include "compile/symbols.h"
#include "compile/segments.h"
#include "compile/transactions.h"


int precompile(char *src_path) {

    char *as_path = concat_strings(src_path, ".as");
    FileContent file_content = read_file_content(as_path);
    if (file_content.error) {
        log_internal_error(file_content.error);
        return PRECOMPILATION_ERROR;
    }

    remove_comments(&file_content);
    handle_macros(&file_content);
    if (file_content.error) {
        log_internal_error(file_content.error);
        return PRECOMPILATION_MACROS_ERROR;
    }

    char *dst_path = concat_strings(src_path, ".am");
    write_file_content(file_content, dst_path);

//    free_file_content(file_content);

    return SUCCESS;
}


int compile(char *src_path) {

    int IC = 0;
    int DC = 0;
    Table *data_segment = init_segment_table();
    Table *code_segment = init_segment_table();
    Table *symbol_table = init_symbol_table();

    src_path = concat_strings(src_path, ".am");
    FileContent file_content = read_file_content(src_path);
    int first_transaction_status = run_first_transaction(file_content, &IC, &DC, code_segment, data_segment,
                                                         symbol_table);
    if (first_transaction_status) {
        log_internal_error(first_transaction_status);
        return PRECOMPILATION_MACROS_ERROR;
    }

    int second_transaction_status = run_second_transaction(file_content, &IC, &DC, code_segment, data_segment,
                                                           symbol_table);
    if (second_transaction_status) {
        log_internal_error(second_transaction_status);
        return PRECOMPILATION_MACROS_ERROR;
    }

    free_file_content(file_content);
    free_table(data_segment);
    free_table(code_segment);
    free_table(symbol_table);

    return SUCCESS;
}


int main(int argc, char *argv[]) {

    char *src_path = "try";

    ErrorNumber precompilation_status = precompile(src_path);
    if (precompilation_status) {
        log_internal_error(precompilation_status);
        return 1;
    }

    ErrorNumber compilation_status = compile(src_path);
    if (compilation_status) {
        log_internal_error(compilation_status);
        return 1;
    }

}

