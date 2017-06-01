//
// Created by user on 5/31/2017.
//

#include "assembleMUL.h"


uint32_t getRegisterIndex(char* registerString) {
  char registerIndex = *((++registerString));
  return (uint32_t)(registerIndex - '0') ;
}

char* intToBinaryString(uint32_t number, uint32_t nOfBits) {

  /**
   * Allocate memory for string of binary digits
   */
  char* numberString = malloc(nOfBits* sizeof(char));

  int32_t mask = 1 << (nOfBits-1);

  /**
   * First if-else clause copies most significant bit first
   */
  if((number & mask) == 0){
    strcpy(numberString, "0");
  }
  else {
    strcpy(numberString, "1");
  }
  number = number << 1;

  /**
   * Following iterations concatenate resulting strings of 0 or 1
   */
  int i;
  for(i=1; i<nOfBits; ++i) {
    if((number & mask) == 0){
      strcat(numberString, "0");
    }
    else {
      strcat(numberString, "1");
    }
    number = number << 1;
  }

  return numberString;
}


uint32_t assembleMultiply(int argc, char **parameters) {

  /**
   * Default condition is AL
   */
  char conditionCode[] = "1110";

  /**
   * Fetch index of register
   */
  uint32_t rd = getRegisterIndex(parameters+1*CHARACTER_OFFSET_BETWEEN_REGISTER_DIGITS*(sizeof(char)));
  uint32_t rm = getRegisterIndex(parameters+2*CHARACTER_OFFSET_BETWEEN_REGISTER_DIGITS*(sizeof(char)));
  uint32_t rs = getRegisterIndex(parameters+3*CHARACTER_OFFSET_BETWEEN_REGISTER_DIGITS*(sizeof(char)));

  /**
   * Convert register indices to strings
   */
  char* binaryRd = intToBinaryString(rd, BITS_TO_REPRESENT_REGISTER);
  char* binaryRm = intToBinaryString(rm, BITS_TO_REPRESENT_REGISTER);
  char* binaryRs = intToBinaryString(rs, BITS_TO_REPRESENT_REGISTER);

  /**
   * By default index of register Rn is 0 and bit A is set to 0
   */
  uint32_t rn = 0;
  char* binaryRn = "0000";
  char* A = "0";

  /**
   * Otherwise A is set to 1 and Rn is assigned its corresponding index
   */
  if(argc == 4) {
    A = "1";
    rn = getRegisterIndex(parameters+4*CHARACTER_OFFSET_BETWEEN_REGISTER_DIGITS*(sizeof(char)));
    binaryRn = intToBinaryString(rn, BITS_TO_REPRESENT_REGISTER);
  }

  /**
   * Bit S remains 0
   */
  char* S = "0";

  /**
   * Allocate memory for instruction string
   */
  char* instructionString = malloc(INSTRUCTION_LENGTH*sizeof(char));

  /**
   * Copy, then concatenate remaining bits of instruction to instructionString
   */
  strcpy(instructionString, conditionCode);
  strcat(instructionString, "000000");
  strcat(instructionString, A);
  strcat(instructionString, S);
  strcat(instructionString, binaryRd);
  strcat(instructionString, binaryRn);
  strcat(instructionString, binaryRs);
  strcat(instructionString, "1001");
  strcat(instructionString, binaryRm);

  /**
   * Convert binary string representation to int
   */
  uint32_t instructionCode = (uint32_t)strtol(instructionString, NULL, 2);

  /**
   * Free allocated memory
   */
  free(binaryRd);
  free(binaryRm);
  free(binaryRs);
  if (argc == 4) {
    free(binaryRn);
  }

  return instructionCode;
}
