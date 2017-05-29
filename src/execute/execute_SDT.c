//
// Created by Ada Cristina Stoenica on 28/05/2017.
//

#include "execute_SDT.h"

uint32_t shiftRegister(uint32_t offset, ARM11* arm11) {
    uint32_t* reg = &arm11->registers[extractBit(offset, 0, 3)];
    int shift =  extractBit(offset, 5, 6);
    uint32_t shiftAmount;
    if(extractBit(offset, 3, 4) == 0) {
        shiftAmount = extractBit(offset, 7, 11);
    } else {
        shiftAmount = extractBit(arm11->registers[extractBit(offset, 8, 11)], 0, 7);
    }

    switch(shift) {
        case LSL: {
            return shiftLeft(reg, shiftAmount);
        }
        case LSR: {
            return shiftRight(reg, shiftAmount);
        }
        case ASR: {
            return arithmeticShiftRight(reg, shiftAmount);
        }
        case ROR: {
            return rotateRight(reg, shiftAmount);
        }
        default: return 0;
    }
}

uint32_t getAddress(uint32_t up, uint32_t base, uint32_t offset) {
    if(up == 1) {
        return base + offset;
    } else {
        return base - offset;
    }
}

//TODO: might need errorrs if address is not multiple of 4
void fromMemory(uint32_t mem, uint32_t* reg, ARM11* arm11) {
    *reg = littleToBig(mem, arm11);
}

//TODO: check endaianess
void toMemory(uint32_t address, uint32_t value, ARM11* arm11) {
    if(validMemoryAccess(address)) {
        int j;
        for (j = 0; j < BYTE_NUMBER; j--) {
            arm11->memory[address + j] = (uint8_t) value;
            value >>= BYTE_VALUE;
        }
    }
}

void dataTransfer(SingleDataTransferInstruction instruction, ARM11* arm11) {
    uint32_t offset = instruction.offset;
    uint32_t* baseReg = &arm11->registers[instruction.baseInstr.Rn];
    uint32_t address = *baseReg;
    uint32_t* transferReg = &arm11->registers[instruction.baseInstr.Rd];

    if(instruction.immediate == 1) {
        offset = shiftRegister(offset, arm11);
    }

    if(instruction.prePost == 1) {
        address = getAddress(instruction.up, *baseReg, offset);
    }

    if(instruction.load == 1) {
        fromMemory(address, transferReg, arm11);
    } else {
        toMemory(address, *transferReg, arm11);
    }

    if(instruction.prePost == 0) {
        *baseReg += offset;
    }
}
