/*
 ============================================================================
 Name        : args_utils.c
 Author      : Zohar Franco
 Version     :
 Copyright   : Your copyright notice
 Description : Args utils - functions to handle input form stdin-args
 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>

// Extract agrvs
// Gets integer argc and pointer to pointers of chars argv
// Print the program name, the input argvs and return function to the arguments only
char **extract_argvs(int argc, char **argvs) {

    printf("\nProgram name is: %s", argvs[0]);

    if (argc == 1)
        printf("\nNo Extra Command Line Argument Passed "
               "Other Than Program Name");

    char **only_argvs = malloc(argc * sizeof(*argvs));
    if (argc >= 2) {

        printf("\nNumber Of Arguments Passed: %d", argc - 1);
        printf("\n----Following Are The Command Line "
               "Arguments Passed----");
        for (int i = 1; i < argc; i++) {
            printf("\nargv[%d]: %s", i, argvs[i]);
            only_argvs[i - 1] = argvs[i];
        }
    }
    printf("\n");
    return only_argvs;
}
