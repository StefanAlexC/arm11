//
// Created by DAVID BUTEREZ on 26/05/17.
//

#ifndef ARM11_37_BARREL_SHIFTER_H
#define ARM11_37_BARREL_SHIFTER_H

#include <stdint.h>

/**
 *
 * @param bits
 * @param n
 * @return carry out
 * Perform the rotate right operation on the original bits variable by n amount
 */
uint32_t rotateRight(uint32_t* bits, uint32_t n);

/**
 *
 * @param bits
 * @param n
 * @return carry out
 * Perform the logical shift left operation on the original bits variable by n amount
 */
uint32_t shiftLeft(uint32_t* bits, uint32_t n);

/**
 *
 * @param bits
 * @param n
 * @return carry out
 * Perform the logical shift right operation on the original bits variable, by n amount
 */
uint32_t shiftRight(uint32_t* bits, uint32_t n);

/**
 *
 * @return carry out
 * Perform the arithmetic shift right operation on the original bits variable only once
 */
uint32_t arithmeticShiftRightOnce(uint32_t* bits);

/**
 *
 * @param bits
 * @param n
 * @return carry out
 * Perform the arithmetic shift right operation on the original bits variable, by n amount
 */
uint32_t arithmeticShiftRight(uint32_t* bits, uint32_t n);

#endif //ARM11_37_BARREL_SHIFTER_H