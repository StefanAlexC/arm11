#include "branch_instruction.h"

uint32_t padNegativeNumber(uint32_t number) {
    return (uint32_t)(number | PADDING);
}

uint32_t invertBits(uint32_t number) {
    return ~number;
}

int32_t twosComplementCovertor(uint32_t number) {
    if (extractBit(number, SIGN_BIT, SIGN_BIT) == 0) {
        return (int32_t) number;
    } else {
        return (int32_t) -(invertBits(padNegativeNumber(number)) + TWOS_COMPLEMENT_OFFSET);
    }
}

void branchInstruction(BranchInstruction * instruction, ARM11* arm11) {
    arm11->PC += (twosComplementCovertor(instruction->offset) << BRANCH_INSTRUCTION_OFFSET);
}
