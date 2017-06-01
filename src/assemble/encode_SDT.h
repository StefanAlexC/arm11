#ifndef ARM11_37_ASSEMBLE_SDT_H
#define ARM11_37_ASSEMBLE_SDT_H

#include <stdbool.h>
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>


#define AL_COND 14
#define BITS_27_26 1
#define MOV_BITS_27_26 0
#define BITS_22_21 0
#define FLAG_SIZE 1
#define PATTERN_SIZE 2
#define MOV_I 1
#define OPCODE_SIZE 4
#define MOV_CODE 13
#define MOV_S 0
#define REG_SIZE 4
#define OFFSET_SIZE 12
#define MAX_MOV_OPERAND 4096
#define SHIFT_TYPE 2
#define PIPELINE_OFFSET 8
#define WORD_SIZE 4
#define SEPS "[#r=-]"
#define PC 15
#define LSL 0
#define LSR 1
#define ASR 2
#define ROR 3

typedef struct {
    uint32_t instruction;
    bool hasExpr;
    uint32_t expression;
} SDTinstr;

/**
 * Gets the instruction code for when a ldr must be interpreted as a mov
 * @param The destination register
 * @param The value to be stored
 * @return The intruction bit code
 */
uint32_t getMovCode(uint32_t rd, uint32_t value);

/**
 * Gets the instruction code for an SDT instruction
 * @param Indicates if the offset is an immediate
 * @param Indicates if pre or post indexing will be used
 * @param Indicates if the offsed is added or subtracted
 * @param Indicates if instruction is ldr or str
 * @param The base register
 * @param The source/destination register
 * @param The offset
 * @return The constructed instruction bit-code
 */
uint32_t constructCode(uint32_t i, uint32_t p, uint32_t u, uint32_t l, uint32_t rn, uint32_t rd, uint32_t offset);

/**
 * Gets an integer from a string
 * @param The string
 * @return The integer
 */
uint32_t intFromString (char value[]);

/**
 * Gets an integer from its hexadecimal representation in a string
 * @param The string
 * @return The integer
 */
uint32_t intFromStringHex (char value[]);

/**
 * Gets the last element of a string
 * @param The string
 * @return The last element
 */
char lastElement (char value[]);

/**
 * Gets the first element of a string
 * @param The string
 * @return The first element
 */
char firstElement (char value[]);

/**
 * Gets the integer corresponding to a shift type
 * @param The string representation of the shift type
 * @return The integer
 */
uint32_t getShift (char shiftType[]);

/**
 * Check if the contents of the register must be added or subtracted and sets the UP flag accordingly
 * @param The UP flag
 * @param The string representing the register
 */
void setUpBit (uint32_t* up, char reg[]);

/**
 * Calculates the offset with a shifted register
 * @param The string representing the register
 * @param The type of shift to be applied
 * @param The shift amount
 * @param The UP flag which will be set accordingly
 * @return
 */
uint32_t getOffsetForShiftedRegister (char reg[], char shiftType[], char shiftAmount[], uint32_t* up);

/**
 * Calculates the offset with a simple register
 * @param The string representation of the register
 * @param The UP flag which will be set accordingly
 * @return
 */
uint32_t getOffsetForRegister(char *reg, uint32_t *up);

/**
 *
 * @param The number of parameters in argv
 * @param Pointer to a string containing the tokeniezed intruction
 * @param The memory address after the HALT instruction
 * @param The memory address of this instruction
 * @return A SDTinstr struct containing the assembled instruction,
 * a bool indicating if an immediate must be placed at the end of
 * the program and an immediate expression.
 */
SDTinstr encodeSDT(int argc, char **argv, int *endAddress, int thisAddress);

#endif //ARM11_37_ASSEMBLE_SDT_H
