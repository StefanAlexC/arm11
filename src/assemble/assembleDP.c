//
// Created by DAVID BUTEREZ on 30/05/17.
//

#define MAX_IMMEDIATE 255

#include <stdbool.h>
#include <stdlib.h>
#include "assembleDP.h"
#include "../emulate/execute/barrel_shifter.h"

struct {
    const char* mnemonic;
    Opcode opcode;
} dictionary[] = {{"and", AND}, {"eor", EOR}, {"sub", SUB}, {"rsb", RSB}, {"add", ADD}, {"tst", TST}, {"teq", TEQ}, {"cmp", CMP}, {"orr", ORR}, {"mov", MOV}};

typedef struct {
    bool isRegister;
    ShiftType type;
    uint32_t shiftValue;
} Shift;

typedef struct {
    bool exists;
    uint8_t immediateValue;
    uint32_t rotateAmount;
} Immediate;

typedef struct {
    bool isConstant;
    Immediate immediate;
    uint32_t rm;
    Shift shift;
} ExtractedOperand;




uint32_t isConstantOperand(char *operandString) {
    return (uint32_t) (strchr(operandString, CONSTANT_EXPRESSION_SIGN) != NULL);
}

uint32_t getOpcodeValue(char* mnemonic) {
    for (int i = 0;  i < sizeof(dictionary) / sizeof(dictionary[0]);  i++)
        if (!strcmp(mnemonic, dictionary[i].mnemonic))
            return dictionary[i].opcode;
    return 0;
}

uint32_t getSetBitValue(uint32_t opcode) {
    return (uint32_t) (opcode == TST || opcode == TEQ || opcode == CMP);
}

uint32_t generateMask(int numberOfSetBits, int right) {
    return (uint32_t) (~(~0 << numberOfSetBits) << right);
}

uint32_t extractConstant(char* operandString) {
    static const int hexOffset = 3;
    static const int decOffset = 1;
    if (strstr(operandString, "0x") != NULL) {
        char* end;
        return (uint32_t) (strtoul(operandString + hexOffset, &end, 16));
    } else {
        return (uint32_t) (atoi(operandString + decOffset));
    }
}

void initImm(Immediate* imm) {
    imm->immediateValue = 0;
    imm->rotateAmount = 0;
    imm->exists = false;
}

uint32_t constantSignificantBits(uint32_t constant) {
//    uint32_t l = lowestSetBitIndex(constant);
//    uint32_t h = highestSetBitIndex(constant);
//    uint32_t msk = generateMask(h - l + 1, l);
//    return mask(constant, msk);

    uint32_t min = constant;
    for (int i = 0; i <= INSTR_BITS; i++) {
        rotateRight(&constant, 1);
        if (constant <= min) {
            min = constant;
        }
    }

    return min;
}

Immediate processConstant(uint32_t constant) {
    Immediate immediate;
    initImm(&immediate);

    uint32_t bits = constantSignificantBits(constant);

    if (bits > MAX_IMMEDIATE) {
        perror("Value cannot be represented!");
        return immediate;
    }

    uint32_t init = bits;
    uint32_t rot = 0;
    for (int i = 0; i <= 30; i++) {
        rotateRight(&init, 2);
        rot += 1;
        if (init == constant) {
            immediate.exists = true;
            immediate.immediateValue = (uint8_t) bits;
            immediate.rotateAmount = rot;
            return immediate;
        }
    }

    if (!immediate.exists) {
        perror("Value cannot be represented!");
    }

    return immediate;
}

void printConstantOperand(Immediate imm) {
    printf("Value can be represented: %s\n", imm.exists ? "true" : "false");
    printf("Immediate value %u\n", imm.immediateValue);
    printf("Shift amount: %u\n", imm.rotateAmount);
}

ExtractedOperand processOperand(char* operandString) {
    ExtractedOperand operand;
    if (isConstantOperand(operandString)) {
        operand.isConstant = 1;
        operand.immediate = processConstant(extractConstant(operandString));
        return operand;
    }
}

instr assembleDataProcessing(char** instrComponents, int numberOfComponents) {
    uint32_t condition = AL;
    char* operandString = instrComponents[numberOfComponents - 1];
    uint32_t immediateBit = isConstantOperand(operandString);
    uint32_t opcode = getOpcodeValue(instrComponents[0]);
    uint32_t rn = 0;
    uint32_t rd = 0;
    ExtractedOperand operand = processOperand(operandString);

}

//int main(void) {
////    printConstantOperand(processConstant(0xFF0000FF));
////    printBits(constantSignificantBits(0x0003FC00));
//    printConstantOperand(processConstant(0xC0000034));
//}