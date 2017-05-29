//
// Created by DAVID BUTEREZ on 25/05/17.
//

#include "decode_utils.h"
#include <stdio.h>
#include <assert.h>

Opcode opcode[] = {AND, EOR, SUB, RSB, ADD, UNUSED, UNUSED, UNUSED, TST, TEQ, CMP, UNUSED, ORR, MOV};
char* opcodeString[] = {"AND", "EOR", "SUB", "RSB", "ADD", "TST", "TEQ", "CMP", "ORR", "MOV"};

Cond condition[] = {EQ, NE, NOTUSED, NOTUSED, NOTUSED, NOTUSED, NOTUSED,NOTUSED, NOTUSED, NOTUSED, GE, LT, GT, LE, AL};
char* conditionString[] = {"EQ", "NE", "GE", "LT", "GT", "LE", "AL"};

ShiftType shift[] = {LSL, LSR, ASR, ROR};
char* shiftString[] = {"LSL", "LSR", "ASR", "ROR"};

void printBits(uint32_t bits) {
    uint32_t mask = (uint32_t) (1 << (INSTR_BITS - 1));

    for (int i = 0; i < INSTR_BITS; i++) {
        printf("%i", (bits & mask) != 0);
        bits <<= 1;
    }

    printf("\n");
}

uint32_t setBit(uint32_t bits, int n, int b) {
    assert(b == 0 || b == 1);
    return bits ^ ((-b ^ bits) & (1 << n));
}

void changeBit(uint32_t *bits, int n, int b) {
    assert(b == 0 || b == 1);
    *bits = setBit(*bits, n, b);
}

uint32_t getBit(uint32_t bits, int n) {
    assert(n <= INSTR_BITS);
    return (bits >> n) & 1;
}

uint32_t highestSetBitIndex(uint32_t bits) {
    int p = 0;
    while (bits != 0) {
        p++;
        bits >>= 1;
    }

    return (uint32_t) p;
}

uint32_t lowestSetBitIndex(uint32_t bits) {
    int p = 0;
    while ((bits & 1) == 0) {
        bits >>= 1;
        p++;
    }

    return (uint32_t) p;
}

uint32_t simpleMask(uint32_t bits, uint32_t mask) {
    return (bits & mask);
}

uint32_t mask(uint32_t bits, uint32_t mask) {
    bits &= mask;
    return (bits >> lowestSetBitIndex(mask));
}

uint32_t getConditionBits(instr instruction) {
    return mask(instruction, COND_MASK);
}

uint32_t getRnBits(instr instruction) {
    return mask(instruction, RN_MASK);
}

uint32_t getRdBits(instr instruction) {
    return mask(instruction, RD_MASK);
}

uint32_t getRnMultiplyBits(instr instruction) {
    return mask(instruction, RN_MULTIPLY);
}

uint32_t getRdMultiplyBits(instr instruction) {
    return mask(instruction, RD_MULTIPLY);
}

uint32_t getOpcodeBits(instr instruction) {
    return mask(instruction, OPCODE_MASK);
}

uint32_t getImmediateBit(instr instruction) {
    return mask(instruction, IMMEDIATE_OP_MASK);
}

uint32_t getOperand2Bits(instr instruction) {
    return mask(instruction, OPERAND2_MASK);
}

uint32_t getSDTOffset(instr instruction) {
    return mask(instruction, SDT_OFFSET_MASK);
}

uint32_t getSetBit(instr instruction) {
    return mask(instruction, SET_CODE_MASK);
}

uint32_t getAccumulateBit(instr instruction) {
    return mask(instruction, ACCUMULATE_MASK);
}

uint32_t getRsBits(instr instruction) {
    return mask(instruction, RS_MASK);
}

uint32_t getRmBits(instr instruction) {
    return mask(instruction, RM_MASK);
}

uint32_t getLoadBits(instr instruction) {
    return mask(instruction, LOAD_MASK);
}

uint32_t getPrePostBit(instr instruction) {
    return mask(instruction, PRE_POST_MASK);
}

uint32_t getUpBit(instr instruction) {
    return mask(instruction, UP_MASK);
}

uint32_t getBranchOffset(instr instruction) {
    return mask(instruction, BRANCH_OFFSET_MASK);
}

Cond getCond(uint32_t conditionBits) {
    return condition[conditionBits];
}

char* getCondString(Cond cond) {
    return conditionString[cond];
}

Opcode getOpcode(uint32_t bits) {
    return opcode[bits];
}

char* getOpcodeString(Opcode opcode) {
    return opcodeString[opcode];
}

ShiftType getShiftType(uint32_t bits) {
    return shift[bits];
}

char* getShiftTypeString(ShiftType shiftType) {
    return shiftString[shiftType];
}
