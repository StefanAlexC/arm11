#define MAX_IMMEDIATE 255
#define REGISTER_LETTER_OFFSET 1

#include <stdbool.h>
#include <stdlib.h>
#include "assembleDP.h"
#include "../emulate/execute/barrel_shifter.h"
#include "../arm11_utils.h"

struct {
    const char* mnemonic;
    Opcode opcode;
} opcodeDictionary[] = {{"and", AND}, {"eor", EOR}, {"sub", SUB}, {"rsb", RSB}, {"add", ADD}, {"tst", TST},
                        {"teq", TEQ}, {"cmp", CMP}, {"orr", ORR}, {"mov", MOV}, {"andeq", ANDEQ}, {"lsl", LSLI}};

struct {
    const char* mnemonic;
    uint32_t shiftType;
} shiftDictionary[] = {{"lsl", LSL}, {"lsr", LSR}, {"asr", ASR}, {"ror", ROR}};

uint32_t getOpcodeValue(char *mnemonic) {
    for (int i = 0; i < sizeof(opcodeDictionary) / sizeof(opcodeDictionary[0]); i++)
        if (!strcmp(mnemonic, opcodeDictionary[i].mnemonic))
            return opcodeDictionary[i].opcode;
    return 0;
}

uint32_t getShiftTypeValue(char *mnemonic) {
    for (int i = 0; i < sizeof(shiftDictionary) / sizeof(shiftDictionary[0]); i++)
        if (!strcmp(mnemonic, shiftDictionary[i].mnemonic))
            return shiftDictionary[i].shiftType;
    return 0;
}

uint32_t setsFlags(uint32_t opcode) {
    return (uint32_t) (opcode == TST || opcode == TEQ || opcode == CMP);
}

uint32_t isMoveInstruction(uint32_t opcode) {
    return (uint32_t) (opcode == MOV);
}

uint32_t isLSLInstruction(uint32_t opcode) {
    return (uint32_t) (opcode == LSLI);
}

uint32_t computesResult(uint32_t opcode) {
    return (uint32_t) (!setsFlags(opcode) && !isMoveInstruction(opcode));
}

uint32_t generateMask(int numberOfSetBits, int right) {
    return (uint32_t) (~(~0 << numberOfSetBits) << right);
}

uint32_t isConstant(char *operandString) {
    return (uint32_t) (strchr(operandString, CONSTANT_EXPRESSION_SIGN) != NULL);
}

uint32_t extractConstant(char *operandString) {
    static const int hexOffset = 3;
    static const int decOffset = 1;
    if (strstr(operandString, "0x") != NULL) {
        char *end;
        return (uint32_t) (strtoul(operandString + hexOffset, &end, 16));
    } else {
        return (uint32_t) (atoi(operandString + decOffset));
    }
}

void initImm(Immediate *imm) {
    imm->immediateValue = 0;
    imm->rotateAmount = 0;
    imm->exists = false;
}

