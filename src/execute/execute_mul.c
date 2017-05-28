//
// Created by user on 5/25/2017.
//

#include "../emulate.h"
#include <stdlib.h>
#include <stdio.h>
#include "execute.h"
#include "execute_mul.h"
#include "../decode/decode_utils.h"


uint32_t registerFind(uint32_t r) {
  struct ARM11 arm11;
  uint32_t Register = arm11.registers[r];
  uint32_t *registerAddress = &Register;
}

void multiply(MultiplyInstruction* multiplyInstruction) {

  struct ARM11 arm11;
  DecodedInstruction *decodedInstruction =  multiplyInstruction->baseInstr;

  /**
   * Find address of each corresponding register from ARM11 structure
   */

  uint32_t* rn = registerFind(*(decodedInstruction->Rn));
  uint32_t* rs = registerFind(*(multiplyInstruction->Rs));
  uint32_t* rm = registerFind(*(multiplyInstruction->Rm));

  /**
   * Extract contents of each register
   */


  uint32_t rnContents = *rn;
  uint32_t rsContents = *rs;
  uint32_t rmContents = *rm;
  uint32_t CPSRContents = &(arm11.registers[14]);

  uint32_t condition = *(decodedInstruction->condition);
  uint32_t A = *(multiplyInstruction->accumulate);
  uint32_t S = *(multiplyInstruction->set);

  uint32_t result = 0;

  /**
   * Check if condition parameter satisfies condition;
   * Do nothing if condition fails;
   */

  if(isConditionSatisfied(condition)) {
    //Result depends on state of accumulator parameter
    if(A != 0) {
      result = extractBit(rnContents*rsContents+rmContents, 0, 31);
    } else {
      result = extractBit(rnContents*rsContents, 0, 31);
    }
    if(S != 0) {
      //Set bit N of CPSR to 1 if bit 31 of result is 1
      if(extractBit(result, 31, 31) != 0 ) {
        CPSRContents = CPSRContents|(1<<31);
      //Set bit Z of CPSR is result is zero
      } else if(result == 0) {
        CPSRContents = CPSRContents|(1<<30);
      //Set bit N of CPSR to 0 if bit 31 of result is 0
      } else {
        CPSRContents = CPSRContents|(~(1<<31));
      }
    }

    /**
     * Store result in registers field of ARM11 structure with index rd
     * Update contents of CPSR register
     */

    arm11.registers[*(decodedInstruction->Rd)] = result;
    arm11->registers[14] = CPSRContents;
  }


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

int main(void) {
  printBits(genMask(4, 11));
  printBits(0xff0);
  printBits(genMask(15, 15));
  printBits(0x8000);

  return 0;
}




