#include "execute.h"

FLAG execute(void *decoded, ARM11 *arm11) {
    DecodedInstruction *decodedInstruction = (DecodedInstruction *) decoded;
    if (decodedInstruction->type == H) {
        return STOP;
    } else if (isConditionSatisfied(decodedInstruction->condition, arm11)) {
        switch (decodedInstruction->type) {
            case B:
                branchInstruction((BranchInstruction *) decodedInstruction, arm11);
                return BRANCH;
            case DP:
                dataProcessing((DataProcessingInstruction *) decodedInstruction, arm11);
                return NORMAL;
            case M:
                multiply((MultiplyInstruction *) decodedInstruction, arm11);
                return NORMAL;
            case SDT:
                dataTransfer(*((SingleDataTransferInstruction *) decodedInstruction), arm11);
                return NORMAL;
            default:
                //TODO: Add error once learned
                return STOP;
        }
    } else {
        return NORMAL;
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
    //printf("Condition: %i == %i\n", condition, CSPR_SIGNIFICANT_BITS);
    //return condition == getCond(CSPR_SIGNIFICANT_BITS);

    uint32_t CSPRBitN = extractBit(CPSR_SIGNIFICANT_BITS,3, 3);
    uint32_t CSPRBitZ = extractBit(CPSR_SIGNIFICANT_BITS,2, 2);
    uint32_t CSPRBitV = extractBit(CPSR_SIGNIFICANT_BITS,0, 0);

    bool ZSet = (CSPRBitZ != 0);
    bool Zclear = (CSPRBitZ == 0);
    bool NEqualV = (CSPRBitN == CSPRBitV);
    bool NNotEqualV = (CSPRBitN != CSPRBitV);

    switch (condition) {
        case EQ:
        {
           return (ZSet);
        }
        case NE:
        {
            return (Zclear);
        }
        case GE:
        {
            return (NEqualV);
        }
        case LT:
        {
            return (NNotEqualV);
        }
        case GT:
        {
            return (Zclear&&NEqualV);
        }
        case LE:
        {
            return (ZSet||NNotEqualV);
        }
        case AL:
        {
            return (true);
        }
        default:
        {
            //TODO: Add exception is provided with invalid Condition code
            printf("Exception: Invalid Condition Code");
            return (false);
        }
    }
}

