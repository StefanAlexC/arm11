//
// Created by user on 5/25/2017.
//

#include "../emulate.h"
#include <stdlib.h>
#include <stdio.h>


uint32_t* registerFind(uint32_t r) {
  uint32_t* baseRegister = &(ARM11.registers);
  while(baseRegister != r) {
    ++baseRegister;
  }
  return baseRegister;
}

void multiply(uint32_t parameters[]) {
  uint32_t* rd = registerFind(parameters[3]);
  uint32_t* rn = registerFind(parameters[4]);
  uint32_t* rs = registerFind(parameters[5]);
  uint32_t* rm = registerFind(parameters[6]);
  uint32_t* CPSR = &(ARM11.registers[13]);

  uint32_t rdContents = *rd;
  uint32_t rnContents = *rn;
  uint32_t rsContents = *rs;
  uint32_t rmContents = *rm;
  uint32_t CPSRContents = *CPSR;

  uint32_t condition = parameters[0];
  uint32_t A = parameters[1];
  uint32_t S = parameters[2];

  uint32_t result = 0;


  if(isConditionSatisfied(condition)) {
    if(A != 0) {
      result = extractBit(rnContents*rsContents+rmContents, 0, 31);
    } else {
      result = extractBit(rnContents*rsContents, 0, 31);
    }
    if(S != 0) {

      //CPSRContents =  ;
      if(result == 0) {
        CPSRContents = CPSRContents|(1<<30);
      }
    }
  }

}

void dataTransfer(uint32_t parameters[]) {

}

void branch(uint32_t parameters[]) {

}

void printBits(uint32_t x) {
  int i;
  uint32_t mask = 1 << 31;
  for(i=0; i<32; ++i) {
    if((x & mask) == 0){
      printf("0");
    }
    else {
      printf("1");
    }
    x = x << 1;
  }
  printf("\n");
}

/


int main(void) {
  printBits(genMask(4, 11));
  printBits(0xff0);
  printBits(genMask(15, 15));
  printBits(0x8000);

  return 0;
}




