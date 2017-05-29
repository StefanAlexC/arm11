//
// Created by DAVID BUTEREZ on 28/05/17.
//

#ifndef ARM11_37_EXECUTE_UTILS_H
#define ARM11_37_EXECUTE_UTILS_H

#include <stdint.h>

static const uint32_t N_BIT = 31;
static const uint32_t Z_BIT = 30;
static const uint32_t C_BIT = 29;
static const uint32_t V_BIT = 28;
static const uint32_t CPSR_INDEX = 16;

typedef struct {
    uint32_t result;
    uint32_t carry;
} IntermediateResult;

void setN(uint32_t* cpsr, uint32_t bit);

void setZ(uint32_t* cpsr, uint32_t bit);

void setC(uint32_t* cpsr, uint32_t bit);

void setV(uint32_t* cpsr, uint32_t bit);

#endif //ARM11_37_EXECUTE_UTILS_H
