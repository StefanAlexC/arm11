#ifndef ARM11_37_ARM11_UTILS_H
#define ARM11_37_ARM11_UTILS_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define END_OF_MAP -1
#define CHAR_TYPE 0
#define MAP_TYPE 1
#define MAX_COMMAND_SIZE 50
#define MAX_NUMBER_COMMANDS 50
#define MAX_ARGUMENT_NUMBER 15
#define MAX_ARGUMENT_SIZE 15

#define FIRST_BYTE_END 31
#define SECOND_BYTE_END 23
#define THIRD_BYTE_END 15
#define FOURTH_BYTE_END 7

typedef struct {
    char* key;
    int value;
} Map;

typedef struct {
    uint32_t instruction;
    bool hasExpr;
    uint32_t expression;
} SDTinstr;

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
 *
 * @param bits
 * Prints the bits of a 32-bit integer
 * Most significant bit to the left
 */
void printBits(uint32_t bits);

/**
 * Safely allocates a String of specified size.
 * @param size The length of the String.
 * @param Defines the return type, if mode is True then the returned array is int32_t otherwise it is a char array.
 * @return A pointer to the created String.
 */
void* allocateArray(int size, bool mode);

/**
 * Safely allocate a String Matrix .
 * @param lines The number of line of the Matrix.
 * @param columns The length of each line of the Matrix.
 * @return A pointer to the created String Matrix.
 */
char **allocateStringMatrix(int lines, int columns);

/**
 * Counts the number of arguments in a String Array.
 * @param array The String Array, whose arguments we need to count
 * @return The number of arguments.
 */
int numberArgumentsStringArray(char** array);

/**
 * Countrs the number of arguments in a Int32_t Array
 * @param array The Int32_t Array, whose arguments we need to count
 * @return The number of arguments
 */
int numberArgumentsInt32Array(int **array);

/**
 * Prints the 32 bit number as four chars
 * @param number The number we wish to print
 */
void printAsChar(uint32_t number);

#endif //ARM11_37_ARM11_UTILS_H