uint32_t constantSignificantBits(uint32_t constant) {
    if (constant <= MAX_IMMEDIATE) {
        return constant;
    }

    uint32_t cursor = constant;
    uint32_t min = cursor;
    for (int i = 0; i <= INSTR_BITS / 2; i++) {
        if (cursor <= min && cursor <= MAX_IMMEDIATE) {
            min = cursor;
        }
        rotateRight(&cursor, 2);
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
        if (init == constant) {
            immediate.exists = true;
            immediate.immediateValue = (uint8_t) bits;
            immediate.rotateAmount = rot;
            return immediate;
        }
        rotateRight(&init, 2);
        rot += 1;
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

uint32_t extractRegisterIndex(char *registerName) {
    return (uint32_t) atoi(registerName + REGISTER_LETTER_OFFSET);
}

uint32_t extractRn(char **operandString, uint32_t opcode) {
    if (setsFlags(opcode)) {
        return extractRegisterIndex(operandString[1]);
    } else if (!isMoveInstruction(opcode)) {
        return extractRegisterIndex(operandString[2]);
    } else {
        return 0;
    }
}

uint32_t extractRd(char **operandString, uint32_t opcode) {
    if (computesResult(opcode) || isMoveInstruction(opcode)) {
        return extractRegisterIndex(operandString[1]);
    }
    return 0;
}

void initShift(Shift *shift) {
    shift->type = 0;
    shift->isRegister = false;
    shift->shiftValue = 0;
}

Shift processShift(char **operandString, int numberOfElements) {
    char *shiftTypeStr = operandString[1];
    char *shiftAmountString = operandString[2];

    Shift shift;
    initShift(&shift);

    if (numberOfElements == 1) {
        return shift;
    }

    shift.type = getShiftTypeValue(shiftTypeStr);
    if (isConstant(shiftAmountString)) {
        shift.isRegister = false;
        shift.shiftValue = (uint32_t) extractConstant(shiftAmountString);
        return shift;
    }

    shift.isRegister = true;
    shift.shiftValue = extractRegisterIndex(shiftAmountString);
    return shift;
}

ExtractedOperand processOperand(char **operandString, int numberOfElements) {
    char *value = operandString[0];

    ExtractedOperand operand;

    if (isConstant(value)) {
        operand.isConstant = 1;
        operand.immediate = processConstant(extractConstant(value));
        return operand;
    }

    operand.isConstant = 0;
    operand.rm = extractRegisterIndex(value);
    operand.shift = processShift(operandString, numberOfElements);

    return operand;
}

void printStrArrContents(char **instrComponents, int numberOfComponents) {
    for (int i = 0; i < numberOfComponents; i++) {
        printf("%s  ", instrComponents[i]);
    }
    printf("\n");
}


char **getLSLProperFormat(char **instrComponents) {
    static const uint32_t LSL_NUMBER_OF_COMPONENTS = 3;
    static const uint32_t SIZE_OF_COMPONENT = 20;

    char **newInstrComponents = (char **) malloc(sizeof(char *) * LSL_NUMBER_OF_COMPONENTS);

    if (!newInstrComponents) {
        perror("Cannot allocate memory!");
        exit(EXIT_FAILURE);
    }

    newInstrComponents[0] = (char *) malloc(sizeof(char) * LSL_NUMBER_OF_COMPONENTS * SIZE_OF_COMPONENT);

    if (!newInstrComponents[0]) {
        free(newInstrComponents);
        perror("Cannot allocate memory!");
        exit(EXIT_FAILURE);
    }

    newInstrComponents[0] = instrComponents[1];
    newInstrComponents[1] = instrComponents[0];
    newInstrComponents[2] = instrComponents[2];

//    printStrArrContents(newInstrComponents, 3);

    return newInstrComponents;
}

uint32_t processOpcode(uint32_t opcode) {
    if (opcode == LSLI) {
        return MOV;
    }
    return opcode;
}

ExtractedInstruction extractInstruction(char **instrComponents, int numberOfComponents) {
    static const uint32_t computeOffset = 3;
    static const uint32_t restOffset = 2;

    char **originalInstrComp = instrComponents;
    ExtractedInstruction extr;

    extr.condition = AL;
    extr.opcode = getOpcodeValue(instrComponents[0]);

    if (setsFlags(extr.opcode) || isMoveInstruction(extr.opcode) || isLSLInstruction(extr.opcode)) {
        uint32_t offset = restOffset;
        if (isLSLInstruction(extr.opcode)) {
            extr.opcode = processOpcode(extr.opcode);
            instrComponents = getLSLProperFormat(instrComponents);
            offset = 0;
        }
        extr.operand = processOperand(instrComponents + offset, numberOfComponents - offset);
    } else {
        extr.operand = processOperand(instrComponents + computeOffset, numberOfComponents - computeOffset);
    }

    extr.rn = extractRn(originalInstrComp, extr.opcode);
    extr.rd = extractRd(originalInstrComp, extr.opcode);

    return extr;
}

void setBitsAtPosition(instr *instruction, uint32_t right, uint32_t value) {
    value <<= right;
    *instruction |= value;
}

void getOperandMachineCode(instr *instruction, ExtractedOperand eop) {
    static const uint32_t ROTATE = 16;
    static const uint32_t IMM = 24;
    static const uint32_t RM = 24;
    static const uint32_t BIT4 = 28;
    static const uint32_t BIT7 = 31;
    static const uint32_t SHIFT = 29;
    static const uint32_t RS = 16;

    static const uint8_t INTEGER_SHIFT_SIZE = 5;

    if (eop.isConstant) {
        setBitsAtPosition(instruction, ROTATE, eop.immediate.rotateAmount);
        setBitsAtPosition(instruction, IMM, eop.immediate.immediateValue);
    } else {
        setBitsAtPosition(instruction, RM, eop.rm);
        if (eop.shift.isRegister) {
            setBitsAtPosition(instruction, RS, eop.shift.shiftValue);
            setBitsAtPosition(instruction, BIT7, 0);
            setBitsAtPosition(instruction, SHIFT, eop.shift.type);
            setBitsAtPosition(instruction, BIT4, 1);
        } else {
//            uint8_t integerBody = (uint8_t) setBit(eop.shift.shiftValue, INTEGER_SHIFT_SIZE - 1, 0);
            uint8_t integerBody = (uint8_t) eop.shift.shiftValue >> 1;
            setBitsAtPosition(instruction, RS, integerBody);

            uint8_t integerHead = (uint8_t) getBit(eop.shift.shiftValue, 0);
            setBitsAtPosition(instruction, BIT7, integerHead);
        }
    }
}

instr assembleDataProcessing(int numberOfComponents, char **instrComponents) {
    static const uint32_t COND = 4;
    static const uint32_t I = 1;
    static const uint32_t OPCODE_HIGHEST = 0;
    static const uint32_t OPCODE = 13;
    static const uint32_t S = 12;
    static const uint32_t RN = 8;
    static const uint32_t RD = 20;

    static const uint8_t OPCODE_SIZE = 4;

    ExtractedInstruction extr = extractInstruction(instrComponents, numberOfComponents);

    instr instruction = 0;

    if (extr.opcode == ANDEQ) {
        return instruction;
    }

    setBitsAtPosition(&instruction, COND, extr.condition);
    setBitsAtPosition(&instruction, I, (uint32_t) extr.operand.isConstant);

    uint8_t opcodeHighest = (uint8_t) extr.opcode >> (OPCODE_SIZE - 1);
    setBitsAtPosition(&instruction, OPCODE_HIGHEST, opcodeHighest);

    uint8_t opcodeRest = (uint8_t) setBit(extr.opcode, OPCODE_SIZE - 1, 0);
    setBitsAtPosition(&instruction, OPCODE, opcodeRest);

    setBitsAtPosition(&instruction, S, setsFlags(extr.opcode));
    setBitsAtPosition(&instruction, RN, extr.rn);
    setBitsAtPosition(&instruction, RD, extr.rd);

    getOperandMachineCode(&instruction, extr.operand);

    return instruction;
}

//int main(void) {
//////    printConstantOperand(processConstant(0xFF0000FF));
//////    printBits(constantSignificantBits(0x0003FC00));
////    printConstantOperand(processConstant(4));
//
////    printf("%i", getShiftTypeValue("ror"));
////
//    char* instrEl1[] = {"mov", "r1", "#4"};
//    char* instrEl2[] = {"mov", "r2", "#2"};
//    char* instrEl3[] = {"add", "r3", "r1", "r2"};
//    char* instrEl4[] = {"add", "r4", "r3", "#4"};
//    char* instrEl5[] = {"sub", "r5", "r4", "r3", "lsr", "r2"};
//    extractInstruction(instrEl, 6);

//    uint32_t i = 0;
//    printBits(i);
//    setBitsAtPosition(&i, 2, 15);
//    setBitsAtPosition(&i, 2, 1);
//    printBits(i);

///////////////////////    opt_add05    /////////////////////
//    printBits(assembleDataProcessing(3, instrEl1));
//    printBits(assembleDataProcessing(3, instrEl2));
//    printBits(assembleDataProcessing(4, instrEl3));
//    printBits(assembleDataProcessing(4, instrEl4));
//    printBits(assembleDataProcessing(6, instrEl5));
//
//    printf("\n");
//
///////////////////////    or02    /////////////////////
//    char* instrEl6[] = {"mov", "r1", "#0x0F"};
//    char* instrEl7[] = {"mov", "r2", "#0xAB"};
//    char* instrEl8[] = {"orr", "r3", "r1", "r2"};
//
//    printBits(assembleDataProcessing(extractInstruction(instrEl6, 3)));
//    printBits(assembleDataProcessing(extractInstruction(instrEl7, 3)));
//    printBits(assembleDataProcessing(extractInstruction(instrEl8, 4)));
//
//    printf("\n");
//
///////////////////////    add01   /////////////////////
////
//    char* instrEl9[] = {"mov", "r1", "#1"};
//    char* instrEl10[] = {"add", "r2", "r1", "#2"};
//    printBits(assembleDataProcessing(extractInstruction(instrEl9, 3)));
//    printBits(assembleDataProcessing(extractInstruction(instrEl10, 4)));
//
//    printf("\n");
//
///////////////////////    add02   /////////////////////
//    char* instrEl11[] = {"mov", "r1", "#1"};
//    char* instrEl12[] = {"mov", "r2", "#2"};
//    char* instrEl13[] = {"add", "r3", "r1", "r2"};
//    printBits(assembleDataProcessing(extractInstruction(instrEl11, 3)));
//    printBits(assembleDataProcessing(extractInstruction(instrEl12, 3)));
//    printBits(assembleDataProcessing(extractInstruction(instrEl13, 4)));
//
//    printf("\n");
//
///////////////////////    add03   /////////////////////
//    char* instrEl14[] = {"mov", "r1", "#1"};
//    char* instrEl15[] = {"add", "r1", "r1", "r1"};
//
//    printBits(assembleDataProcessing(extractInstruction(instrEl14, 3)));
//    printBits(assembleDataProcessing(extractInstruction(instrEl15, 4)));
//
//    printf("\n");
//
///////////////////////    add04   /////////////////////
//    char* instrEl16[] = {"mov", "r1", "#1"};
//    char* instrEl17[] = {"mov", "r2", "#2"};
//    char* instrEl18[] = {"add", "r3", "r1", "r2"};
//    char* instrEl19[] = {"add", "r4", "r3", "#4"};
//
//    printBits(assembleDataProcessing(extractInstruction(instrEl16, 3)));
//    printBits(assembleDataProcessing(extractInstruction(instrEl17, 3)));
//    printBits(assembleDataProcessing(extractInstruction(instrEl18, 4)));
//    printBits(assembleDataProcessing(extractInstruction(instrEl19, 4)));
//
//    printf("\n");
//
///////////////////////    and01   /////////////////////
//    char* instrEl20[] = {"mov", "r1", "#0xFF"};
//    char* instrEl21[] = {"and", "r2", "r1", "#0xAB"};
//
//    printBits(assembleDataProcessing(extractInstruction(instrEl20, 3)));
//    printBits(assembleDataProcessing(extractInstruction(instrEl21, 4)));
//
//    printf("\n");
//
///////////////////////    and02   /////////////////////
//    char* instrEl22[] = {"mov", "r1", "#0x0F"};
//    char* instrEl23[] = {"mov", "r2", "#0xAB"};
//    char* instrEl24[] = {"and", "r3", "r1", "r2"};
//
//    printBits(assembleDataProcessing(extractInstruction(instrEl22, 3)));
//    printBits(assembleDataProcessing(extractInstruction(instrEl23, 3)));
//    printBits(assembleDataProcessing(extractInstruction(instrEl24, 4)));
//
//    printf("\n");
//
///////////////////////    eor01   /////////////////////
//    char* instrEl25[] = {"mov", "r1", "#0x0F"};
//    char* instrEl26[] = {"mov", "r2", "#0xFF"};
//    char* instrEl27[] = {"eor", "r3", "r1", "r2"};
//
//    printBits(assembleDataProcessing(extractInstruction(instrEl25, 3)));
//    printBits(assembleDataProcessing(extractInstruction(instrEl26, 3)));
//    printBits(assembleDataProcessing(extractInstruction(instrEl27, 4)));
//
//    printf("\n");
//
///////////////////////    eor02   /////////////////////
//    char* instrEl28[] = {"mov", "r1", "#0xFF"};
//    char* instrEl29[] = {"eor", "r2", "r1", "#0x0F"};
//
//    printBits(assembleDataProcessing(extractInstruction(instrEl28, 3)));
//    printBits(assembleDataProcessing(extractInstruction(instrEl29, 4)));
//
//    printf("\n");
//
///////////////////////    mov03   /////////////////////
//    char* instrEl30[] = {"mov", "r1", "#0x0F"};
//    char* instrEl31[] = {"mov", "r2", "#0xFF"};
//    char* instrEl32[] = {"mov", "r3", "#0xAB"};
//    char* instrEl33[] = {"mov", "r4", "#0xCD"};
//
//    printBits(assembleDataProcessing(extractInstruction(instrEl30, 3)));
//    printBits(assembleDataProcessing(extractInstruction(instrEl31, 3)));
//    printBits(assembleDataProcessing(extractInstruction(instrEl32, 3)));
//    printBits(assembleDataProcessing(extractInstruction(instrEl33, 3)));
//
//    printf("\n");
//
///////////////////////    mov04   /////////////////////
//    char* instrEl34[] = {"mov", "r2", "#4128768"};
//
////    printConstantOperand(processConstant(4128768));
//    printBits(assembleDataProcessing(extractInstruction(instrEl34, 3)));
//
//    printf("\n");

///////////////////////    mov05   /////////////////////
//    char* instrEl35[] = {"mov", "r1", "#1"};
//    char* instrEl36[] = {"mov", "r2", "r1"};
//
//    printBits(assembleDataProcessing(extractInstruction(instrEl35, 3)));
//    printBits(assembleDataProcessing(extractInstruction(instrEl36, 3)));
//
//    printf("\n");

///////////////////////    mov06   /////////////////////
//    char* instrEl37[] = {"mov", "r2", "#163840"};
//
//    printBits(assembleDataProcessing(extractInstruction(instrEl37, 3)));
//
//    printf("\n");

///////////////////////    mov07   /////////////////////
//    char* instrEl38[] = {"mov", "r0", "#50331648"};
//
//    printBits(assembleDataProcessing(extractInstruction(instrEl38, 3)));
//
//    printf("\n");

///////////////////////    sub02   /////////////////////
//    char* instrEl39[] = {"mov", "r1", "#0xFF"};
//    char* instrEl40[] = {"sub", "r2", "r1", "#0xFF"};
//
//    printBits(assembleDataProcessing(extractInstruction(instrEl39, 3)));
//    printBits(assembleDataProcessing(extractInstruction(instrEl40, 4)));
//
////    printConstantOperand(processConstant(255));
//
//    printf("\n");

//    char* instrEl41[] = {"andeq", "r0", "r0", "r0"};
//    printBits(assembleDataProcessing(extractInstruction(instrEl41, 4)));



//    char* instrEl42[] = {"lsl", "r1", "#1"};
//    printBits(assembleDataProcessing(3, instrEl42));
//
//    char* instrEl43[] = {"lsl", "r1", "#0x1f"};
//    printBits(assembleDataProcessing(3, instrEl43));
//}
