#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "encode.h"
#include "assembleBranch.h"
#include "assembleSDT.h"
#include "assembleMUL.h"
#include "assembleDP.h"

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

    if (isInstructionType(INSTRUCTION, BRANCH_INSTRUCTIONS)) {

        result = encodeBranch(argv, labels, currentOperationNumber);

    } else if (isInstructionType(INSTRUCTION, MULTIPLY_INSTRUCTIONS)) {

        result = assembleMultiply(argv);

    } else if (isInstructionType(INSTRUCTION, SINGLE_DATA_TRANSFER_INSTRUCTIONS)) {

        SDTinstr instruction = encodeSDT(argc, argv, numberOperations, (BYTE_NUMBER * currentOperationNumber));
        result = instruction.instruction;
        if (instruction.hasExpr) {
            remenants[++NUMBER_REMENANTS] = bigToLittle(instruction.expression);
        }

    } else if (isInstructionType(INSTRUCTION, DATA_PROCESSING_INSTRUCTIONS)) {

        result = bigToLittle(assembleDataProcessing(argc, argv));

    } else {

        //TODO: ERROR

    }

    //printBits(bigToLittle(result));
    printAsChar(bigToLittle(result));
}

