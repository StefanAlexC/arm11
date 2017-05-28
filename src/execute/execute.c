#include "execute.h"

FLAG execute(char decoded, struct ARM11* arm11) {
    enum FLAG temp = NORMAL;
    if (decoded == 'a') {
        temp = STOP;
        return temp;
    }
    arm11->registers[10] += 1;
    return temp;
}

uint32_t genMask(int start, int end) {
    uint32_t mask = 0;
    for(int i = 31; i >= start; --i) {
        if(i == end) {
            for(int j = end; j >= start; --j) {
                mask = mask|(1 << j);
            }
        }
    }
    return mask;
}

uint32_t extractBit(uint32_t n, int start, int end) {
    uint32_t mask = genMask(start, end);
    n = n&mask;
    n = n >> start;
    return n;
}

bool isConditionSatisfied(uint32_t condition) {

    uint32_t register_CMP = ARM11.registers[14];
    //uint32_t* register_CMP = (uint32_t *)((struct ARM11 *arm11)->
    // (register_CMP));
    bool Z_clear = extractBit(register_CMP, 30, 30) == 0;
    bool Z_set = extractBit(register_CMP, 30, 30) != 0;
    bool N_equals_V = extractBit(register_CMP, 31, 31) ==
                      extractBit(register_CMP, 28, 28);
    bool N_not_equal_V = extractBit(register_CMP, 31, 31) !=
                         extractBit(register_CMP, 28, 28);

    switch(condition) {
        case EQ:
            return (Z_set);
        case NE:
            return (Z_clear);
        case GE:
            return (N_equals_V);
        case LT:
            return (N_not_equal_V);
        case GT:
            return (Z_clear&&N_equals_V);
        case LE:
            return (Z_set||N_not_equal_V);
        case AL:
            return (true);
    }

    //return (!(register_CMP >> 27)&condition != 0);

}

/**
* Executes instruction based on instruction type
* @param instruction : instruction to be executed
* @param type : an int describing the type of instruction
* (either DP, MUL, DT or BRANCH);
*/

void execute(uint32_t instruction, uint32_t type) {

    /**
     * parameters: an array of ints describing parameters of instruction type
     * Layout for:
     * DP: [Cond (bit 27-31), I (bit 25), OpCode (bit 21-24), S (bit 20), Rn (bit
     * 16-19),Rd (bit 12-15), Operand 2( bit 0-11)];
     * MUL: [Cond (bit 27-31), A (bit 21), S (bit 20), Rd (bit 16-19), Rn (bit
     * 12-15), Rs (bit 8-11), Rm (bit 0-3)];
     * DT: [Cond (bit 27-31), P (bit 24), U (bit 23), Rn (bit 16-19), Rd (bit
     * 12-15), Offset (bit 0-11)];
     * BRANCH: [Cond (bit 27-31), Offset (bit 0-23)];
     */

    switch (type) {

        case DP: {
            uint32_t parameters[] = {extractBit(instruction, 27, 31),
                                     extractBit(instruction, 25, 25),
                                     extractBit(instruction, 21, 24),
                                     extractBit(instruction, 20, 20),
                                     extractBit(instruction, 16, 19),
                                     extractBit(instruction, 12, 15),
                                     extractBit(instruction, 0, 11)};
            dataProcess(parameters);
            break;
        }
        case MUL: {
            uint32_t parameters[] = {extractBit(instruction, 27, 31),
                                     extractBit(instruction, 21, 21),
                                     extractBit(instruction, 20, 20),
                                     extractBit(instruction, 16, 19),
                                     extractBit(instruction, 12, 15),
                                     extractBit(instruction, 8, 11),
                                     extractBit(instruction, 0, 3)};
            multiply(parameters);
            break;
        }
        case DT: {
            uint32_t parameters[] = {extractBit(instruction, 27, 31),
                                     extractBit(instruction, 24, 24),
                                     extractBit(instruction, 23, 23),
                                     extractBit(instruction, 20, 20),
                                     extractBit(instruction, 16, 19),
                                     extractBit(instruction, 12, 15),
                                     extractBit(instruction, 0, 11)};
            dataTransfer(parameters);
            break;
        }
        case BRANCH: {
            uint32_t parameters[] = {extractBit(instruction, 27, 31),
                                     extractBit(instruction, 0, 23)};
            branch(parameters);
            break;
        }
    }
}
