#ifndef ARM11_37_ARM11_UTILS_H
#define ARM11_37_ARM11_UTILS_H

#include <stdint.h>
#include <stdio.h>

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
 *
 * @param bits
 * Prints the bits of a 32-bit integer
 * Most significant bit to the left
 */
void printBits(uint32_t bits);

#endif //ARM11_37_ARM11_UTILS_H
