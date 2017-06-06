//
// Created by DAVID BUTEREZ on 25/05/17.
//

#include "decode.h"

static const uint32_t BRANCH_BITS = 2;
static const uint32_t SDT_BITS = 1;

bool isDataProcessingInstruction(instr instruction) {
    // check that bits 27-26 are 0
    if (mask(instruction, BITS_27_26_MASK)) {
        return false;
    }
    // check if bits 24-22 are 0
    int checkBits = mask(instruction, BITS_24_22_MASK);
    if (checkBits) {
        return true;
    }
    // if I is 1 then instr is Data Processing
    int immediateBit = mask(instruction, IMMEDIATE_OP_MASK);
    if (immediateBit) {
        return true;
    }
    // if I is 0 then check bits 4 and 7
    int bit4 = getBit(instruction, 4);
    int bit7 = getBit(instruction, 7);
    return !bit4 || (bit4 && !bit7);
}

bool isSingleDataTransferInstruction(instr instruction) {
    int checkBits = mask(instruction, BITS_27_26_MASK);
    return checkBits == SDT_BITS;
}

bool isBranchInstruction(instr instruction) {
    int checkBits = mask(instruction, BITS_27_26_MASK);
    return checkBits == BRANCH_BITS;
}

bool isMultiplyInstruction(instr instruction) {
    return !isDataProcessingInstruction(instruction) && !isSingleDataTransferInstruction(instruction)
           && !isBranchInstruction(instruction);
}

bool isHaltInstruction(instr instruction) {
    return instruction == 0;
}

//void testInstr(instr instruction) {
//    printf("Data Processing Instr: %i ; Multiply: %i ; SDT: %i ; Branch: %i; Halt: %i",
//           isDataProcessingInstruction(instruction),
//           isMultiplyInstruction(instruction),
//           isSingleDataTransferInstruction(instruction),
//           isBranchInstruction(instruction),
//           isHaltInstruction(instruction));
//}

InstrType getType(instr instruction) {
    if (instruction == 0) {
        return H;
    } else if (isDataProcessingInstruction(instruction)) {
        return DP;
    } else if (isMultiplyInstruction(instruction)) {
        return M;
    } else if (isSingleDataTransferInstruction(instruction)) {
        return SDT;
    } else if (isBranchInstruction(instruction)) {
        return B;
    } else {
        perror("Unrecognised instruction!");
        exit(EXIT_FAILURE);
    }
}

void initOperand(Operand* op) {
    op->Rm = 0;
    op->I = 0;
    op->immediateValue = 0;
    op->shiftAmount = 0;
    op->shiftType = getShiftType(0);
}

Operand processOperand2(uint32_t operand, uint32_t immediateBit) {
    Operand result;
    initOperand(&result);

    if (immediateBit) {
        uint32_t immediateValue = mask(operand, LAST_8_BITS_MASK);
        uint32_t rotate = mask(operand, BITS_11_8_MASK);

        result.I = 1;
        result.immediateValue = immediateValue;
        result.shiftAmount = rotate * 2;
        return result;
    }

    result.I = 0;
    result.Rm = mask(operand, RM_MASK);
    result.bit4 = getBit(operand, 4);
    result.shiftType = getShiftType(mask(operand, BITS_7_6_MASK));
    result.shiftAmount = mask(operand, BITS_11_7_MASK);
    result.Rs = mask(operand, RS_MASK);

    return result;
}

void printOperand(Operand operand) {
    if (operand.I) {
        printf("  Operand2 is an immediate value\n  Immediate value: %i\n  Rotate right amount: %i", operand.immediateValue, operand.shiftAmount);
    } else {
        printf("  Operand2 is a register\n  Rm: %i\n", operand.Rm);
        if (!operand.bit4) {
            printf("  Shift by constant amount: %i\n  Shift type: %s\n", operand.shiftAmount, getShiftTypeString(operand.shiftType));
        } else {
            printf("  Shift by register\n  Rs: %i\n  Shift type: %s\n", operand.Rs, getShiftTypeString(operand.shiftType));
        }
    }
}

DataProcessingInstruction* decodeDP(DecodedInstruction* base, instr instruction) {
    base->Rd = getRdBits(instruction);
    base->Rn = getRnBits(instruction);

    DataProcessingInstruction* dpi;
    dpi = malloc(sizeof(DataProcessingInstruction));

    dpi->baseInstr = *base;
    dpi->set = getSetBit(instruction);
    dpi->immediate = getImmediateBit(instruction);
    dpi->opcode = getOpcode(getOpcodeBits(instruction));
    dpi->operand2 = processOperand2(getOperand2Bits(instruction), dpi->immediate);

    return dpi;
}

