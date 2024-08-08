#ifndef ADDRESSING_H
#define ADDRESSING_H

#define IMMEDIATE_ADDRESSING_CHAR '#'
#define REGISTRY_INDIRECT_ADDRESSING_CHAR '*'

#define ADDRESSING_BITS 4
#define SOURCE_ADDRESSING_BITS_SHIFT 7 // number of shift left needed to reach the machine code line LSB 7-10
#define DESTINATION_ADDRESSING_BITS_SHIFT 3 // number of shift left needed to reach the machine code line LSB 3-6


/*!
 * Enum of all addressing types
 */
typedef enum {
    NOT_EXIST,
    IMMEDIATE_ADDRESSING,
    DIRECT_ADDRESSING,
    REGISTRY_INDIRECT_ADDRESSING,
    REGISTRY_DIRECT_ADDRESSING,
    ADDRESSINGS_LENGTH
} AddressingType;


/*!
 * Get the addressing number and return the mask bits
 * @param addressing : addressing type to get bits
 * @return int of bits
 */
int get_addressing_bits(AddressingType addressing);


#endif // ADDRESSING_H
