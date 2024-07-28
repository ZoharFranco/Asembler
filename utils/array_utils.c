/*
 ============================================================================
 Name        : array_utils.c
 Author      : zoharfranco
 Version     :
 Copyright   : Your copyright notice
 Description : Array utils file, variety of functions on list \ with lists
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


void print_array(int * array, int length) {
	printf("\nElements of given array: \n");
	for (int i = 0; i < length; i++)
	{
		printf("%d ", array[i]);
	}
}

int get_index_in_array_int(int item, int * array, int array_size) {
    for (int i = 0; i < array_size; i++) {
        if (item == array[i]) return i;
    }
    return -1;
}


int get_index_in_array_string(char * item, char **array, int array_size) {
	for (int i = 0; i < array_size; ++i) {
	        if (strcmp(array[i], item) == 0) return i;
	}
	return -1;  // Return -1 if string not found
}

int is_in_array_int(int item, int * array, int array_size) {
	return (int)(get_index_in_array_int(item, array, array_size) != -1);
}

int is_in_array_string(char * item, char ** array, int array_size) {
    return (int)(get_index_in_array_string(item, array, array_size) != -1);
}




