//
// Created by DAVID BUTEREZ on 26/05/17.
//

#include <assert.h>
#include "decode/decode_utils.h"
#include "decode/decode.h"
#include "execute/barrel_shifter.h"
#include "stdio.h"
#include "execute/execute_dp.h"
#include "ARM11.h"
#include "emulate.h"

void initializeForTesting(ARM11 *arm11, uint32_t rn, uint32_t rnVal, uint32_t rm, uint32_t rmVal, uint32_t rs, uint32_t rsVal) {
    int i;
    for (i = 0; i < MEMORY_SIZE; i++) {
        arm11->memory[i] = 0;
    }
    for (i = 0; i < REGISTER_SIZE; i++) {
        arm11->registers[i] = 0;
    }

    arm11->registers[rn] = rnVal;
    arm11->registers[rm] = rmVal;
    arm11->registers[rs] = rsVal;
}

void testAndImm(void) {
    uint32_t i = 111;
    printBits(i);
    rotateRight(&i, 4);
    printBits(i);
    uint32_t j = 100;
    printBits(j);
    printBits(i & j);
    printf("EXPECTED: %u\n", i & j);

    instr instruction = 0b11100010000101010111001001101111;
    ARM11 arm;
    initializeForTesting(&arm, 5, 100, 0, 0, 0, 0);
    uint32_t rd = 7;

    void* instrPtr = decode(instruction);
    DataProcessingInstruction* dpi = (DataProcessingInstruction *) instrPtr;
    dataProcessing(dpi, &arm);
    print(&arm);

    //EXPECTED: 4;
    assert(arm.registers[rd] == 4);

    printf("\n");
    printBits(536870912);
    printf("\n----------------------------------------------------------------------------------\n");
}

void testAndRegShiftByConstant(void) {
    uint32_t i = 10;
    printBits(i);
    shiftLeft(&i, 3);
    printBits(i);
    uint32_t j = 116;
    printBits(j);
    printBits(i & j);
    printf("EXPECTED: %u\n", i & j);

    instr instruction = 0b11100000000101011000000110001010;
    ARM11 arm;
    initializeForTesting(&arm, 5, 116, 10, 10, 0, 0);
    uint32_t rd = 8;

    void* instrPtr = decode(instruction);
    DataProcessingInstruction* dpi = (DataProcessingInstruction *) instrPtr;
    dataProcessing(dpi, &arm);
    print(&arm);

    //EXPECTED: 80;
    assert(arm.registers[rd] == 80);

    printf("\n");
    printf("\n----------------------------------------------------------------------------------\n");
}

void testAndRegShiftByRegister(void) {
    uint32_t i = 759;
    printBits(i);
    shiftRight(&i, 4);
    printBits(i);
    uint32_t j = 116;
    printBits(j);
    printBits(i & j);
    printf("EXPECTED: %u\n", i & j);

    instr instruction = 0b11100000000101010100101100111010;
    ARM11 arm;
    initializeForTesting(&arm, 5, 116, 10, 759, 11, 4);
    uint32_t rd = 4;

    void* instrPtr = decode(instruction);
    DataProcessingInstruction* dpi = (DataProcessingInstruction *) instrPtr;
    dataProcessing(dpi, &arm);
    print(&arm);

//    EXPECTED: 36;
    assert(arm.registers[rd] == 36);

    printf("\n");
    printf("\n----------------------------------------------------------------------------------\n");
}

void testEorImm(void) {
    uint32_t i = 111;
    printBits(i);
    rotateRight(&i, 4);
    printBits(i);
    uint32_t j = 100;
    printBits(j);
    printBits(i ^ j);
    printf("EXPECTED: %u\n", i ^ j);

    instr instruction = 0b11100010001101010111001001101111;
    ARM11 arm;
    initializeForTesting(&arm, 5, 100, 0, 0, 0, 0);
    uint32_t rd = 7;

    void* instrPtr = decode(instruction);
    DataProcessingInstruction* dpi = (DataProcessingInstruction *) instrPtr;
    dataProcessing(dpi, &arm);
    print(&arm);

    //EXPECTED: 4026531938;
    assert(arm.registers[rd] == 4026531938);

    printf("\n");
    printf("\n----------------------------------------------------------------------------------\n");
}

