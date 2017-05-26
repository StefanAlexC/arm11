//
// Created by DAVID BUTEREZ on 25/05/17.
//

#include <stdio.h>
#include <stdbool.h>
#include "decode.h"
#include "utils.h"
#include "masks.h"

static const uint32_t BRANCH_BITS = 0b10;
static const uint32_t SDT_BITS = 0b01;

bool isDataProcessingInstruction(instr instruction) {
    // check that bits 27-26 are 0
    if (mask(instruction, CHECK_BITS)) {
        return false;
    }
    // check if bits 24-22 are 0
    int checkBits = mask(instruction, DATA_PROCESSING_HELPER_MASK);
    if (checkBits) {
        return true;
    }
    // if I is 1 then instr is Data Processing
    int immediateBit = mask(instruction, IMMEDIATE_OP_MASK);
    if (immediateBit) {
        return true;
    }
    // if I is 0 then check bits 4 and 7
    int bit4 = getBit(instruction, 4);
    int bit7 = getBit(instruction, 7);
    return !bit4 || (bit4 && !bit7);
}

bool isSingleDataTransferInstruction(instr instruction) {
    int checkBits = mask(instruction, CHECK_BITS);
    return checkBits == SDT_BITS;
}

bool isBranchInstruction(instr instruction) {
    int checkBits = mask(instruction, CHECK_BITS);
    return checkBits == BRANCH_BITS;
}

bool isMultiplyInstruction(instr instruction) {
    return !isDataProcessingInstruction(instruction) && !isSingleDataTransferInstruction(instruction)
            && !isBranchInstruction(instruction);
}

void testInstr(instr instruction) {
    printf("Data Processing Instr: %i ; Multiply: %i ; SDT: %i ; Branch: %i\n",
           isDataProcessingInstruction(instruction),
           isMultiplyInstruction(instruction),
           isSingleDataTransferInstruction(instruction),
           isBranchInstruction(instruction));
}

int main(void) {
//  10100000110111100111000001111000 / Data Processing
    instr instr1 = 0xA0DE7078;
//  10100010000111100111000001111000 / Data Processing
    instr instr2 = 0xA21E7078;
//  10100000000111100111000001101000 / Data Processing
    instr instr3 = 0xA01E7068;
//  10100000000111100111000001111000 / Data Processing
    instr instr4 = 0xA01E7078;
//  10100100000111100111000001111000 / SDT
    instr instr5 = 0xA41E7078;
//  10100000000111100111000010011000 / Multiply
    instr instr6 = 0xA01E7098;
//  10101000000111100111000010011000 / Branch
    instr instr7 = 0xA81E7098;

    testInstr(instr1);
    testInstr(instr2);
    testInstr(instr3);
    testInstr(instr4);
    testInstr(instr5);
    testInstr(instr6);
    testInstr(instr7);
}
