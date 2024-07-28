#ifndef DIRECTIVES_H
#define DIRECTIVES_H


/*!
 * Enum of directive types
 */
typedef enum {
    DATA_DIRECTIVE, STRING_DIRECTIVE, ENTRY_DIRECTIVE, EXTERN_DIRECTIVE, DIRECTIVES_LENGTH
} DirectiveType;


/*!
 * Struct of directive
 */
typedef struct Directive {
    char *name;
    DirectiveType type;
} Directive;


/*!
 * Array of all directives options
 */
extern Directive DirectivesArray[]; // Array of all directives


/*!
 * Function to return all directive names array by DirectivesArray
 * @return all directives names as list of strings
 */
char **get_directives_names();


/*!
 * Function that gets directive string and return if exist
 * @param directive : directive name to check if exist
 * @return
 */
int is_directive_exist(char *directive);


/*!
 * Function that gets string directive and return the map value directive
 * @param directive : directive name to get by
 * @return directive object
 */
Directive get_directive_from_directive_string(char *directive);


#endif // DIRECTIVES_H
