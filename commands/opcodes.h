#ifndef OPCODES_H
#define OPCODES_H


#include "addressing.h"
#include "encoding.h"

#define OPCODE_BITS_SHIFT 11 // number of shift left needed to reach the machine code line LSB 11-14


/*!
 * Enum of all opcode args types
 */
typedef enum {
    LABEL_OPCODE_ARG, REGISTRY_OPCODE_ARG, NUMBER_OPCODE_ARG, OPCODE_ARGS_LENGTH
} OpcodeInstructionArgType;


/*!
 * OpcodeInstructionArg struct contain string data and type OpcodeInstructionArgType
 */
typedef struct OpcodeInstructionArg {
    char *data;
    OpcodeInstructionArgType type;
    AddressingType addressing;
} OpcodeInstructionArg;


/*!
 * Enum of all opcodes numbers
 */
typedef enum {
    MOV, CMP, ADD, SUB, LEA, CLR, NOT, INC, DEC, JMP, BNE, RED, PRN, JSR, RTS, STOP, OPCODES_LENGTH
} OpcodeType;


/*!
 * Opcode struct contain string name, OpcodeNumber number, int number_of_args number of args that use, and function to handle opcode action
 */
typedef struct Opcode {
    OpcodeType type;
    char *name;
    int number_of_args;
    AddressingType source_addressings[ADDRESSINGS_LENGTH];
    AddressingType destination_addressings[ADDRESSINGS_LENGTH];
} Opcode;


/*!
 * Array of all opcodes
 */
extern Opcode OpcodesArray[];


/*!
 * Function to return all opcodes names array by OpcodesArray
 * @return all the opcode names as list of strings
 */
char **get_opcodes_names();


/*!
 *  Function that gets opcode string and return if exist
 * @param opcode: opcode string to search
 * @return returns 1 if opcode is in the array of opcodes and 0 otherwise
 */
int is_opcode_exist(char *opcode);


/*!
 * Function that gets string opcode and return the map value opcode object
 * @param opcode: opcode string to get
 * @return the Opcode opcode object
 */
Opcode get_opcode_from_opcode_string(char *opcode);


/*!
 * Function that gets opcode and return its int bits representation
 * @param opcode: opcode to gets its bits int
 * @return the int representation of the opcode
 */
int get_opcode_bits(Opcode opcode);


/*!
 * Function that gets string arg and return the parsed OpcodeInstructionArg arg
 * @param arg: string arg to parse
 * @return OpcodeInstructionArg object after parsing the arg as raw string
 */
OpcodeInstructionArg parse_opcode_instruction_arg(char *arg);


#endif // OPCODES_H
