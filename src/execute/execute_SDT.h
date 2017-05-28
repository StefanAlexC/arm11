//
// Created by Ada Cristina Stoenica on 28/05/2017.
//

#ifndef ARM11_37_EXECUTE_SDT_H
#define ARM11_37_EXECUTE_SDT_H

#include <cstdint>
#include "../ARM11.h"
#include "barrel_shifter.h"
#include "../emulate.h"
#include "../decode/decode_utils.h"

#define LSL 0
#define LSR 1
#define ASR 2
#define ROR 3

/**
 * Performs the shift indicated by the offset field to the value held by the register
 * @param offset
 * @param arm11
 * @return the shifted value
 */
uint32_t shiftRegister(uint32_t offset, ARM11* arm11);

/**
 * Calculates the memory address
 * @param up
 * @param base
 * @param offset
 * @return memory address
 */
uint32_t getAddress(uint32_t up, uint32_t base, uint32_t offset);

/**
 * Performs a data transfer from memory to a given register
 * @param mem
 * @param reg
 * @param arm11
 */
void fromMemory(uint32_t mem, uint32_t* reg, ARM11* arm11);

/**
 * Performs a data transfer from a register to memory
 * @param mem
 * @param value
 * @param arm11
 */
void toMemory(uint32_t mem, uint32_t value, ARM11* arm11);

/**
 * Performs the Single Data Transfer instruction on the arm11
 * @param instruction
 * @param arm11
 */
void dataTransfer(SingleDataTransferInstruction instruction, ARM11* arm11);



#endif //ARM11_37_EXECUTE_SDT_H
