//
// Created by DAVID BUTEREZ on 26/05/17.
//

#include "decode_utils.h"
#include "decode.h"
#include "barrel_shifter.h"
#include "stdio.h";

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
//}