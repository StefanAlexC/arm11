//
// Created by DAVID BUTEREZ on 26/05/17.
//

#include <assert.h>
#include "barrel_shifter.h"
#include "masks.h"
#include "decode/decode_utils.h"

uint32_t rightOperationCarry(uint32_t bits, uint32_t n) {
    return getBit(bits, n - 1);
}

uint32_t rotateRight(uint32_t* bits, uint32_t n) {
    assert(n <= INSTR_BITS);
    uint32_t carry = rightOperationCarry(*bits, n);
    uint32_t leftshift = (32 - n) % 32;
    uint32_t shifted = (*bits) >> n;
    uint32_t rotated = (*bits) << leftshift;

    (*bits) = shifted | rotated;

    return carry;
}

uint32_t shiftLeft(uint32_t* bits, uint32_t n) {
    assert(n <= INSTR_BITS);
    uint32_t carry = getBit(*bits, INSTR_BITS - n);
    (*bits) <<= n;
    return carry;
}

uint32_t shiftRight(uint32_t* bits, uint32_t n) {
    assert(n <= INSTR_BITS);
    uint32_t carry = rightOperationCarry(*bits, n);
    (*bits) >>= n;
    return carry;
}

uint32_t arithmeticShiftRightOnce(uint32_t* bits) {
    uint32_t msb = mask(*bits, MSB_LITTLE_ENDIAN_MASK);
    uint32_t carry = getBit(*bits, 0);
    *bits >>= 1;
    changeBit(bits, INSTR_BITS - 1, (msb != 0));
    return carry;
}

uint32_t arithmeticShiftRight(uint32_t* bits, uint32_t n) {
    assert(n <= INSTR_BITS);
    uint32_t carry = rightOperationCarry(*bits, n);
    for (int i = 0; i < n; i++) {
        arithmeticShiftRightOnce(bits);
    }
    return carry;
}