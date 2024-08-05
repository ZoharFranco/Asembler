/*
 ============================================================================
 Name        : strings_utils.c
 Author      : zoharfranco
 Version     :
 Copyright   : Your copyright notice
 Description : Strings utils - functions to handle strings manipulation
 ============================================================================
 */


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


#include "../assembler.h"
#include "../errors/errors.h"
#include "strings_utils.h"
#include "errors_handling.h"

void remove_whitespace(char *str) {
    if (str[0] != '\0') {
        char *dst = str;
        while (*str) {
            if (!isspace((unsigned char) *str)) {
                *dst++ = *str;
            }
            str++;
        }
        *dst = '\0';
    } // Null-terminate the cleaned string
}

char **split_string(char *str, char *delimiter, int *count) {
    // Copy the input string to avoid modifying the original string
    char *str_copy = strdup(str);
    if (str_copy == NULL) {
        log_internal_error(ALLOCATION_FAILED_TO_ALLOCATE_MEMORY);
        return NULL;
    }

    // Count the number of tokens
    int token_count = 0;
    char *temp = strtok(str_copy, delimiter);
    while (temp != NULL) {
        token_count++;
        temp = strtok(NULL, delimiter);
    }

    // Allocate memory for the array of strings
    char **result = (char **) malloc(token_count * sizeof(char *));
    if (result == NULL) {
        free(str_copy);
        log_internal_error(ALLOCATION_FAILED_TO_ALLOCATE_MEMORY);
        return NULL;
    }

    // Reset the copy and split the string again
    strcpy(str_copy, str);
    int index = 0;
    temp = strtok(str_copy, delimiter);
    while (temp != NULL) {
        result[index] = strdup(temp);
        if (result[index] == NULL) {
            for (int i = 0; i < index; i++) {
                free(result[i]);
            }
            free(result);
            free(str_copy);
            log_internal_error(ALLOCATION_FAILED_TO_ALLOCATE_MEMORY);
            return NULL;
        }
        index++;
        temp = strtok(NULL, delimiter);
    }

    // Free the copy of the original string
    free(str_copy);

    // Set the count of tokens
    *count = token_count;

    return result;
}

int is_empty_string(char *str) {
    if (str == NULL) return 1;
    while (*str != '\0') {
        if (!isspace((unsigned char) *str)) {
            return 0;
        }
        str++;
    }
    return 1;
}

char *concat_strings(const char *str1, const char *str2) {
    size_t str1_len = strlen(str1);
    size_t str2_len = strlen(str2);

    char *result = (char *) malloc(str1_len + str2_len + 1);

    strcpy(result, str1);
    strcat(result, str2);

    return result;
}


int is_valid_number(const char *number_str) {
    if (number_str[0] == '+' || number_str[0] == '-') {
        number_str++;
    }
    if (*number_str == '\0') {
        return 0;
    }

    while (*number_str) {
        if (!isdigit((unsigned char) *number_str)) {
            return 0;
        }
        number_str++;
    }
    return 1;
}

char *number_to_binary(char *number_str) {
    int number = atoi(number_str);
    char *bits = malloc(LINE_BITS_LENGTH + 1 * sizeof(char));
    if (bits == NULL) {
        log_internal_error(ALLOCATION_FAILED_TO_ALLOCATE_MEMORY);
        return NULL;
    }
    for (int i = LINE_BITS_LENGTH - 1; i >= 0; --i) {
        bits[LINE_BITS_LENGTH - 1 - i] = ((number >> i) & 1) ? '1' : '0';
    }
    bits[LINE_BITS_LENGTH] = '\0';
    return bits;
}


int is_valid_string(const char *str) {
    size_t len = strlen(str);
    if (len < 2) {
        return 0;
    }
    return (str[0] == '"' && str[len - 1] == '"');
}


int is_alphabet_digits_no_spaces_string(const char *str) {
    while (*str) {
        if (!isalnum(*str) && *str != '_') {
            return 0; // Return false if a character is not alphanumeric or an underscore
        }
        str++;
    }
    return 1; // Return true if all characters are valid
}

void strip_newline(char *str) {
    char *pos;
    if ((pos = strchr(str, '\n')) != NULL) {
        *pos = '\0';
    }
}