#ifndef ARM11_37_EXECUTE_H
#define ARM11_37_EXECUTE_H

#include "../decode/decode_utils.h"
#include "../ARM11.h"
#include <stdbool.h>
#include <stdint.h>
#include "execute_mul.h"
#include "execute_SDT.h"
#include "execute_dp.h"
#include "execute_b.h"

#define CPSR_SIGNIFICANT_BITS (arm11->registers[16] >> 28)

/**
 * Handle the execution of an instruction
 * @param decoded The decoded instruction that needs to be executed
 * @param arm11 Pointer to the ARM11 object
 * @return A flag that indicated the status of the processor
 */
FLAG execute(void *decoded, ARM11 *arm11);

/**
 * Tests if the current instruction satisfies the condition of the CSPR register
 * @param condition The condition under which the current instruction needs
 * to be executed
 * @param arm11 Pointer to the ARM11 object
 * @return TRUE if the condition is satisfied and FALSE otherwise.
 */
bool isConditionSatisfied(Cond condition, ARM11 *arm11);

#endif //ARM11_37_EXECUTE_H