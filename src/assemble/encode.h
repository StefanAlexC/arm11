//
// Created by Stefan Alexandru Cuturela on 31/05/2017.
//

#ifndef ARM11_37_ENCODE_H_H
#define ARM11_37_ENCODE_H_H

#include "assemble.h"

#define DATA_PROCESSING_INSTRUCTIONS "and eor sub rsb add orr mov tst teq cmp"
#define MULTIPLY_INSTRUCTIONS "mul mla"
#define SINGLE_DATA_TRANSFER_INSTRUCTIONS "ldr str"
#define BRANCH_INSTRUCTIONS "beq bne bge blt bgt ble b"
#define SPECIAL_INSTRUCTIONS "lsl andeq"
#define INSTRUCTION argv[0]

/**
 * Encodes the given operation.
 * @param argc The number of arguments of the instruction.
 * @param argv The array of strings containing all the arguments
 * @return The encoded instruction.
 */
uint32_t encode(int argc, char**argv, Map* labels, int32_t currentOperationNumber);

#endif //ARM11_37_ENCODE_H_H
