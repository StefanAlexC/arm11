//
// Created by Stefan Alexandru Cuturela on 29/05/2017.
//

#ifndef ARM11_37_BRANCH_INSTRUCTION_H
#define ARM11_37_BRANCH_INSTRUCTION_H

#include <stdint.h>
#include "execute.h"
#include "../ARM11.h"
#include "../decode/decode_utils.h"

/**
 * Padding is equivalent to 11111111 followed by 24 bits of value 0.
 */
#define PADDING  4278190080

/**
 * The bit containing the the sign value of the number.
 */
#define SIGN_BIT 23

/**
 * The offset that needs to be added in the two's complement conversion.
 */
#define TWOS_COMPLEMENT_OFFSET 1

/**
 * The shift value that is required by the offset instruction.
 */
#define BRANCH_INSTRUCTION_OFFSET 2

/**
 * Pads 24 bit two's complemenet negative number with 1s up to 32bits.
 * @param number The 24bit two's complement that we wish to pad.
 * @return A 32bit number that has 1s on bits 31-24 and from 23-0 is equal to the original number.
 */
uint32_t padNegativeNumber(uint32_t number);

/**
 * Inverts all the bits of a number.
 * @param number The number whose bits we wish to invert.
 * @return The inverted number.
 */
uint32_t invertBits(uint32_t number);

/**
 * Returns the signed decimal value of a 24bit two's complement number.
 * @param number The 24bit two's complement number we want to convert.
 * @return The decimal value of the converted number extended to 32bits.
 */
int32_t twosComplementCovertor(uint32_t number);

/**
 * Executes an ARM11 branch instruction.
 * @param instruction The decoded instruction containing the unconverted offset.
 * @param arm11 Pointer to the ARM11 object.
 */
void branchInstruction(BranchInstruction * instruction, ARM11* arm11);

#endif //ARM11_37_BRANCH_INSTRUCTION_H
