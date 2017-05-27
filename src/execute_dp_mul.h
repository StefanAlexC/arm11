//
// Created by user on 5/25/2017.
//

#ifndef ARM11_37_EXECUTE_H
#define ARM11_37_EXECUTE_H

#include <stdlib.h>
#include <stdbool.h>
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

uint32_t genMask(int start, int end);

/**
 * Extracts all bits between two specified positions
 * @param n : number to extract from
 * @param start : start position
 * @param end : end position
 * @return
 */

uint32_t extractBit(uint32_t n, int start, int end);

/**
 * Checks if condition bits satisfy the contents of CPSR register
 * @param condition : condition bits to check
 * @return : returns boolean if condition was satisfied
 */

bool isConditionSatisfied(uint32_t condition);

/**
 * Executes a specific data processing instruction with given parameters
 * @param parameters : provided parameters
 */

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
