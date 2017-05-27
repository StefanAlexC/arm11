//
// Created by DAVID BUTEREZ on 25/05/17.
//

#include "decode_utils.h"
#include "stdbool.h"

#ifndef ARM11_37_DECODE_H
#define ARM11_37_DECODE_H

/**
 *
 * @param instruction
 * @return true if the provided instruction is a Data Processing Instruction
 */
bool isDataProcessingInstruction(instr instruction);

/**
 *
 * @param instruction
 * @return true if the provided instruction is a Single Data Transfer Instruction
 */
bool isSingleDataTransferInstruction(instr instruction);

/**
 *
 * @param instruction
 * @return true if the provided instruction is a Branch Instruction
 */
bool isBranchInstruction(instr instruction);

/**
 *
 * @param instruction
 * @return true if the provided instruction is a Branch Instruction
 */
bool isMultiplyInstruction(instr instruction);

/**
 *
 * @param instruction
 * Simulated "test" to see what type the provided instruction is
 */
void testInstr(instr instruction);

/**
 *
 * @param instruction
 * @return corresponding InstrType enum value (one of the 4 types) for the given instruction
 */
InstrType getType(instr instruction);

/**
 *
 * @param operand
 * @param immediateBit
 * @return a struct containing all the useful information required to execute a Data Processing Instruction
 * If operand2 is an immediate value, the rotate right amount is ALREADY multiplied by 2
 */
Operand processOperand2(uint32_t operand, uint32_t immediateBit);

/**
 *
 * @param operand
 * Prints the data contained in the operand
 */
void printOperand(Operand operand);

/**
 *
 * @param base; contains decoded instruction data that is common to all instruction types
 * @param instruction; the 32-bit instruction
 * @return a pointer to a DataProcessingInstruction struct
 * All the decoded data is contained in the struct
 *
 */
DataProcessingInstruction* decodeDP(DecodedInstruction* base, instr instruction);

/**
 *
 * @param base; contains decoded instruction data that is common to all instruction types
 * @param instruction; the 32-bit instruction
 * @return a pointer to a MultiplyInstruction struct
 * All the decoded data is contained in the struct
 *
 */
MultiplyInstruction* decodeM(DecodedInstruction* base, instr instruction);

/**
 *
 * @param base; contains decoded instruction data that is common to all instruction types
 * @param instruction; the 32-bit instruction
 * @return a pointer to a SingleDataTransferInstruction struct
 * All the decoded data is contained in the struct
 *
 */
SingleDataTransferInstruction* decodeSDT(DecodedInstruction* base, instr instruction);

/**
 *
 * @param base; contains decoded instruction data that is common to all instruction types
 * @param instruction; the 32-bit instruction
 * @return a pointer to a BranchInstruction struct
 * All the decoded data is contained in the struct
 *
 */
BranchInstruction* decodeB(DecodedInstruction* base, instr instruction);

/**
 *
 * @param instruction; the 32-bit instruction
 * @return the corresponding struct containing the decoded data for the given instruction
 * Since there are multiple instruction types, a void pointer is provided
 * In order to use the return value, first cast to DecodedInstruction
 * (i.e. DecodedInstruction *dec = (DecodedInstruction *) instrPtr
 * This will allow you to extract the type from the DecodedInstruction struct
 * Once you know the type, cast to the appropriate struct type
 * (i.e. BranchInstruction *bi = (BranchInstruction *) instrPtr;)
 * Also see function testStructs for example usage
 */
void* decode(instr instruction);

/**
 *
 * @param dp
 * Print useful decoded information about the provided instruction
 */
void printDPI(DataProcessingInstruction *dp);

/**
 *
 * @param mi
 * Print useful decoded information about the provided instruction
 */
void printMI(MultiplyInstruction *mi);

/**
 *
 * @param sdti
 * Print useful decoded information about the provided instruction
 */
void printSDTI(SingleDataTransferInstruction *sdti);

/**
 *
 * @param bi
 * Print useful decoded information about the provided instruction
 */
void printBI(BranchInstruction *bi);

/**
 *
 * @param instrPtr
 * Example use of decode
 */
void testStructs(void* instrPtr);

#endif //ARM11_37_DECODE_H