void testEorRegShiftByConstant(void) {
    uint32_t i = 10;
    printBits(i);
    shiftLeft(&i, 3);
    printBits(i);
    uint32_t j = 116;
    printBits(j);
    printBits(i ^ j);
    printf("EXPECTED: %u\n", i ^ j);

    instr instruction = 0b11100000001101011000000110001010;
    ARM11 arm;
    initializeForTesting(&arm, 5, 116, 10, 10, 0, 0);
    uint32_t rd = 8;

    void* instrPtr = decode(instruction);
    DataProcessingInstruction* dpi = (DataProcessingInstruction *) instrPtr;
    dataProcessing(dpi, &arm);
    print(&arm);

    //EXPECTED: 36;
    assert(arm.registers[rd] == 36);

    printf("\n");
    printf("\n----------------------------------------------------------------------------------\n");
}

void testEorRegShiftByRegister(void) {
    uint32_t i = 759;
    printBits(i);
    shiftRight(&i, 4);
    printBits(i);
    uint32_t j = 116;
    printBits(j);
    printBits(i ^ j);
    printf("EXPECTED: %u\n", i ^ j);

    instr instruction = 0b11100000001101010100101100111010;
    ARM11 arm;
    initializeForTesting(&arm, 5, 116, 10, 759, 11, 4);
    uint32_t rd = 4;

    void* instrPtr = decode(instruction);
    DataProcessingInstruction* dpi = (DataProcessingInstruction *) instrPtr;
    dataProcessing(dpi, &arm);
    print(&arm);

//    EXPECTED: 91;
    assert(arm.registers[rd] == 91);

    printf("\n");
    printf("\n----------------------------------------------------------------------------------\n");
}

void testOrrImm(void) {
    uint32_t i = 111;
    printBits(i);
    rotateRight(&i, 4);
    printBits(i);
    uint32_t j = 100;
    printBits(j);
    printBits(i | j);
    printf("EXPECTED: %u\n", i | j);

    instr instruction = 0b11100011100101010111001001101111;
    ARM11 arm;
    initializeForTesting(&arm, 5, 100, 0, 0, 0, 0);
    uint32_t rd = 7;

    void* instrPtr = decode(instruction);
    DataProcessingInstruction* dpi = (DataProcessingInstruction *) instrPtr;
    dataProcessing(dpi, &arm);
    print(&arm);

//    //EXPECTED: 4026531942;
    assert(arm.registers[rd] == 4026531942);

    printf("\n");
    printf("\n----------------------------------------------------------------------------------\n");
}

void testOrrRegShiftByConstant(void) {
    uint32_t i = 10;
    printBits(i);
    shiftLeft(&i, 3);
    printBits(i);
    uint32_t j = 116;
    printBits(j);
    printBits(i | j);
    printf("EXPECTED: %u\n", i | j);

    instr instruction = 0b11100001100101011000000110001010;
    ARM11 arm;
    initializeForTesting(&arm, 5, 116, 10, 10, 0, 0);
    uint32_t rd = 8;

    void* instrPtr = decode(instruction);
    DataProcessingInstruction* dpi = (DataProcessingInstruction *) instrPtr;
    dataProcessing(dpi, &arm);
    print(&arm);

    //EXPECTED: 116;
    assert(arm.registers[rd] == 116);

    printf("\n");
    printf("\n----------------------------------------------------------------------------------\n");
}

