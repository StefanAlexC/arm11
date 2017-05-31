//
// Created by user on 5/31/2017.
//

#include "multiply_assemble.h"

uint32_t getRegisterIndex(char* registerString) {
  char registerIndex = *((++registerString));
  return (uint32_t)(registerIndex - '0') ;
}

char* intToBinaryString(uint32_t number) {
  char* numberString = malloc(4* sizeof(char));
  int i;
  uint32_t mask = 1 << 3;
  if((number & mask) == 0){
    strcpy(numberString, "0");
  }
  else {
    strcpy(numberString, "1");
  }
  number = number << 1;

  for(i=1; i<4; ++i) {
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


char* assembleMultiply(uint32_t args, char* parameters) {

  char conditionCode[] = "1110";
  uint32_t rd = getRegisterIndex(parameters+4*(sizeof(char)));
  uint32_t rm = getRegisterIndex(parameters+8*(sizeof(char)));
  uint32_t rs = getRegisterIndex(parameters+12*(sizeof(char)));


  char* binaryRd = intToBinaryString(rd);
  char* binaryRm = intToBinaryString(rm);
  char* binaryRs = intToBinaryString(rs);

  uint32_t rn = 0;
  char* binaryRn = "0000";

  char S[] = "0";
  char* A;
  if(args == 3) {
    A = "0";
  } else {
    A = "1";
    rn = getRegisterIndex(parameters+16*(sizeof(char)));
    binaryRn = intToBinaryString(rn);
  }

  char* instruction = malloc(32* sizeof(char));
  strcpy(instruction, conditionCode);
  strcat(instruction, "000000");
  strcat(instruction, A);
  strcat(instruction, S);
  strcat(instruction, binaryRd);
  strcat(instruction, binaryRn);
  strcat(instruction, binaryRs);
  strcat(instruction, "1001");
  strcat(instruction, binaryRm);

  free(binaryRd);
  free(binaryRm);
  free(binaryRs);

  if (args == 4) {
    free(binaryRn);
  }

  return instruction;

}
