#include "execute.h"

FLAG execute(void *decoded, ARM11 *arm11) {
    DecodedInstruction *decodedInstruction = (DecodedInstruction *) decoded;
    if (decodedInstruction->type == H) {
        return STOP;
    } else if (isConditionSatisfied(decodedInstruction->condition, arm11)) {
        switch (decodedInstruction->type) {
            case B:
                //TODO: Add function call
                return BRANCH;
            case DP:
                //TODO: Add function call
            case M:
                multiply((MultiplyInstruction *) decodedInstruction);
                return NORMAL;
            case SDT:
                //TODO: Add function call
                return NORMAL;
            default:
                //TODO: Add error once learned
                return STOP;
        }
    }
}

uint32_t genMask(int start, int end) {
    uint32_t mask = 0;
    for (int i = 31; i >= start; --i) {
        if (i == end) {
            for (int j = end; j >= start; --j) {
                mask = mask | (1 << j);
            }
        }
    }
    return mask;
}

uint32_t extractBit(uint32_t n, int start, int end) {
    uint32_t mask = genMask(start, end);
    n = n & mask;
    n = n >> start;
    return n;
}

bool isConditionSatisfied(Cond condition, ARM11 *arm11) {
    return condition == getCond(CSPR);
}

