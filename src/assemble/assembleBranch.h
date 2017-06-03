#ifndef ARM11_37_ASSEMBLEBRANCH_H
#define ARM11_37_ASSEMBLEBRANCH_H

#include <stdint.h>
#include "../arm11_utils.h"

#define BEQ "beq"
#define BNE "bne"
#define BGE "bge"
#define BLT "blt"
#define BGT "bgt"
#define BLE "ble"
#define BAL "b"
#define BEQ_BYTES 0
#define BNE_BYTES 1
#define BGE_BYTES 10
#define BLT_BYTES 11
#define BGT_BYTES 12
#define BLE_BYTES 13
#define BAL_BYTES 14
#define CONDITION_OFFSET 4
#define OFFSET_OFFSET 24
#define BRANCH_OPCODE 10
#define MEMORY_MULTIPLIER 4
#define PIPELINE_OFFSET 8
#define PADDING 4278190080
#define SIGN_BIT 8388608

/**
 * Encodes the given instruction in a 32bit format.
 * @param argv The string array containing the arguments of the instructions.
 * @param labels The ADT that maps labels to memory locations.
 * @param currentOperationNumber An int indicating what is the number of the current instruction.
 * @return The encoded 32bit instruction.
 */
uint32_t encodeBranch(char**argv, Map* labels, int32_t currentOperationNumber);

/**
 * Computes the condition value of the instruction.
 * @param operation The string containing the instruction.
 * @return The 4bit condition code.
 */
uint8_t computeCond(char* operation);

/**
 * Gets the memory address the referenced label points to.
 * @param searchedLabel The label we wish to search.
 * @param labels The map containing the labels and memory addresses.
 * @return The value of the searched key label.
 */
uint32_t getLabelAddress(char *searchedLabel, Map* labels);

/**
 * Converts a normal binary number into a 24bit two's complement number.
 * @param number The number we wish to convert.
 * @return The 24bit two's complement number.
 */
uint32_t twosComplement24bit(int32_t number);

/**
 * Calculates the offset from the current memory location to the one we wish to jump to.
 * @param target The target address we want to jump to.
 * @param source The source address, where we currently are.
 * @return The calculates 24bit offset.
 */
uint32_t calculateOffset(int32_t target, int32_t source);

#endif //ARM11_37_ASSEMBLEBRANCH_H
