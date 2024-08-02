#ifndef REGISTER_H
#define REGISTER_H


#define REGISTER_SRC_BITS_SHIFT 6 // number of shift left needed to reach the opcode LSB 6-8
#define REGISTER_DST_BITS_SHIFT 3 // number of shift left needed to reach the opcode LSB 3-5


/*!
 * Enum of all registers types
 */
typedef enum {
    R1, R2, R3, R4, R5, R6, R7, REGISTERS_LENGTH
} RegisterNumber;


/*!
 * Register struct contain string name and number RegisterNumber
 */
typedef struct Registry {
    RegisterNumber number;
    char *name;
} Register;

/*!
 * Array of all registers
 */
extern Register RegistersArray[];


/*!
 * Function to return all registers names array by RegisterArray
 * @return list of all registers names
 */
char **get_registers_names();


/*!
 * Function that gets string register and return the map value register
 * @param reg : register name to check if exist
 * @return returns 1 if reg is in the array of registers names and 0 otherwise
 */
int is_register_exist(char *reg);


/*!
 * Function that gets string register and return the map value register
 * @param reg : register name to get
 * @return Register object by reg string register name
 */
Register get_register_from_register_string(char *reg);


/*!
 * Function that gets register and return the bit mask
 * @param reg : register to gets its bits representation
 * @param is_src : if the register is src or not
 * @return the int representation of the register
 */
unsigned int get_register_bits(Register reg, int is_src);


/*!
 * Function that gets 2 registers and return the bit mask
 * @param src_reg : the first register in the opcode instruction
 * @param dst_reg : the second register in the opcode instruction
 * @return the int representation of the registers bits together
 */
unsigned int get_registers_bits(Register src_reg, Register dst_reg);


#endif // REGISTER_H