void testOrrRegShiftByRegister(void) {
    uint32_t i = 759;
    printBits(i);
    shiftRight(&i, 4);
    printBits(i);
    uint32_t j = 116;
    printBits(j);
    printBits(i | j);
    printf("EXPECTED: %u\n", i | j);

    instr instruction = 0b11100001100101010100101100111010;
    ARM11 arm;
    initializeForTesting(&arm, 5, 116, 10, 759, 11, 4);
    uint32_t rd = 4;

    void* instrPtr = decode(instruction);
    DataProcessingInstruction* dpi = (DataProcessingInstruction *) instrPtr;
    dataProcessing(dpi, &arm);
    print(&arm);

//    EXPECTED: 127;
    assert(arm.registers[rd] == 127);

    printf("\n");
    printf("\n----------------------------------------------------------------------------------\n");
}

void testTstImm(void) {
    uint32_t i = 111;
    printBits(i);
    rotateRight(&i, 4);
    printBits(i);
    uint32_t j = 100;
    printBits(j);
    printBits(i & j);
    printf("EXPECTED: %u\n", i & j);

    instr instruction = 0b11100011000101010111001001101111;
    ARM11 arm;
    initializeForTesting(&arm, 5, 100, 0, 0, 0, 0);
    uint32_t rd = 7;

    void* instrPtr = decode(instruction);
    DataProcessingInstruction* dpi = (DataProcessingInstruction *) instrPtr;
    dataProcessing(dpi, &arm);
    print(&arm);

    //EXPECTED: 0;
    assert(arm.registers[rd] == 0);

    printf("\n");
    printf("\n----------------------------------------------------------------------------------\n");
}

void testTstImm2(void) {
    uint32_t i = 111;
    printBits(i);
    rotateRight(&i, 4);
    printBits(i);
    uint32_t j = 0;
    printBits(j);
    printBits(i & j);
    printf("EXPECTED: %u\n", i & j);

    instr instruction = 0b11100011000101010111001000000000;
    ARM11 arm;
    initializeForTesting(&arm, 5, 100, 0, 0, 0, 0);
    uint32_t rd = 7;

    void* instrPtr = decode(instruction);
    DataProcessingInstruction* dpi = (DataProcessingInstruction *) instrPtr;
    dataProcessing(dpi, &arm);
    print(&arm);

    //EXPECTED: 0;
    assert(arm.registers[CPSR_INDEX] == 1073741824);

    printf("\n");
    printf("\n----------------------------------------------------------------------------------\n");
}

void testTstRegShiftByConstant(void) {
    uint32_t i = 10;
    printBits(i);
    shiftLeft(&i, 3);
    printBits(i);
    uint32_t j = 116;
    printBits(j);
    printBits(i & j);
    printf("EXPECTED: %u\n", i & j);

    instr instruction = 0b11100001000101011000000110001010;
    ARM11 arm;
    initializeForTesting(&arm, 5, 116, 10, 10, 0, 0);
    uint32_t rd = 8;

    void* instrPtr = decode(instruction);
    DataProcessingInstruction* dpi = (DataProcessingInstruction *) instrPtr;
    dataProcessing(dpi, &arm);
    print(&arm);

    //EXPECTED: 0;
    assert(arm.registers[rd] == 0);

    printf("\n");
    printf("\n----------------------------------------------------------------------------------\n");
}

void testTstRegShiftByRegister(void) {
    uint32_t i = 759;
    printBits(i);
    shiftRight(&i, 4);
    printBits(i);
    uint32_t j = 116;
    printBits(j);
    printBits(i & j);
    printf("EXPECTED: %u\n", i & j);

    instr instruction = 0b11100001000101010100101100111010;
    ARM11 arm;
    initializeForTesting(&arm, 5, 116, 10, 759, 11, 4);
    uint32_t rd = 4;

    void* instrPtr = decode(instruction);
    DataProcessingInstruction* dpi = (DataProcessingInstruction *) instrPtr;
    dataProcessing(dpi, &arm);
    print(&arm);

//    EXPECTED: 0;
    assert(arm.registers[rd] == 0);

    printf("\n");
    printf("\n----------------------------------------------------------------------------------\n");
}

