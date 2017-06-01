//
// Created by DAVID BUTEREZ on 30/05/17.
//

#ifndef ARM11_37_ASSEMBLEDP_H
#define ARM11_37_ASSEMBLEDP_H
#define CONSTANT_EXPRESSION_SIGN '#'

#include <string.h>
#include "../emulate/decode/decode_utils.h"

struct {
    const char* mnemonic;
    Opcode opcode;
} opcodeDictionary[] = {{"and", AND}, {"eor", EOR}, {"sub", SUB}, {"rsb", RSB}, {"add", ADD}, {"tst", TST},
                        {"teq", TEQ}, {"cmp", CMP}, {"orr", ORR}, {"mov", MOV}, {"andeq", ANDEQ}, {"lsl", LSLI}};

struct {
    const char* mnemonic;
    uint32_t shiftType;
} shiftDictionary[] = {{"lsl", LSL}, {"lsr", LSR}, {"asr", ASR}, {"ror", ROR}};

typedef struct {
    bool isRegister;
    uint32_t type;
    uint32_t shiftValue;
} Shift;

typedef struct {
    bool exists;
    uint8_t immediateValue;
    uint32_t rotateAmount;
} Immediate;

typedef struct {
    bool isConstant;
    Immediate immediate;
    uint32_t rm;
    Shift shift;
} ExtractedOperand;

typedef struct {
    uint32_t condition;
    uint32_t opcode;
    uint32_t rd;
    uint32_t rn;
    ExtractedOperand operand;
} ExtractedInstruction;

/**
 *
 * @param mnemonic
 * @return the corresponding opcode integer for the given string
 */
uint32_t getOpcodeValue(char* mnemonic);

/**
 *
 * @param mnemonic
 * @return the corresponding shift type integer for the given string
 */
uint32_t getShiftTypeValue(char* mnemonic);

/**
 *
 * @param opcode
 * @return true if the given instruction sets flags
 */
uint32_t setsFlags(uint32_t opcode);

/**
 *
 * @param opcode
 * @return true if instruction is mov
 */
uint32_t isMoveInstruction(uint32_t opcode);

/**
 *
 * @param opcode
 * @return true if instruction computes a result
 */
uint32_t computesResult(uint32_t opcode);

/**
 *
 * @param numberOfSetBits
 * @param right
 * @return a mask whose rightmost set bit is the index right, and the number of set bits is numberOfSetBits
 */
uint32_t generateMask(int numberOfSetBits, int right);

/**
 *
 * @param operandString
 * @return true if the given string expression represents a constant value
 */
uint32_t isConstant(char *operandString);

/**
 *
 * @param operandString
 * @return the integer corresponding the the expression (works with hex and decimal)
 */
uint32_t extractConstant(char* operandString);

/**
 * Helper function to initialise an Immediate struct to 0
 * @param imm
 */
void initImm(Immediate* imm);

/**
 *
 * @param constant
 * @return the bits that are rotated right
 */
uint32_t constantSignificantBits(uint32_t constant);

/**
 * Provides the constant value in the format of a 8-bit immediate value with an associated rotation
 * Prints error to stderr if value cannot be represented
 * @param constant
 * @return the corresponding Immediate struct
 */
Immediate processConstant(uint32_t constant);

/**
 * Debug function to check contents of an Immediate struct
 * @param imm
 */
void printConstantOperand(Immediate imm);

/**
 * Extracts the register index from a string of the form "rX"
 * @param registerName
 * @return the register index
 */
uint32_t extractRegisterIndex(char* registerName);

/**
 *
 * @param operandString
 * @param opcode
 * @return Rn index
 */
uint32_t extractRn(char** operandString, uint32_t opcode);

/**
 *
 * @param operandString
 * @param opcode
 * @return Rd index
 */
uint32_t extractRd(char** operandString, uint32_t opcode);

/**
 * Helper function to initialise a Shift struct to 0
 * @param shift
 */
void initShift(Shift* shift);

/**
 * Extract useful shift information from the array of instruction components into a Shift struct
 * @param operandString
 * @param numberOfElements
 * @return corresponding Shift struct
 */
Shift processShift(char **operandString, int numberOfElements);

/**
 * Extract useful operand2 information from the array of instruction components into an ExtractedOperand struct
 * @param operandString
 * @param numberOfElements
 * @return corresponding ExtractedOperand struct
 */
ExtractedOperand processOperand(char** operandString, int numberOfElements);

/**
 * Extract useful instruction information from the array of instruction components into an ExtractedInstruction struct
 * @param instrComponents
 * @param numberOfComponents
 * @return corresponding ExtractedInstruction struct
 */
ExtractedInstruction extractInstruction(char** instrComponents, int numberOfComponents);

/**
 * Sets the bits of the given instruction as follows:
 * value gets written starting from the right index to the left
 * @param instruction
 * @param right
 * @param value
 */
void setBitsAtPosition(instr* instruction, uint32_t right, uint32_t value);

/**
 * Set the correct operand2 bits of the instruction
 * @param instruction
 * @param eop
 */
void getOperandMachineCode(instr *instruction, ExtractedOperand eop);

/**
 * Generate the final machine instruction in little endian format
 * @param extr
 * @return
 */
instr assembleDataProcessing(int numberOfComponents, char **instrComponents);

#endif //ARM11_37_ASSEMBLEDP_H
