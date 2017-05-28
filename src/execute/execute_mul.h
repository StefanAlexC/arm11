//
// Created by user on 5/25/2017.
//

#ifndef ARM11_37_EXECUTE_MUL_H
#define ARM11_37_EXECUTE_MUL_H
#define CPSR_BIT_N_POSITION 31
#define CPSR_BIT_Z_POSITION 30

#include <stdlib.h>
#include "../emulate.h"
#include "../decode/decode_utils.h"



/**
 * Return address of register in ARM11 structure when given register index
 * from Instruction structure field
 * @param r : index of register
 * @param arm11 : ARM11 structure
 * @return : pointer to specific register within registers field
 */

uint32_t* registerFind(uint32_t r, ARM11* arm11);


/**
 * Executes a multiplication instruction with given MultiplyInstruction
 * structure
 * @param multiplyInstruction : given MultiplyInstruction structure
 * @param arm11 : ARM11 structure
 */

void multiply(MultiplyInstruction* multiplyInstruction, ARM11* arm11);

#endif //ARM11_37_EXECUTE_H