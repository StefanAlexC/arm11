//
// Created by DAVID BUTEREZ on 25/05/17.
//

#ifndef ARM11_37_UTILS_H
#define ARM11_37_UTILS_H

#include <stdint.h>
#include "masks.h"

typedef uint32_t instr;

enum cond {EQ, NE, GE, LT, GT, LE, AL};
enum opcode {AND, EOR, SUB, RSB, ADD, TST, TEQ, CMP, ORR, MOV};


/**
     * Prints the bits of a 32-bit integer
     * Most significant bit to the left
*/
void printBits(uint32_t bits);


/**
     * Changes the n-th bit of the number to the provided b bit value
     * If the bits variable is, say, a, then pass &a
*/
void changeBit(uint32_t *bits, int n, int b);


/**
     * Returns a new number with the n-th bit of the original set to the provided b bit value
*/
uint32_t setBit(uint32_t bits, int n, int b);


/**
     * Returns the bit value at n-th position
*/
uint32_t getBit(uint32_t bits, int n);

/**
     * Returns the index of the highest set (= 1) bit
*/
uint32_t highestSetBitIndex(uint32_t bits);


/**
     * Returns the index of the lowest set (= 1) bit
*/
uint32_t lowestSetBitIndex(uint32_t bits);


/**
     * Returns the result of ANDing the given bits with the given mask
*/
uint32_t simpleMask(uint32_t bits, uint32_t mask);


/**
     * Masks and then shifts right (i.e. if mask is 0000111100 then result has the form 0000001111)
*/
uint32_t mask(uint32_t bits, uint32_t mask);


#endif //ARM11_37_UTILS_H
