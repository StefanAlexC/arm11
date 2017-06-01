//
// Created by DAVID BUTEREZ on 25/05/17.
//

#ifndef ARM11_37_UTILS_H
#define ARM11_37_UTILS_H

#include <stdint.h>
#include "masks.h"
#include <stdio.h>
#include <assert.h>

typedef uint32_t instr;

typedef enum {EQ = 0, NE = 1, GE = 10, LT = 11, GT = 12, LE = 13, AL = 14,
    NOTUSED = 15} Cond;
typedef enum {AND = 0, EOR = 1, SUB = 2, RSB = 3, ADD = 4, TST = 8, TEQ = 9, CMP = 10, ORR = 12, MOV = 13, UNUSED = 14, ANDEQ = 15} Opcode;
typedef enum {LSL, LSR, ASR, ROR} ShiftType;
typedef enum {DP, M, SDT, B, H} InstrType;

typedef struct {
    InstrType type;
    Cond condition;
    uint32_t Rn;
    uint32_t Rd;
} DecodedInstruction;

typedef struct {
    uint32_t I;
    uint32_t immediateValue;
    uint32_t Rm;
    uint32_t Rs;
    uint32_t bit4;
    uint32_t shiftAmount;
    ShiftType shiftType;
} Operand;

typedef struct {
    DecodedInstruction baseInstr;
    uint32_t immediate;
    uint32_t set;
    Opcode opcode;
    Operand operand2;
} DataProcessingInstruction;

typedef struct {
    DecodedInstruction baseInstr;
    uint32_t accumulate;
    uint32_t set;
    uint32_t Rs;
    uint32_t Rm;
} MultiplyInstruction;

typedef struct {
    DecodedInstruction baseInstr;
    uint32_t immediate;
    uint32_t prePost;
    uint32_t up;
    uint32_t load;
    uint32_t offset;
} SingleDataTransferInstruction;

typedef struct {
    DecodedInstruction baseInstr;
    uint32_t offset;
} BranchInstruction;

/**
 *
 * @param bits
 * @param n
 * @param b
 * Changes the n-th bit of the number to the provided b bit value
 * If the bits variable is, say, a, then pass &a
 */
void changeBit(uint32_t *bits, int n, int b);


/**
 *
 * @param bits
 * @param n
 * @param b
 * @return a new number with the n-th bit of the original set to the provided b bit value
 */
uint32_t setBit(uint32_t bits, int n, int b);


/**
 *
 * @param bits
 * @param n
 * @return the bit value at n-th position
 */
uint32_t getBit(uint32_t bits, int n);

/**
 *
 * @param bits
 * @return the index of the highest set (= 1) bit
 */
uint32_t highestSetBitIndex(uint32_t bits);


/**
 *
 * @param bits
 * @return the index of the lowest set (= 1) bit
 */
uint32_t lowestSetBitIndex(uint32_t bits);


/**
 *
 * @param bits
 * @param mask
 * @return the result of ANDing the given bits with the given mask
 */
uint32_t simpleMask(uint32_t bits, uint32_t mask);


/**
 *
 * @param bits
 * @param mask
 * @return Masks and then shifts right (i.e. if mask is 0000111100 then result has the form 0000001111)
 */
uint32_t mask(uint32_t bits, uint32_t mask);

///////////////// function names are self-explanatory /////////////////
uint32_t getConditionBits(instr instruction);

uint32_t getConditionBits(instr instruction);

uint32_t getRnBits(instr instruction);

uint32_t getRdBits(instr instruction);

uint32_t getRnMultiplyBits(instr instruction);

uint32_t getRdMultiplyBits(instr instruction);

uint32_t getOpcodeBits(instr instruction);

uint32_t getImmediateBit(instr instruction);

uint32_t getOperand2Bits(instr instruction);

uint32_t getSDTOffset(instr instruction);

uint32_t getSetBit(instr instruction);

uint32_t getAccumulateBit(instr instruction);

uint32_t getRsBits(instr instruction);

uint32_t getRmBits(instr instruction);

uint32_t getLoadBits(instr instruction);

uint32_t getPrePostBit(instr instruction);

uint32_t getUpBit(instr instruction);

uint32_t getBranchOffset(instr instruction);

///////////////// function names are self-explanatory /////////////////

/**
 *
 * @param conditionBits
 * @return corresponding Cond enum from bits
 */
Cond getCond(uint32_t conditionBits);

/**
 *
 * @param cond
 * @return a string with the name of the cond
 */
char* getCondString(Cond cond);

/**
 *
 * @param bits
 * @return corresponding Opcode enum from bits
 */
Opcode getOpcode(uint32_t bits);

/**
 *
 * @param opcode
 * @return a string with the name of the opcode
 */
char* getOpcodeString(Opcode opcode);

/**
 *
 * @param bits
 * @return corresponding ShiftType enum from bits
 */
ShiftType getShiftType(uint32_t bits);

/**
 *
 * @param shiftType
 * @return a string with the name of the ShiftType
 */
char* getShiftTypeString(ShiftType shiftType);

#endif //ARM11_37_UTILS_H
