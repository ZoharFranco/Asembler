/*
 ============================================================================
 Name        : encoding.c
 Author      : Zohar Franco
 Version     :
 Copyright   : Your copyright notice
 Description : Encoding file - functions to handle encoding functionality
 ============================================================================
 */



#include "encoding.h"


int get_encoding_bits(EncodingType encoding) {
    return (1 << encoding);
}