void testTeqImm(void) {
    uint32_t i = 111;
    printBits(i);
    rotateRight(&i, 4);
    printBits(i);
    uint32_t j = 100;
    printBits(j);
    printBits(i ^ j);
    printf("EXPECTED: %u\n", i ^ j);

    instr instruction = 0b11100011001101010111001001101111;
    ARM11 arm;
    initializeForTesting(&arm, 5, 100, 0, 0, 0, 0);
    uint32_t rd = 7;

    void* instrPtr = decode(instruction);
    DataProcessingInstruction* dpi = (DataProcessingInstruction *) instrPtr;
    dataProcessing(dpi, &arm);
    print(&arm);

    //EXPECTED: 0;
    assert(arm.registers[rd] == 0);

    printf("\n");
    printf("\n----------------------------------------------------------------------------------\n");
}

void testTeqRegShiftByConstant(void) {
    uint32_t i = 10;
    printBits(i);
    shiftLeft(&i, 3);
    printBits(i);
    uint32_t j = 116;
    printBits(j);
    printBits(i ^ j);
    printf("EXPECTED: %u\n", i ^ j);

    instr instruction = 0b11100001001101011000000110001010;
    ARM11 arm;
    initializeForTesting(&arm, 5, 116, 10, 10, 0, 0);
    uint32_t rd = 8;

    void* instrPtr = decode(instruction);
    DataProcessingInstruction* dpi = (DataProcessingInstruction *) instrPtr;
    dataProcessing(dpi, &arm);
    print(&arm);

    //EXPECTED: 0;
    assert(arm.registers[rd] == 0);

    printf("\n");
    printf("\n----------------------------------------------------------------------------------\n");
}

void testTeqRegShiftByRegister(void) {
    uint32_t i = 759;
    printBits(i);
    shiftRight(&i, 4);
    printBits(i);
    uint32_t j = 116;
    printBits(j);
    printBits(i ^ j);
    printf("EXPECTED: %u\n", i ^ j);

    instr instruction = 0b11100001001101010100101100111010;
    ARM11 arm;
    initializeForTesting(&arm, 5, 116, 10, 759, 11, 4);
    uint32_t rd = 4;

    void* instrPtr = decode(instruction);
    DataProcessingInstruction* dpi = (DataProcessingInstruction *) instrPtr;
    dataProcessing(dpi, &arm);
    print(&arm);

//    EXPECTED: 0;
    assert(arm.registers[rd] == 0);

    printf("\n");
    printf("\n----------------------------------------------------------------------------------\n");
}

void testMovImm(void) {
    uint32_t i = 111;
    printBits(i);
    rotateRight(&i, 4);
    printBits(i);
    printf("EXPECTED: %u\n", i);

    instr instruction = 0b11100011101101010111001001101111;
    ARM11 arm;
    initializeForTesting(&arm, 0, 0, 0, 0, 0, 0);
    uint32_t rd = 7;

    void* instrPtr = decode(instruction);
    DataProcessingInstruction* dpi = (DataProcessingInstruction *) instrPtr;
    dataProcessing(dpi, &arm);
    print(&arm);

    //EXPECTED: 4026531846;
    assert(arm.registers[rd] == 4026531846);

    printf("\n");
    printf("\n----------------------------------------------------------------------------------\n");
}

void testMovRegShiftByConstant(void) {
    uint32_t i = 10;
    printBits(i);
    shiftLeft(&i, 3);
    printBits(i);
    printf("EXPECTED: %u\n", i);

    instr instruction = 0b11100001101101011000000110001010;
    ARM11 arm;
    initializeForTesting(&arm, 5, 116, 10, 10, 0, 0);
    uint32_t rd = 8;

    void* instrPtr = decode(instruction);
    DataProcessingInstruction* dpi = (DataProcessingInstruction *) instrPtr;
    dataProcessing(dpi, &arm);
    print(&arm);

    //EXPECTED: 80;
    assert(arm.registers[rd] == 80);

    printf("\n");
    printf("\n----------------------------------------------------------------------------------\n");
}

