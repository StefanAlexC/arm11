#ifndef ARM11_37_EXECUTE_H
#define ARM11_37_EXECUTE_H

#include "../emulate.h"
#include "../decode/decode.h"
#include "../decode/decode_utils.h"
#include <stdbool.h>
#include <stdint.h>

typedef enum FLAG {STOP, NORMAL, BRANCH} FLAG;

//TODO: Add definition
FLAG execute(void *decoded, struct ARM11* arm11);

#endif //ARM11_37_EXECUTE_H

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
 * Checks if condition bits satisfy the contents of CPSR register
 * @param condition : condition bits to check
 * @return : returns boolean if condition was satisfied
 */
//bool isConditionSatisfied(uint32_t condition);
