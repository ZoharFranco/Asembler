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
 * @return 1 if string is empty and 0 otherwise
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
 * @return 1 if string is valid number and 0 otherwise
 */
int is_valid_number(const char *number_str);


/*!
 * Function that gets string of string ("after") and return if valid (string between "")
 * @param str : string to check
 * @return 1 if string is valid and 0 otherwise
 */
int is_valid_string(const char *str);


/*!
 * Function to check if string is consists of alphabets digits and _ chars only
 * @param str : string to check
 * @return 1 if string is valid and 0 otherwise
 */
int is_alphabet_digits_no_spaces_string(const char *str);

void strip_newline(char *str);


#endif // STRINGS_UTILS_H
