/*
 ============================================================================
 Name        : addressing.c
 Author      : Zohar Franco
 Version     :
 Copyright   : Your copyright notice
 Description : Addressing file - functions to handle addressing functionality
 ============================================================================
 */


#include "addressing.h"


int get_addressing_bits(AddressingType addressing) {
    return 1 << (addressing - 1);
}
