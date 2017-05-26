//
// Created by user on 5/25/2017.
//

#ifndef ARM11_37_EXECUTE_H
#define ARM11_37_EXECUTE_H

#include <stdint.h>
#include "emulate.c"

#endif //ARM11_37_EXECUTE_H

#define INSTRUCTION_SIZE = 31;
#define POSITION_I = 25;




enum instruction {DP, MUL, DT, BRANCH};
enum condition {EQ, LE, GE, NE, LT, GT, AL};
enum opcode {AND, EOR, SUB, RSB, ADD, TST, TEQ, CMP, ORR, MOV};

/**
 * Generates a mask in order to select specific bits
 * @param start : start of bit
 * @param end : end of bit
 * @return : returns a 32 bit mask
 */

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


/**
 * Extracts all bits between two specified positions
 * @param n : number to extract from
 * @param start : start position
 * @param end : end position
 * @return
 */

uint32_t extractBit(uint32_t n, int start, int end) {
  uint32_t mask = genMask(start, end);
  n = n&mask;
  n = n >> start;
  return n;
}

void dataProcess(uint32_t parameters[]) {

}

void multiply(uint32_t parameters[]) {
  uint32_t rd = parameters[2];
  uint32_t rn = parameters[3];
  uint32_t rs = parameters[4];
  uint32_t rm = parameters[5];


}

void dataTransfer(uint32_t parameters[]) {

}

void branch(uint32_t parameters[]) {

}