void testMovRegShiftByRegister(void) {
    uint32_t i = 759;
    printBits(i);
    shiftRight(&i, 4);
    printBits(i);
    printf("EXPECTED: %u\n", i);

    instr instruction = 0b11100001101101010100101100111010;
    ARM11 arm;
    initializeForTesting(&arm, 5, 116, 10, 759, 11, 4);
    uint32_t rd = 4;

    void* instrPtr = decode(instruction);
    DataProcessingInstruction* dpi = (DataProcessingInstruction *) instrPtr;
    dataProcessing(dpi, &arm);
    print(&arm);

//    EXPECTED: 47;
    assert(arm.registers[rd] == 47);

    printf("\n");
    printf("\n----------------------------------------------------------------------------------\n");
}

void testAddImm(void) {
    uint32_t i = 111;
    printBits(i);
    rotateRight(&i, 4);
    printBits(i);
    uint32_t j = 100;
    printBits(j);
    printBits(i + j);
    printf("EXPECTED: %u\n", i + j);

    instr instruction = 0b11100010100101010111001001101111;
    ARM11 arm;
    initializeForTesting(&arm, 5, 100, 0, 0, 0, 0);
    uint32_t rd = 7;

    void* instrPtr = decode(instruction);
    DataProcessingInstruction* dpi = (DataProcessingInstruction *) instrPtr;
    dataProcessing(dpi, &arm);
    print(&arm);
//
    //EXPECTED: 4026531946;
    assert(arm.registers[rd] == 4026531946);

    printf("\n");
    printf("\n----------------------------------------------------------------------------------\n");
}

void testAddImm2(void) {
    uint32_t i = 111;
    printBits(i);
    rotateRight(&i, 4);
    printBits(i);
    uint32_t j = 0b11111111111111111111111111111111;
    printBits(j);
    printBits(i + j);
    printf("EXPECTED: %u\n", i + j);

    instr instruction = 0b11100010100101010111001001101111;
    ARM11 arm;
    initializeForTesting(&arm, 5, 0b11111111111111111111111111111111, 0, 0, 0, 0);
    uint32_t rd = 7;

    void* instrPtr = decode(instruction);
    DataProcessingInstruction* dpi = (DataProcessingInstruction *) instrPtr;
    dataProcessing(dpi, &arm);
    print(&arm);
//
    //EXPECTED: 4026531845;
    assert(arm.registers[rd] == 4026531845);

    printf("\n");
    printf("\n----------------------------------------------------------------------------------\n");
}

void testAddRegShiftByConstant(void) {
    uint32_t i = 10;
    printBits(i);
    shiftLeft(&i, 3);
    printBits(i);
    uint32_t j = 116;
    printBits(j);
    printBits(i + j);
    printf("EXPECTED: %u\n", i + j);

    instr instruction = 0b11100000100101011000000110001010;
    ARM11 arm;
    initializeForTesting(&arm, 5, 116, 10, 10, 0, 0);
    uint32_t rd = 8;

    void* instrPtr = decode(instruction);
    DataProcessingInstruction* dpi = (DataProcessingInstruction *) instrPtr;
    dataProcessing(dpi, &arm);
    print(&arm);

    //EXPECTED: 196;
    assert(arm.registers[rd] == 196);

    printf("\n");
    printf("\n----------------------------------------------------------------------------------\n");
}

void testAddRegShiftByRegister(void) {
    uint32_t i = 759;
    printBits(i);
    shiftRight(&i, 4);
    printBits(i);
    uint32_t j = 116;
    printBits(j);
    printBits(i + j);
    printf("EXPECTED: %u\n", i + j);

    instr instruction = 0b11100000100101010100101100111010;
    ARM11 arm;
    initializeForTesting(&arm, 5, 116, 10, 759, 11, 4);
    uint32_t rd = 4;

    void *instrPtr = decode(instruction);
    DataProcessingInstruction *dpi = (DataProcessingInstruction *) instrPtr;
    dataProcessing(dpi, &arm);
    print(&arm);

//    EXPECTED: 163;
    assert(arm.registers[rd] == 163);

    printf("\n");
    printf("\n----------------------------------------------------------------------------------\n");
}

