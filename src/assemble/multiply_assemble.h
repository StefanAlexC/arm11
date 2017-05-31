//
// Created by user on 5/31/2017.
//

#ifndef ARM11_37_MULTIPLY_ASSEMBLE_H
#define ARM11_37_MULTIPLY_ASSEMBLE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Returns numerical index of a register (0-15) given a pointer to its string
 * representation
 * @param registerString : pointer to string representation of register
 * @return : index of register
 */

uint32_t getRegisterIndex(char* registerString);

/**
 * Returns pointer to string of binary representation of number
 * @param number : number to be converted
 * @return : string of binary bits
 */

char* intToBinaryString(uint32_t number);

/**
 * Returns pointer to string representation of 32 bit binary instruction
 * given number of arguments and pointer to array of parameters
 * @param args : number of valid arguments in instruction (3 or 4)
 * @param parameters : pointer to array of valid parameters for multiply
 * instruction
 * @return : pointer to string containing binary representation of instruction
 */

char* assembleMultiply(uint32_t args, char* parameters);
#endif //ARM11_37_MULTIPLY_ASSEMBLE_H
