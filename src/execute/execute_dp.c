//
// Created by DAVID BUTEREZ on 28/05/17.
//

#include "../emulate.h"
#include "execute_dp.h"

uint32_t offsetRegister(uint32_t registerIndex) {
    if (registerIndex == 16) {
        return 14;
    }

    return registerIndex;
}

uint32_t and(uint32_t rnValue, uint32_t op2) {
    return rnValue & op2;
}

uint32_t eor(uint32_t rnValue, uint32_t op2) {
    return rnValue ^ op2;
}

uint32_t sub(uint32_t rnValue, uint32_t op2) {
    return rnValue - op2;
}

uint32_t rsb(uint32_t rnValue, uint32_t op2) {
    return op2 - rnValue;
}

uint32_t add(uint32_t rnValue, uint32_t op2) {
    return rnValue + op2;
}

uint32_t tst(uint32_t rnValue, uint32_t op2) {
    return and(rnValue, op2);
}

uint32_t teq(uint32_t rnValue, uint32_t op2) {
    return eor(rnValue, op2);
}

uint32_t cmp(uint32_t rnValue, uint32_t op2) {
    return sub(rnValue, op2);
}

uint32_t orr(uint32_t rnValue, uint32_t op2) {
    return rnValue | op2;
}

uint32_t mov(uint32_t rnValue, uint32_t op2) {
    return op2;
}

bool addOverflows(uint32_t number1, uint32_t number2) {
    return number1 + number2 < number1;
}

bool subOverflows(uint32_t number1, uint32_t number2) {
    return (int)(number1 - number2) >= 0;
}

bool rsbOverflows(uint32_t number1, uint32_t number2) {
    return (int)(number2 - number1) >= 0;
}

void writeDestinationRegister(ARM11* arm, uint32_t destinationIndex, uint32_t newValue) {
    arm->registers[offsetRegister(destinationIndex)] = newValue;
}

bool writesResult(Opcode opcode) {
    return !(opcode == TST || opcode == TEQ || opcode == CMP);
}

bool isArithmeticFunction(Opcode opcode) {
    return opcode == ADD || opcode == SUB || opcode == RSB || opcode == CMP;
}

bool isLogicalFunction(Opcode opcode) {
    return !isArithmeticFunction(opcode);
}

IntermediateResult computeSecondOperand(ARM11* arm, DataProcessingInstruction *dpi) {
    typedef uint32_t (*BarrelFunctionPtr) (uint32_t*, uint32_t);
    BarrelFunctionPtr functionPointers[] = {shiftLeft, shiftRight, arithmeticShiftRight, rotateRight};

    IntermediateResult barrelResult;

    if (dpi->immediate) {
        barrelResult.result = dpi->operand2.immediateValue;
        barrelResult.carry = rotateRight(&barrelResult.result, dpi->operand2.shiftAmount);
    } else {
        barrelResult.result = arm->registers[offsetRegister(dpi->operand2.Rm)];
        if (!dpi->operand2.bit4) {
            barrelResult.carry = (*functionPointers[dpi->operand2.shiftType]) (&barrelResult.result, dpi->operand2.shiftAmount);
        } else {
            uint32_t rs = arm->registers[offsetRegister(dpi->operand2.Rs)];
            barrelResult.carry = (*functionPointers[dpi->operand2.shiftType]) (&barrelResult.result, rs);
        }
    }

    return barrelResult;
}

IntermediateResult applyFunction(ARM11* arm, DataProcessingInstruction *dpi, IntermediateResult barrelResult) {
    typedef uint32_t (*FunctionPtr)(uint32_t, uint32_t);
    FunctionPtr functionPointers[] = {and, eor, sub, rsb, add, NULL, NULL, NULL, tst, teq, cmp, NULL, orr, mov};

    typedef bool (*OverflowFunctionPtr)(uint32_t, uint32_t);
    OverflowFunctionPtr  overflowFunctionPointers[] = {NULL, NULL, subOverflows, rsbOverflows, addOverflows, NULL, NULL, NULL, NULL, NULL, subOverflows, NULL, NULL, NULL};

    IntermediateResult finalResult;
    uint32_t rn = arm->registers[offsetRegister(dpi->baseInstr.Rn)];

    if (isLogicalFunction(dpi->opcode)) {
        finalResult.carry = barrelResult.carry;
    } else {
        finalResult.carry = (uint32_t) ((*overflowFunctionPointers[dpi->opcode]) (rn, barrelResult.result));
    }

    finalResult.result = (*functionPointers[dpi->opcode]) (rn, barrelResult.result);

    return finalResult;
}

void setCPSR(IntermediateResult finalResult, ARM11* arm) {
    uint32_t* cpsrPtr = &(arm->registers[CPSR_INDEX]);
    setC(cpsrPtr, finalResult.carry);
    setZ(cpsrPtr, (uint32_t) !finalResult.result);
    setN(cpsrPtr, getBit(finalResult.result, N_BIT));
}

void dataProcessing(DataProcessingInstruction *dpi, ARM11 *arm) {
    IntermediateResult secondOperand = computeSecondOperand(arm, dpi);
    IntermediateResult finalResult = applyFunction(arm, dpi, secondOperand);

    if (writesResult(dpi->opcode)) {
        writeDestinationRegister(arm, dpi->baseInstr.Rd, finalResult.result);
    }

    if (dpi->set) {
        setCPSR(finalResult, arm);
    }

    free(dpi);
}
