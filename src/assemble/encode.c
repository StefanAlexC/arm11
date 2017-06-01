#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "encode.h"
#include "assembleBranch.h"
#include "encode_SDT.h"

bool isInstructionType(char *operation, char *type) {
    return strstr(type, operation) != NULL;;
}

uint32_t bigToLittle(uint32_t number) {
    uint32_t value = 0;
    for (int i = 0; i < BYTE_NUMBER; i++) {
        value <<= BYTE_VALUE;
        value += extractBit(number, i * BYTE_VALUE, (i + 1) * BYTE_VALUE - 1);
    }
    return value;
}

void encode(int argc, char **argv, Map *labels, int32_t currentOperationNumber, int *numberOperations,
            uint32_t remenants[]) {
    uint32_t result = 0;

    if (isInstructionType(INSTRUCTION, DATA_PROCESSING_INSTRUCTIONS)) {
        //TODO: ADD INSTRUCTION
    } else if (isInstructionType(INSTRUCTION, MULTIPLY_INSTRUCTIONS)) {
        //TODO: ADD INSTRUCTION
    } else if (isInstructionType(INSTRUCTION, SINGLE_DATA_TRANSFER_INSTRUCTIONS)) {
        SDTinstr instruction = encodeSDT(argc, argv, numberOperations, (BYTE_VALUE * currentOperationNumber));
        result = instruction.instruction;
        if (instruction.hasExpr) {
            remenants[++NUMBER_REMENANTS] = instruction.expression;
        }
        //TODO: convert remenant into little
    } else if (isInstructionType(INSTRUCTION, BRANCH_INSTRUCTIONS)) {
        result = encodeBranch(argv, labels, currentOperationNumber);
    } else if (isInstructionType(INSTRUCTION, SPECIAL_INSTRUCTIONS)) {
        //TODO: ADD INSTRUCTION
    } else {
        //TODO: ERROR
    }

    printBits(bigToLittle(result));
}

