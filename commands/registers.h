#ifndef REGISTER_H
#define REGISTER_H


#define REGISTER_SRC_BITS_SHIFT 6 // number of shift left needed to reach the opcode LSB 6-8
#define REGISTER_DST_BITS_SHIFT 3 // number of shift left needed to reach the opcode LSB 3-5


// Enum of all registers types
typedef enum {
    R1, R2, R3, R4, R5, R6, R7, REGISTERS_LENGTH
} RegisterNumber;

// Register struct contain string name and number RegisterNumber
typedef struct Registry {
    RegisterNumber number;
    char *name;
} Register;


extern Register RegistersArray[]; // Array of all registers
char **get_registers_names(); // Function to return all registers names array by RegisterArray
int is_register_exist(char *reg); // Function that gets string register and return the map value register
Register
get_register_from_register_string(char *reg); // Function that gets string register and return the map value register

unsigned short get_register_bits(Register reg, int is_src); // Function that gets register and return the bit mask
unsigned short
get_registers_bits(Register src_reg, Register dst_reg); // Function that gets 2 registers and return the bit mask


#endif // REGISTER_H
