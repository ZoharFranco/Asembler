#ifndef ENCODING_H
#define ENCODING_H

#define ENCODINGS_SHIFT 0
#define ENCODINGS_BITS 3

/*!
 * Enum of encoding types
 */
typedef enum {
    A, R, E, ENCODINGS_LENGTH
} EncodingType;


/*!
 * Get the encoding number and return the mask bits
 * @param encoding : encoding type
 * @return the bits as int
 */
int get_encoding_bits(EncodingType encoding);


#endif // ENCODING_H
