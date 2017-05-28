//
// Created by user on 5/25/2017.
//

#ifndef ARM11_37_EXECUTE_H
#define ARM11_37_EXECUTE_H

#include <stdlib.h>
#include <stdbool.h>
#include "../emulate.c"

#endif //ARM11_37_EXECUTE_H

#define INSTRUCTION_SIZE = 31;
#define POSITION_I = 25;




typedef enum {DP, MUL, DT, BRANCH} instruction ;
typedef enum {EQ, LE, GE, NE, LT, GT, AL} condition;
typedef enum opcode {AND, EOR, SUB, RSB, ADD, TST, TEQ, CMP, ORR, MOV};



void dataProcess(uint32_t parameters[]);

/**
 * Executes a multiplication instruction with given parameters
 * @param parameters : provided parameters
 */

void multiply(uint32_t parameters[]);

/**
 * Executes a data transfer instruction with given parameters
 * @param parameters : provided parameters
 */

void dataTransfer(uint32_t parameters[]);

/**
 * Executes a branching instruction with given parameters
 * @param parameters : provided parameters
 */

void branch(uint32_t parameters[]);

/**
 * Prints the binary representation of a number
 * Used for testing purposes
 * @param x : number to be printed
 */

void printBits(uint32_t x);
