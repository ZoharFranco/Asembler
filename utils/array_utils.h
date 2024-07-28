#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

/*!
 * Print integers array - Gets pointer to integer array and length
 * @param array: the array to print out
 * @param length: the length of the array
 */
void print_array(int *array, int length);


/*!
 * Return item in integers array - Gets item integer pointer to integer array and length (return -1 if not found)
 * @param item: the item to search
 * @param array: the array to search in
 * @param array_size: array size
 * @return the index of the item in the array
 */
int get_index_in_array_int(int item, int *array, int array_size);


/*!
 * Gets item integer pointer to integer array and length (return -1 if not found)
 * @param string: string to search
 * @param array: array to search in
 * @param array_size: array size
 * @return the index of the string in the array
 */
int get_index_in_array_string(char *string, char **array, int array_size);


/*!
 * Check if item in integers array - Gets item integer pointer to integer array and length
 * @param item: item to search
 * @param array: array to search in
 * @param array_size: array size
 * @return returns 1 if item is in the array and 0 otherwise
 */
int is_in_array_int(int item, int *array, int array_size);


/*!
 * Check if item in integers array - Gets item integer pointer to integer array and length
 * @param string : string to check
 * @param array : array to check in
 * @param array_size : the size of the array
 * @return returns 1 if item is in the array and 0 otherwise
 */
int is_in_array_string(char *string, char **array, int array_size);

#endif // ARRAY_UTILS_H