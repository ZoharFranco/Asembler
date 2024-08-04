#ifndef STRINGS_UTILS_H
#define STRINGS_UTILS_H


/*!
 *  Function that gets string and remove all its white spaces
 * @param str : str to remove its white spaces
 */
void remove_whitespace(char *str);

/*!
 * Function that gets string delimiter and pointer to count and return list of strings split and set count with the length
 * @param str : string to split
 * @param delimiter : delimiter to split by
 * @param count : count of items split
 * @return list of strings after split
 */
char **split_string(char *str, char *delimiter, int *count);

/*!
 * Function that get string and return if it empty
 * @param string : string to check
 * @return return 1 if string is empty and 0 otherwise
 */
int is_empty_string(char *string);


/*!
 * Function that gets 2 strings and concat them
 * @param str1:  first string
 * @param str2: second string
 * @return string that contain two strings together
 */
char *concat_strings(const char *str1, const char *str2);


/*!
 * Function that gets string of number and return if valid (just digits and start with +\-\none)
 * @param number_str : string that contain the number
 * @return return 1 if string is valid number and 0 otherwise
 */
int is_valid_number(const char *number_str);

/*!
 * Function that gets string of number and return string of the binary
 * @param number_str : number to get its binary string
 * @return string of binary bits chars of the number
 */
char *number_to_binary(char *number_str);

/*!
 * Function that gets list of string of numbers and return list of strings of the binary of each number
 * @param number_str_list
 * @param count
 * @return list of strings of binary ascii of each number
 */
char **numbers_to_binary_list(char **number_str_list, int count);

/*!
 * Function that int number and create a string of ascii bits
 * @param number
 * @return binary string of the number
 */
char *number_int_to_binary(unsigned int number);

/*!
 * Function that gets string of string ("after") and return if valid (string between "")
 * @param str : string to check
 * @return return 1 if string is valid and 0 otherwise
 */
int is_valid_string(const char *str);


char *format_number(unsigned int number, int length);

#endif // STRINGS_UTILS_H
