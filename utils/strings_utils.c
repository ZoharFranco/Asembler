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

#include "../assembler.h"
#include "../errors/errors.h"
#include "strings_utils.h"
#include "errors_handling.h"

void remove_whitespace(char *str) {
    char *dst = str;
    while (*str) {
        if (!isspace((unsigned char) *str)) {
            *dst++ = *str;
        }
        str++;
    }
    *dst = '\0';  // Null-terminate the cleaned string
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

char **numbers_to_binary_list(char **number_str_list, int count) {
    char **binary_list = malloc(count * sizeof(char *));
    if (binary_list == NULL) {
        log_internal_error(ALLOCATION_FAILED_TO_ALLOCATE_MEMORY);
        return NULL;
    }
    for (int i = 0; i < count; ++i) {
        binary_list[i] = number_to_binary(number_str_list[i]);
        if (binary_list[i] == NULL) {
            // Cleanup allocated memory on error
            for (int j = 0; j < i; ++j) {
                free(binary_list[j]);
            }
            free(binary_list);
            return NULL;
        }
    }
    return binary_list;
}

int is_valid_string(const char *str) {
    size_t len = strlen(str);
    if (len < 2) {
        return 0;
    }
    return (str[0] == '"' && str[len - 1] == '"');
}

char *char_to_bits(char ch) {
    char *bits = malloc((LINE_BITS_LENGTH + 1) * sizeof(char));
    if (bits == NULL) {
        log_internal_error(ALLOCATION_FAILED_TO_ALLOCATE_MEMORY);
        return NULL;
    }
    for (int i = LINE_BITS_LENGTH - 1; i >= 0; --i) {
        bits[LINE_BITS_LENGTH - 1 - i] = ((ch >> i) & 1) ? '1' : '0';
    }
    bits[LINE_BITS_LENGTH] = '\0';
    return bits;
}


char **get_string_ascii_values_as_bits(const char *str) {
    size_t len = strlen(str);
    char **ascii_bits = malloc(len * sizeof(char *));
    if (ascii_bits == NULL) {
        log_internal_error(ALLOCATION_FAILED_TO_ALLOCATE_MEMORY);
        return NULL;
    }

    size_t idx = 0;
    for (size_t i = 1; i < len - 1; ++i) {
        ascii_bits[idx++] = char_to_bits(str[i]);
        if (ascii_bits[idx - 1] == NULL) {
            for (size_t j = 0; j < idx - 1; ++j) {
                free(ascii_bits[j]);
            }
            free(ascii_bits);
            log_internal_error(ALLOCATION_FAILED_TO_ALLOCATE_MEMORY);
            return NULL;
        }
    }
    ascii_bits[idx] = NULL;
    return ascii_bits;
}


char *number_int_to_binary(int number) {
    char *binary = malloc((LINE_BITS_LENGTH + 1) * sizeof(char)); // +1 for null terminator
    if (binary == NULL) {
        log_internal_error(ALLOCATION_FAILED_TO_ALLOCATE_MEMORY);
        return NULL;
    }

    // Fill the binary array with '0' and '1' based on the bits in the number
    for (int i = LINE_BITS_LENGTH - 1; i >= 0; --i) {
        binary[LINE_BITS_LENGTH - 1 - i] = (number & (1 << i)) ? '1' : '0';
    }
    binary[LINE_BITS_LENGTH] = '\0'; // Null-terminate the string

    return binary;
}
