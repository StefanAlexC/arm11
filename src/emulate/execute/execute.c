#include "execute.h"
#include "../../arm11_utils.h"

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
            return true;
        }
        default:
        {
            perror("Invalid Condition Code");
            exit(EXIT_FAILURE);
        }
    }
}