void testSubImm(void) {
    uint32_t i = 112;
    printBits(i);
    rotateRight(&i, 4);
    printBits(i);
    uint32_t j = 10;
    printBits(j);
    printBits(j - i);
    printf("EXPECTED: %u\n", j - i);

    instr instruction = 0b11100010010101010111001001110000;
    ARM11 arm;
    initializeForTesting(&arm, 5, 10, 0, 0, 0, 0);
    uint32_t rd = 7;

    void* instrPtr = decode(instruction);
    DataProcessingInstruction* dpi = (DataProcessingInstruction *) instrPtr;
    dataProcessing(dpi, &arm);
    print(&arm);

    //EXPECTED: 3;
    assert(arm.registers[rd] == 3);

    printf("\n");
    printf("\n----------------------------------------------------------------------------------\n");
}

void testSubRegShiftByConstant(void) {
    uint32_t i = 10;
    printBits(i);
    shiftLeft(&i, 3);
    printBits(i);
    uint32_t j = 116;
    printBits(j);
    printBits(j - i);
    printf("EXPECTED: %u\n", j - i);

    instr instruction = 0b11100000010101011000000110001010;
    ARM11 arm;
    initializeForTesting(&arm, 5, 116, 10, 10, 0, 0);
    uint32_t rd = 8;

    void* instrPtr = decode(instruction);
    DataProcessingInstruction* dpi = (DataProcessingInstruction *) instrPtr;
    dataProcessing(dpi, &arm);
    print(&arm);

    //EXPECTED: 36;
    assert(arm.registers[rd] == 36);

    printf("\n");
    printf("\n----------------------------------------------------------------------------------\n");
}

void testSubRegShiftByRegister(void) {
    uint32_t i = 759;
    printBits(i);
    shiftRight(&i, 4);
    printBits(i);
    uint32_t j = 116;
    printBits(j);
    printBits(j - i);
    printf("EXPECTED: %u\n", j - i);

    instr instruction = 0b11100000010101010100101100111010;
    ARM11 arm;
    initializeForTesting(&arm, 5, 116, 10, 759, 11, 4);
    uint32_t rd = 4;

    void* instrPtr = decode(instruction);
    DataProcessingInstruction* dpi = (DataProcessingInstruction *) instrPtr;
    dataProcessing(dpi, &arm);
    print(&arm);

//    EXPECTED: 69;
    assert(arm.registers[rd] == 69);

    printf("\n");
    printf("\n----------------------------------------------------------------------------------\n");
}

void testRsbImm(void) {
    uint32_t i = 240;
    printBits(i);
    rotateRight(&i, 4);
    printBits(i);
    uint32_t j = 10;
    printBits(j);
    printBits(i - j);
    printf("EXPECTED: %u\n", i - j);

    instr instruction = 0b11100010011101010111001011110000;
    ARM11 arm;
    initializeForTesting(&arm, 5, 10, 0, 0, 0, 0);
    uint32_t rd = 7;

    void* instrPtr = decode(instruction);
    DataProcessingInstruction* dpi = (DataProcessingInstruction *) instrPtr;
    dataProcessing(dpi, &arm);
    print(&arm);

    //EXPECTED: 5;
    assert(arm.registers[rd] == 5);

    printf("\n");
    printf("\n----------------------------------------------------------------------------------\n");
}

