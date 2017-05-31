#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "encode.h"
#include "assembleBranch.h"

bool isInstructionType (char* operation, char* type) {
    return strstr(operation, type) != NULL;
}

int32_t encode(int argc, char**argv, Map* labels) {

    if (isInstructionType(INSTRUCTION, DATA_PROCESSING_INSTRUCTIONS)) {

    } else if (isInstructionType(INSTRUCTION, MULTIPLY_INSTRUCTIONS)) {

    } else if (isInstructionType(INSTRUCTION, SINGLE_DATA_TRANSFER_INSTRUCTIONS)) {

    } else if (isInstructionType(INSTRUCTION, BRANCH_INSTRUCTIONS)) {
        encodeBranch(argc, argv, labels);
    } else if (isInstructionType(INSTRUCTION, SPECIAL_INSTRUCTIONS)) {

    }

}

