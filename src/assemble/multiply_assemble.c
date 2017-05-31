//
// Created by user on 5/31/2017.
//

#include "multiply_assemble.h"

uint32_t getRegisterIndex(char* registerString) {
  return (uint32_t)(*(registerString++));
  //comment
}

char* intToBinaryString(uint32_t number) {
  uint32_t numLength = snprintf(NULL, 0, "%i", number);
  char* numberString = malloc(numLength+1);
  int i;
  uint32_t mask = 1 << 31;
  for(i=0; i<32; ++i) {
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
  uint32_t rd = getRegisterIndex(parameters);
  uint32_t rm = getRegisterIndex(parameters+3*(sizeof(char)));
  uint32_t rs = getRegisterIndex(parameters+6*(sizeof(char)));

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
    rn = getRegisterIndex(parameters+9*(sizeof(char)));
    binaryRn = intToBinaryString(rn);
  }

  char instruction[32];
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
  free(binaryRn);
  free(binaryRs);

  return instruction;

}