void testRsbRegShiftByConstant(void) {
    uint32_t i = 211;
    printBits(i);
    shiftLeft(&i, 3);
    printBits(i);
    uint32_t j = 116;
    printBits(j);
    printBits(i - j);
    printf("EXPECTED: %u\n", i - j);

    instr instruction = 0b11100000011101011000000110001010;
    ARM11 arm;
    initializeForTesting(&arm, 5, 116, 10, 211, 0, 0);
    uint32_t rd = 8;

    void* instrPtr = decode(instruction);
    DataProcessingInstruction* dpi = (DataProcessingInstruction *) instrPtr;
    dataProcessing(dpi, &arm);
    print(&arm);

    //EXPECTED: 1572;
    assert(arm.registers[rd] == 1572);

    printf("\n");
    printf("\n----------------------------------------------------------------------------------\n");
}

void testRsbRegShiftByRegister(void) {
    uint32_t i = 3213;
    printBits(i);
    shiftRight(&i, 4);
    printBits(i);
    uint32_t j = 116;
    printBits(j);
    printBits(i - j);
    printf("EXPECTED: %u\n", i - j);

    instr instruction = 0b11100000011101010100101100111010;
    ARM11 arm;
    initializeForTesting(&arm, 5, 116, 10, 3213, 11, 4);
    uint32_t rd = 4;
//
    void* instrPtr = decode(instruction);
    DataProcessingInstruction* dpi = (DataProcessingInstruction *) instrPtr;
    dataProcessing(dpi, &arm);
    print(&arm);

//    EXPECTED: 84;
    assert(arm.registers[rd] == 84);

    printf("\n");
    printf("\n----------------------------------------------------------------------------------\n");
}

void testCmpImm(void) {
    uint32_t i = 112;
    printBits(i);
    rotateRight(&i, 4);
    printBits(i);
    uint32_t j = 7;
    printBits(j);
    printBits(j - i);
    printf("EXPECTED: %u\n", j - i);

    instr instruction = 0b11100011010101010111001001110000;
    ARM11 arm;
    initializeForTesting(&arm, 5, 7, 0, 0, 0, 0);
    uint32_t rd = 7;

    void* instrPtr = decode(instruction);
    DataProcessingInstruction* dpi = (DataProcessingInstruction *) instrPtr;
    dataProcessing(dpi, &arm);
    print(&arm);

    //EXPECTED: 0;
    assert(arm.registers[rd] == 0);

    printf("\n");
    printf("\n----------------------------------------------------------------------------------\n");
}

void testCmpRegShiftByConstant(void) {
    uint32_t i = 10;
    printBits(i);
    shiftLeft(&i, 3);
    printBits(i);
    uint32_t j = 0b1010000;
    printBits(j);
    printBits(j - i);
    printf("EXPECTED: %u\n", j - i);

    instr instruction = 0b11100001010101011000000110001010;
    ARM11 arm;
    initializeForTesting(&arm, 5, 0b1010000, 10, 10, 0, 0);
    uint32_t rd = 8;

    void* instrPtr = decode(instruction);
    DataProcessingInstruction* dpi = (DataProcessingInstruction *) instrPtr;
    dataProcessing(dpi, &arm);
    print(&arm);

    //EXPECTED: 0;
    assert(arm.registers[rd] == 0);

    printf("\n");
    printf("\n----------------------------------------------------------------------------------\n");
}

void testCmpRegShiftByRegister(void) {
    uint32_t i = 759;
    printBits(i);
    shiftRight(&i, 4);
    printBits(i);
    uint32_t j = 116;
    printBits(j);
    printBits(j - i);
    printf("EXPECTED: %u\n", j - i);

    instr instruction = 0b11100001010101010100101100111010;
    ARM11 arm;
    initializeForTesting(&arm, 5, 0b101111, 10, 759, 11, 4);
    uint32_t rd = 4;

    void* instrPtr = decode(instruction);
    DataProcessingInstruction* dpi = (DataProcessingInstruction *) instrPtr;
    dataProcessing(dpi, &arm);
    print(&arm);

//    EXPECTED: 0;
    assert(arm.registers[rd] == 0);

    printf("\n");
    printf("\n----------------------------------------------------------------------------------\n");
}

