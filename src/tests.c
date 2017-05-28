//
// Created by DAVID BUTEREZ on 26/05/17.
//

#include "decode_utils.h"
#include "decode.h"
#include "execute/barrel_shifter.h"
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
//}