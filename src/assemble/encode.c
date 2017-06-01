#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "encode.h"
#include "assembleBranch.h"

bool isInstructionType (char *operation, char *type) {
    return strstr(type, operation) != NULL;;
}

int32_t encode(int argc, char**argv, Map* labels, int32_t currentOperationNumber) {

    if (isInstructionType(INSTRUCTION, DATA_PROCESSING_INSTRUCTIONS)) {
        return 1;
    } else if (isInstructionType(INSTRUCTION, MULTIPLY_INSTRUCTIONS)) {
        return 2;
    } else if (isInstructionType(INSTRUCTION, SINGLE_DATA_TRANSFER_INSTRUCTIONS)) {
        return 3;
    } else if (isInstructionType(INSTRUCTION, BRANCH_INSTRUCTIONS)) {
        return encodeBranch(argv, labels, currentOperationNumber);
    } else if (isInstructionType(INSTRUCTION, SPECIAL_INSTRUCTIONS)) {
        return 4;
    } else {
        //TODO: ERROR
        return -1;
    }

}

