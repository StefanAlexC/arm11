//
// Created by user on 5/25/2017.
//

#include "../emulate.h"
#include "../../arm11_utils.h"

void multiply(MultiplyInstruction* multiplyInstruction, ARM11* arm11) {

  DecodedInstruction decodedInstruction = (multiplyInstruction->baseInstr);

  /**
   * Find address of each corresponding register from ARM11 structure
   */

  uint32_t rnIndex = (decodedInstruction.Rn);
  uint32_t rsIndex = (multiplyInstruction->Rs);
  uint32_t rmIndex = (multiplyInstruction->Rm);

  /**
   * Extract contents of each register
   */


  uint32_t rnContents = arm11->registers[rnIndex];
  uint32_t rsContents = arm11->registers[rsIndex];
  uint32_t rmContents = arm11->registers[rmIndex];
  uint32_t CPSRContents = arm11->CPSR;

  Cond condition = (decodedInstruction.condition);
  uint32_t A = (multiplyInstruction->accumulate);
  uint32_t S = (multiplyInstruction->set);
  uint32_t result = 0;

  /**
   * Check if condition parameter satisfies condition;
   * Do nothing if condition fails;
   */

  if (isConditionSatisfied(condition, arm11)) {
    //Result depends on state of accumulator parameter
    if (A != 0) {
      result = extractBit(rmContents*rsContents+rnContents, 0, 31);
    } else {
      result = extractBit(rmContents*rsContents, 0, 31);
    }
    if (S != 0) {
      //Set bit N of CPSR to 1 if bit 31 of result is 1
      if (extractBit(result, 31, 31) != 0 ) {
        CPSRContents = CPSRContents|(1<<CPSR_BIT_N_POSITION);
        //Set bit Z of CPSR is result is zero
      } else if (result == 0) {
        CPSRContents = CPSRContents|(1<<(CPSR_BIT_Z_POSITION));
        //Set bit N of CPSR to 0 if bit 31 of result is 0
      } else {
        CPSRContents = CPSRContents&(~(1<<CPSR_BIT_N_POSITION));
      }
    }

    /**
     * Store result in registers field of ARM11 structure with index rd
     * Update contents of CPSR register
     */

    arm11->registers[decodedInstruction.Rd] = result;
    arm11->CPSR = CPSRContents;
  }


}

/**
int main(void) {
  printBits(genMask(4, 11));
  printBits(0xff0);
  printBits(genMask(15, 15));
  printBits(0x8000);

  return 0;
}
*/
