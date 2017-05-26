//
// Created by DAVID BUTEREZ on 25/05/17.
//

#include "utils.h"

#ifndef ARM11_37_DECODE_H
#define ARM11_37_DECODE_H


/**
     * Return true if the provided instruction is a Data Processing Instruction
*/
bool isDataProcessingInstruction(instr instruction);

/**
     * Return true if the provided instruction is a Single Data Transfer Instruction
*/
bool isSingleDataTransferInstruction(instr instruction);

/**
     * Return true if the provided instruction is a Branch Instruction
*/
bool isBranchInstruction(instr instruction);

/**
     * Return true if the provided instruction is a Branch Instruction
*/
bool isMultiplyInstruction(instr instruction);

/**
     * Simulated "test" to see what type the provided instruction is
*/
void testInstr(instr instruction);

#endif //ARM11_37_DECODE_H
