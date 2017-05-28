#ifndef ARM11_37_EMULATE_H
#define ARM11_37_EMULATE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "execute/execute.h"
#include "decode/decode.h"
#include "ARM11.h"

#define MEMORY_SIZE 65536
#define REGISTER_SIZE 15
#define GP_REGISTERS 12
#define DEFAULT_VALUE 0
#define BYTE_VALUE 8
#define BYTE_NUMBER 4
#define PC registers[13]
#define CSPR registers[14]
#define FILE_NAME argv[1]


/**
 * !!Tested!!
 * Initializes the memory and the registers of the given arm11 to 0
 * @param arm11
 */
void initialize(ARM11 *arm11);

/**
 * !!Tested!!
 * Takes a memory address and converts the next 4 bytes following the address from Little Endian to Big Endian
 * and returns the resulting 32-bit int
 * @param i The memory address
 * @param arm11
 * @return The Big Endian number
 */
uint32_t littleToBig(int i, ARM11 *arm11);


/**
 * !!Tested!!
 * Takes a memory address and returns the value of the next 4 bytes following the address, representing an instruction
 * @param i The memory address
 * @param arm11
 * @return value of 32 bit instruction
 */
uint32_t getMemoryValue(int i, ARM11 *arm11);

/**
 * !!Tested!!
 * Prints the registers and the non-zero memory locations of the given arm11
 * @param arm11
 */
void print(ARM11 *arm11);

/**
 * !!Tested!!
 * Fetches the next instruction from memory
 * @param arm11
 * @return The fetched 32 bit instruction in Big Endian format
 */
uint32_t fetch(ARM11 *arm11);

/**
 * !!Tested!!
 * Prints the binary value of a byte
 * @param The byte we wish to print
 */
void printByte_inBinary(uint8_t byte);

/**
 * !!Tested!!
 * Reads that contents of a file and transfers them to memory
 * @param fileName The path of the file we wish to read
 */
void readFile(char *fileName, ARM11 *arm11);

//TODO: Add description
void fillPipeline(void **decoded, uint32_t *fetched, ARM11 *arm11);

#endif //ARM11_37_EMULATE_H