//int main(void) {
////  10100000100111100111000001111000  / Data Processing
//    instr instr1 = 0xA09E7078;
////  10100010000111100111000001111000 / Data Processing
//    instr instr2 = 0xA21E7078;
////  10100000000111100111000001101000 / Data Processing
//    instr instr3 = 0xA01E7068;
////  10100000000111100111000001111000 / Data Processing
//    instr instr4 = 0xA01E7078;
////  10100100000111100111000001111000 / SDT
//    instr instr5 = 0xA41E7078;
////  10100000000111100111000010011000 / Multiply
//    instr instr6 = 0xA01E7098;
////  10101010000111100111000010011000 / Branch
//    instr instr7 = 0xA81E7098;
//
//    testInstr(instr1);
//    testInstr(instr2);
//    testInstr(instr3);
//    testInstr(instr4);
//    testInstr(instr5);
//    testInstr(instr6);
//    testInstr(instr7);
//
//    testStructs(decode(instr1));
//    testStructs(decode(instr2));
//    testStructs(decode(instr3));
//    testStructs(decode(instr4));
//    testStructs(decode(instr5));
//    testStructs(decode(instr6));
//    testStructs(decode(instr7));
//
//    uint32_t i = 0b11000110110101101101011011010110;
//    printBits(i);
//    int carry = shiftLeft(&i, 4);
//    printBits(i);
//    printf("\n%i\n\n", carry);
//
//    i = 0b11010110110101101101011011011110;
//    printBits(i);
//    carry = shiftRight(&i, 4);
//    printBits(i);
//    printf("\n%i\n\n", carry);
//
//    i = 0b11010110110101101101011011010110;
//    printBits(i);
//    carry = arithmeticShiftRight(&i, 4);
//    printBits(i);
//    printf("\n%i\n\n", carry);
//
//    i = 0b11000110110101101101011011010110;
//    printBits(i);
//    printBits(i);
//    printf("\n%i\n\n", carry);
//
//    i = 0b11000110110101101101011011010110;
//    printBits(i);
//    carry = rotateRight(&i, 4);
//    printBits(i);
//    printf("\n%i\n\n", carry);
//
//
////  10100010100111100111 0010 10001010 / Data Processing, immediate value 138, rotate 2 * 2
//    instr instr8 = 0xA29E728A;
//
////  101000 0 0100111100111 10100 10 0 1010 / Data Processing, op2 is register, constant amount 20, shift type asr, Rm = 10
//    instr instr9 = 0xA09E7A4A;
//
////  101000 0 0100111100111 1101 0 01 1 1010 / Data Processing, op2 is register, Rs = 13, shift type lsr, Rm = 10
//    instr instr10 = 0xA09E7D3A;
//
//    testStructs(decode(instr8));
//    testStructs(decode(instr9));
//    testStructs(decode(instr10));



//    testAndImm();
//    testAndRegShiftByConstant();
//    testAndRegShiftByRegister();
//
//    testEorImm();
//    testEorRegShiftByConstant();
//    testEorRegShiftByRegister();
//
//    testOrrImm();
//    testOrrRegShiftByConstant();
//    testOrrRegShiftByRegister();
//
//    testTstImm();
//    testTstImm2();
//    testTstRegShiftByConstant();
//    testTstRegShiftByRegister();
//
//    testTeqImm();
//    testTeqRegShiftByConstant();
//    testTeqRegShiftByRegister();
//
//    testMovImm();
//    testMovRegShiftByConstant();
//    testMovRegShiftByRegister();
//
//    testAddImm();
//    testAddImm2();
//    testAddRegShiftByConstant();
//    testAddRegShiftByRegister();
//
//    testSubImm();
//    testSubRegShiftByConstant();
//    testSubRegShiftByRegister();
//
//    testRsbImm();
//    testRsbRegShiftByConstant();
//    testRsbRegShiftByRegister();
//
//    testCmpImm();
//    testCmpRegShiftByConstant();
//    testCmpRegShiftByRegister();
//}