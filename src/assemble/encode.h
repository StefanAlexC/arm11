//
// Created by Stefan Alexandru Cuturela on 31/05/2017.
//

#ifndef ARM11_37_ENCODE_H_H
#define ARM11_37_ENCODE_H_H

#include "assemble.h"
#include "../arm11_utils.h"

#define DATA_PROCESSING_INSTRUCTIONS "and eor sub rsb add orr mov tst teq cmp lsl andeq"
#define MULTIPLY_INSTRUCTIONS "mul mla"
#define SINGLE_DATA_TRANSFER_INSTRUCTIONS "ldr str"
#define BRANCH_INSTRUCTIONS "beq bne bge blt bgt ble b"
#define INSTRUCTION argv[0]
#define NUMBER_REMENANTS remenants[0]

/**
 * Calculates whether or not the given operation matches the type of instruction.
 * @param operation The string containing the keyword of the instruction.
 * @param type The type of instruction we want to check.
 * @return A boolean stating if operation is included in type.
 */
bool isInstructionType (char *operation, char *type);

/**
 * Converts a 32bit number in Big Endian format to Little Endian format
 * @param number The 32bit number in Big Endian we wish to convert
 * @return The converted 32bit number in Little Endian format.
 */
uint32_t bigToLittle(uint32_t number);

/**
 * Encodes the given operation.
 * @param argc The number of arguments of the instruction.
 * @param argv The array of strings containing all the arguments
 * @return The encoded instruction.
 */
void encode(int argc, char**argv, Map* labels, int32_t currentOperationNumber, int* numberOperations, uint32_t remenants[]);

#endif //ARM11_37_ENCODE_H_H
