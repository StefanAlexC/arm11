#include <ctype.h>
#include "assembleSDT.h"
#include "../emulate/decode/decode_utils.h"

uint32_t getMovCode(uint32_t rd, uint32_t value) {
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

uint32_t constructCode(uint32_t i, uint32_t p, uint32_t u, uint32_t l, uint32_t rn, uint32_t rd, uint32_t offset) {
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

uint32_t intFromString (char value[]) {
    uint32_t i = 0, res = 0;
    while(!isdigit(value[i])) {
        i++;
    }
    while (isdigit(value[i])) {
        res *= BASE;
        res += value[i] - '0';
        i++;
    }

    return res;
}

uint32_t intFromStringHex (char value[]) {
    return (uint32_t)strtol(strtok(value, SEPS), NULL, 0);
}

char lastElement (char value[]) {
    return value[strlen(value)- 1];
}

char firstElement (char value[]) {
    return value[0];
}

uint32_t getShift (char shiftType[]) {
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

uint32_t getOffsetForShiftedRegister (char reg[], char shiftType[], char shiftAmount[], uint32_t* up) {
    setUpBit(up, reg);

    uint32_t offset = 0;
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

uint32_t getOffsetForRegister(char *reg, uint32_t *up) {
    setUpBit(up, reg);

    return intFromString(reg);
}

SDTinstr encodeSDT(int argc, char **argv, int *endAddress, int thisAddress) {

    SDTinstr instruction;
    instruction.hasExpr = false;
    bool isMov = false;
    uint32_t i = 0, p = 1, u = 1, l = 0, instrCode = 0;
    uint32_t rn = 0, rd, offset = 0;

    if(strcmp(argv[0],"ldr") == 0) {
        l = 1;
    }

    if(argc > 3 && lastElement(argv[2]) == ']') {
        p = 0;
    }

    rd = intFromString(argv[1]);
    rn = intFromString(argv[2]);

    if(argc == 3) {
        if(firstElement(argv[2]) == '=') {
            uint32_t value = intFromStringHex(argv[2]);
            if(value < MAX_MOV_OPERAND) {
                isMov = true;
                instrCode = getMovCode(rd, value);
            } else {
                rn = PC;
                offset = (uint32_t)(*endAddress - thisAddress - PIPELINE_OFFSET);
                instruction.hasExpr = true;
                instruction.expression = value;
                *endAddress += WORD_SIZE;
            }
        }
    } else if(argc == 4) {
        if(firstElement(argv[3]) != 'r') {
            offset = intFromStringHex(argv[3]);
            if(argv[3][1] == '-') {
                u = 0;
            }
        } else {
            i = 1;
            offset = getOffsetForRegister(argv[3], &u);
        }
    } else {
        i = 1;
        offset = getOffsetForShiftedRegister(argv[3], argv[4], argv[5], &u);
    }

    if(!isMov) {
        instrCode = constructCode(i, p, u, l, rn, rd, offset);
    }

    instruction.instruction = instrCode;

    return instruction;
}
