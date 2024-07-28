/*
 ============================================================================
 Name        : opcode.c
 Author      : zoharfranco
 Version     :
 Copyright   : Your copyright notice
 Description : Opcode file - declare all opcodes and + functions and declarations of opcodes utils
 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include "../errors/errors.h"
#include "../utils/array_utils.h"
#include "directives.h"


Directive DirectivesArray [] = {
		{".data", DATA_DIRECTIVE},
		{".string", STRING_DIRECTIVE},
		{".entry", ENTRY_DIRECTIVE},
		{".extern", EXTERN_DIRECTIVE}
};


char ** get_directives_names(){
	char ** DirectivesNames = (char **)malloc(DIRECTIVES_LENGTH * sizeof(char *));
	for (int i = 0; i < DIRECTIVES_LENGTH; i++) {
		DirectivesNames[i] = DirectivesArray[i].name;
	}
	return DirectivesNames;
}


int is_directive_exist(char * directive){
	return is_in_array_string(directive, get_directives_names(), DIRECTIVES_LENGTH);
}


Directive get_directive_from_directive_string(char * directive){
	return DirectivesArray[get_index_in_array_string(directive, get_directives_names(), DIRECTIVES_LENGTH)];
}



