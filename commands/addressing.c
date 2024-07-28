#include "addressing.h"


int get_addressing_bits(AddressingType addressing){
	return 1 << addressing;
}