MultiplyInstruction* decodeM(DecodedInstruction* base, instr instruction) {
    base->Rd = getRdMultiplyBits(instruction);
    base->Rn = getRnMultiplyBits(instruction);

    MultiplyInstruction* mi;
    mi = malloc(sizeof(MultiplyInstruction));

    mi->baseInstr = *base;
    mi->set = getSetBit(instruction);
    mi->accumulate = getAccumulateBit(instruction);
    mi->Rs = getRsBits(instruction);
    mi->Rm = getRmBits(instruction);

    return mi;
}

SingleDataTransferInstruction* decodeSDT(DecodedInstruction* base, instr instruction) {
    base->Rd = getRdBits(instruction);
    base->Rn = getRnBits(instruction);

    SingleDataTransferInstruction* sdti;
    sdti = malloc(sizeof(SingleDataTransferInstruction));

    sdti->baseInstr = *base;
    sdti->immediate = getImmediateBit(instruction);
    sdti->load = getLoadBits(instruction);
    sdti->offset = getSDTOffset(instruction);
    sdti->prePost = getPrePostBit(instruction);
    sdti->up = getUpBit(instruction);

    return sdti;
}

BranchInstruction* decodeB(DecodedInstruction* base, instr instruction) {
    BranchInstruction* bi;
    bi = malloc(sizeof(BranchInstruction));

    bi->baseInstr = *base;
    bi->offset = getBranchOffset(instruction);

    return bi;
}

DecodedInstruction* decodeH(DecodedInstruction* base) {
    DecodedInstruction* hi;
    hi = malloc(sizeof(DecodedInstruction));

    hi->type = H;

    return hi;
}

void* decode(instr instruction) {
    DecodedInstruction base;
    base.type = getType(instruction);
    base.condition = getCond(getConditionBits(instruction));
    if (base.type == DP) {
        return decodeDP(&base, instruction);
    } else if (base.type == M) {
        return decodeM(&base, instruction);
    } else if (base.type == SDT) {
        return decodeSDT(&base, instruction);
    } else if (base.type == B) {
        return decodeB(&base, instruction);
    } else {
        return decodeH(&base);
    }
}

void printDPI(DataProcessingInstruction *dp) {
    printf("Data contained in Data Processing instr: \n Cond: %s\n I: %i\n Opcode: %s\n S: %i\n Rn: %i\n Rd: %i\n",
           getCondString(dp->baseInstr.condition), dp->immediate, getOpcodeString((dp->opcode)), dp->set, dp->baseInstr.Rn, dp->baseInstr.Rd);
    printf(" Operand data:\n");
    printOperand(dp->operand2);
    printf("\n");
}

void printMI(MultiplyInstruction *mi) {
    printf("Data contained in Multiply instr: \n Cond: %s\n A: %i\n S: %i\n Rd: %i\n Rn: %i\n Rs: %i\n Rm: %i\n ",
           getCondString(mi->baseInstr.condition), mi->accumulate, mi->set, mi->baseInstr.Rd, mi->baseInstr.Rn, mi->Rs, mi->Rm);
}

void printSDTI(SingleDataTransferInstruction *sdti) {
    printf("Data contained in SDT instr: \n Cond: %s\n I: %i\n P: %i\n U: %i\n L: %i\n Rn: %i\n Rd: %i\n Offset: %i\n ",
           getCondString(sdti->baseInstr.condition), sdti->immediate, sdti->prePost, sdti->up, sdti->load, sdti->baseInstr.Rn, sdti->baseInstr.Rd, sdti->offset);
}

void printBI(BranchInstruction *bi) {
    printf("Data contained in Branch instr: \n Cond: %s\n offset: %i\n",
           getCondString(bi->baseInstr.condition), bi->offset);
}

void testStructs(void* instrPtr) {
    DecodedInstruction *dec = (DecodedInstruction *) instrPtr;
    if (dec->type == DP) {
        DataProcessingInstruction *dp = (DataProcessingInstruction *) instrPtr;
        printDPI(dp);
    } else if (dec->type == M) {
        MultiplyInstruction *mi = (MultiplyInstruction *) instrPtr;
        printMI(mi);
    } else if (dec->type == SDT) {
        SingleDataTransferInstruction *sdti = (SingleDataTransferInstruction *) instrPtr;
        printSDTI(sdti);
    } else if (dec->type == B){
        BranchInstruction *bi = (BranchInstruction *) instrPtr;
        printBI(bi);
    } else {
        printf("Halt instruction!");
    }
    printf("\n");
}
