#ifndef ARM11_37_EXECUTE_H
#define ARM11_37_EXECUTE_H

#include "../decode/decode_utils.h"
#include "../ARM11.h"
#include <stdbool.h>
#include <stdint.h>
#include "execute_mul.h"
#include "execute_SDT.h"
#include "execute_dp.h"

#define CPSR_SIGNIFICANT_BITS (arm11->registers[14] >> 28)

/**
 * Handle the execution of an instruction
 * @param decoded The decoded instruction that needs to be executed
 * @param arm11 Pointer to the ARM11 object
 * @return A flag that indicated the status of the processor
 */
FLAG execute(void *decoded, ARM11 *arm11);

/**
 * Generates a mask in order to select specific bits
 * @param start : start of bit
 * @param end : end of bit
 * @return : returns a 32 bit mask
 */
uint32_t genMask(int start, int end);

/**
 * Extracts all bits between two specified positions
 * @param n : number to extract from
 * @param start : start position
 * @param end : end position
 * @return
 */
uint32_t extractBit(uint32_t n, int start, int end);

/**
 * Tests if the current instruction satisfies the condition of the CSPR register
 * @param condition The condition under which the current instruction needs
 * to be executed
 * @param arm11 Pointer to the ARM11 object
 * @return TRUE if the condition is satisfied and FALSE otherwise.
 */
bool isConditionSatisfied(Cond condition, ARM11 *arm11);

#endif //ARM11_37_EXECUTE_H