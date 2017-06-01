#ifndef ARM11_37_MULTIPLY_ASSEMBLE_H
#define ARM11_37_MULTIPLY_ASSEMBLE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_CONDITION_CODE 14
#define MUL_PATTERN_SIZE 6
#define MUL_OPCODE parameters[0]
#define RD parameters[1]
#define RM parameters[2]
#define RS parameters[3]
#define RN parameters[4]
#define MLA "mla"
#define MUL_PATTERN 9

/** Returns pointer to string representation of 32 bit binary instruction
 * given number of arguments and pointer to array of parameters
 * @param args : number of valid arguments in instruction (3 or 4)
 * @param parameters : pointer to array of valid parameters for multiply
 * instruction
 * @return : pointer to string containing binary representation of instruction
 */

uint32_t assembleMultiply(char **parameters);

#endif //ARM11_37_MULTIPLY_ASSEMBLE_H
