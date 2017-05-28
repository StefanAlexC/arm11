//
// Created by DAVID BUTEREZ on 28/05/17.
//

#ifndef ARM11_37_EXECUTE_DP_H
#define ARM11_37_EXECUTE_DP_H

#include "../ARM11.h"
#include "execute_utils.h"

/**
 *
 * @param registerIndex
 * @return Register index (CPSR will be 14)
 */
uint32_t offsetRegister(uint32_t registerIndex);

uint32_t and(uint32_t rnValue, uint32_t op2);

uint32_t eor(uint32_t rnValue, uint32_t op2);

uint32_t sub(uint32_t rnValue, uint32_t op2);

uint32_t rsb(uint32_t rnValue, uint32_t op2);

uint32_t add(uint32_t rnValue, uint32_t op2);

uint32_t tst(uint32_t rnValue, uint32_t op2);

uint32_t teq(uint32_t rnValue, uint32_t op2);

uint32_t cmp(uint32_t rnValue, uint32_t op2);

uint32_t orr(uint32_t rnValue, uint32_t op2);

uint32_t mov(uint32_t rnValue, uint32_t op2);

/**
 *
 * @param number1
 * @param number2
 * @return true if addition will overflow
 */
bool addOverflows(uint32_t number1, uint32_t number2);

/**
 *
 * @param number1
 * @param number2
 * @return true if subtraction (number1 - number2) overflows
 */
bool subOverflows(uint32_t number1, uint32_t number2);

/**
 *
 * @param number1
 * @param number2
 * @return true if subtraction (number2 - number1) overflows
 */
bool rsbOverflows(uint32_t number1, uint32_t number2);

/**
 *
 * @param arm
 * @param destinationIndex
 * @param newValue
 * Write the destination register
 */
void writeDestinationRegister(ARM11* arm, uint32_t destinationIndex, uint32_t newValue);

/**
 *
 * @param mnemonic
 * @return true if the given function opcode will write to Rd
 */
bool writesResult(Opcode mnemonic);

/**
 *
 * @param opcode
 * @return true if function is arithmetic
 */
bool isArithmeticFunction(Opcode opcode);

/**
 *
 * @param opcode
 * @return true if function is logical
 */
bool isLogicalFunction(Opcode opcode);

/**
 *
 * @param arm
 * @param dpi
 * @return the actual value of the second operand, along with the carry from the barrel shifter
 */
IntermediateResult computeSecondOperand(ARM11* arm, DataProcessingInstruction *dpi);

/**
 *
 * @param arm
 * @param dpi
 * @param barrelResult
 * @return the result of applying the instruction, along with the corresponding carry
 */
IntermediateResult applyFunction(ARM11* arm, DataProcessingInstruction *dpi, IntermediateResult barrelResult);

/**
 *
 * @param finalResult
 * @param arm
 * Sets the CPSR register accordingly
 */
void setCPSR(IntermediateResult finalResult, ARM11* arm);

/**
 *
 * @param dpi
 * @param arm
 * Executes the instruction
 */
void dataProcessing(DataProcessingInstruction *dpi, ARM11 *arm);

#endif //ARM11_37_EXECUTE_DP_H
