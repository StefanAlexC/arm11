#include <ctype.h>
#include "encode_SDT.h"

uint32_t getMovCode(int rd, int value) {
    uint32_t instrCode;

    instrCode = AL_COND;
    instrCode <<= PATTERN_SIZE;
    instrCode += MOV_BITS_27_26;
    instrCode <<= FLAG_SIZE;
    instrCode += MOV_I;
    instrCode <<= OPCODE_SIZE;
    instrCode += MOV_CODE;
    instrCode <<= FLAG_SIZE;
    instrCode += MOV_S;
    instrCode <<= REG_SIZE;
    instrCode <<= REG_SIZE;
    instrCode += rd;
    instrCode <<= OFFSET_SIZE;
    instrCode += value;

    return instrCode;
}

uint32_t constructCode(uint32_t i, uint32_t p, uint32_t u, uint32_t l, int rn, int rd, int offset) {
    uint32_t instrCode;

    instrCode = AL_COND;
    instrCode <<= PATTERN_SIZE;
    instrCode += BITS_27_26;
    instrCode <<= FLAG_SIZE;
    instrCode += i;
    instrCode <<= FLAG_SIZE;
    instrCode += p;
    instrCode <<= FLAG_SIZE;
    instrCode += u;
    instrCode <<= PATTERN_SIZE;
    instrCode += BITS_22_21;
    instrCode <<= FLAG_SIZE;
    instrCode += l;
    instrCode <<= REG_SIZE;
    instrCode += rn;
    instrCode <<= REG_SIZE;
    instrCode += rd;
    instrCode <<= OFFSET_SIZE;
    instrCode += offset;

    return instrCode;
}

int intFromString (char value[]) {
    int i = 0, res = 0;
    while(!isdigit(value[i])) {
        i++;
    }
    while (isdigit(value[i])) {
        res *= 10;
        res += value[i] - '0';
        i++;
    }

    return res;
}

int intFromStringHex (char value[]) {
    return (int)strtol(strtok(value, SEPS), NULL, 0);
}

char lastElement (char value[]) {
    return value[strlen(value)- 1];
}

char firstElement (char value[]) {
    return value[0];
}

int getShift (char shiftType[]) {
    if(strcmp(shiftType,"lsl") == 0){
        return LSL;
    } else if(strcmp(shiftType,"lsr") == 0) {
        return LSR;
    } else if(strcmp(shiftType,"asr") == 0) {
        return ASR;
    }else {
        return ROR;
    }
}

void setUpBit (uint32_t* up, char reg[]) {
    if(firstElement(reg) == '-') {
        *up = 0;
    }
}

int getOffsetForShiftedRegister (char reg[], char shiftType[], char shiftAmount[], uint32_t* up) {
    setUpBit(up, reg);

    int offset = 0;
    offset += intFromString(shiftAmount);
    if(firstElement(shiftAmount) == 'r') {
        offset <<= 1;
    }
    offset <<= SHIFT_TYPE;
    offset += getShift(shiftType);
    offset <<=1;
    if(firstElement(shiftAmount) == 'r') {
        offset += 1;
    }
    offset <<= REG_SIZE;
    offset += intFromString(reg);
    return offset;
}

int getOffsetForRegister(char *reg, uint32_t *up) {
    setUpBit(up, reg);

    return intFromString(reg);
}

//TODO: used for testing
void printBits(uint32_t instruction) {
    uint32_t i, mask;
    mask = 1;
    mask <<= 31;
    for(i = 0; i < 32; i++) {
        printf("%u ", (instruction & mask) > 0);
        instruction <<= 1;
    }
}

SDTinstr encodeSDT(int argc, char **argv, int *endAddress, int thisAddress) {

    SDTinstr instruction;
    bool isMov = false;
    uint32_t i = 1, p = 1, u = 1, l = 0, instrCode = 0;
    int rn = 0, rd, offset = 0;

    if(strcmp(argv[0],"ldr") == 0) {
        l = 1;
    }

    if( argc >=3 && lastElement(argv[3]) != ']') {
        p = 0;
    }

    rd = intFromString(argv[1]);
    rn = intFromString(argv[2]);

    if(argc == 3) {
        if(firstElement(argv[2]) == '=') {
            int value = intFromStringHex(argv[2]);
            if(value < MAX_MOV_OPERAND) {
                instrCode = getMovCode(rd, value);
                isMov = true;
            } else {
                rn = PC;
                offset = *endAddress - thisAddress - PIPELINE_OFFSET;
                instruction.hasExpr = true;
                instruction.expression = value;
                *endAddress += WORD_SIZE;
            }
        }
    } else if(argc == 4) {
        if(firstElement(argv[3]) != 'r') {
            offset = intFromString(argv[3]);
        } else {
            offset = getOffsetForRegister(argv[3], &u);
        }
    } else {
        offset = getOffsetForShiftedRegister(argv[3], argv[4], argv[5], &u);
    }

    if(!isMov) {
        instrCode = constructCode(i, p, u, l, rn, rd, offset);
    }

    instruction.instruction = instrCode;

    //TODO: test
    printBits(instrCode);

    return instruction;
}

int main(int argc, char **argv) {
    argc = 3;
    argv[0] = "ldr";
    argv[1] = "r2";
    argv[2] = "[r1]";

    encodeSDT(argc, argv, &argc, 8);
}