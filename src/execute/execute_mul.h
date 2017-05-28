//
// Created by user on 5/25/2017.
//

#ifndef ARM11_37_EXECUTE_MUL_H
#define ARM11_37_EXECUTE_MUL_H

#include <stdlib.h>
#include "../emulate.h"
#include "../decode/decode_utils.h"



/**
 * Return address of register in ARM11 structure when given register index
 * from Instruction structure field
 * @param r : index of register
 * @return : pointer to specific register within registers field
 */

uint32_t* registerFind(uint32_t r);


/**
 * Executes a multiplication instruction with given MultiplyInstruction
 * structure
 * @param multiplyInstruction : given MultiplyInstruction structure
 */

void multiply(MultiplyInstruction* multiplyInstruction);


/**
 * Prints the binary representation of a number
 * Used for testing purposes
 * @param x : number to be printed
 */

void printBits(uint32_t x);

#endif //ARM11_37_EXECUTE_H