//
// Created by user on 5/25/2017.
//

#ifndef ARM11_37_EXECUTE_MUL_H
#define ARM11_37_EXECUTE_MUL_H
#define CPSR_BIT_N_POSITION 31
#define CPSR_BIT_Z_POSITION 30

#include <stdlib.h>
#include "../decode/decode_utils.h"


/**
 * Executes a multiplication instruction with given MultiplyInstruction
 * structure
 * @param multiplyInstruction : given MultiplyInstruction structure
 * @param arm11 : ARM11 structure
 */

void multiply(MultiplyInstruction* multiplyInstruction, ARM11* arm11);

#endif //ARM11_37_EXECUTE_H

