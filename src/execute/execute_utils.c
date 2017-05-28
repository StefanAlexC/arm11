//
// Created by DAVID BUTEREZ on 28/05/17.
//

#include <assert.h>
#include "execute_utils.h"
#include "../decode/decode_utils.h"

void setN(uint32_t* cpsr, uint32_t bit) {
    assert(bit == 0 || bit == 1);
    changeBit(cpsr, N_BIT, bit);
}

void setZ(uint32_t* cpsr, uint32_t bit) {
    assert(bit == 0 || bit == 1);
    changeBit(cpsr, Z_BIT, bit);
}

void setC(uint32_t* cpsr, uint32_t bit) {
    assert(bit == 0 || bit == 1);
    changeBit(cpsr, C_BIT, bit);
}

void setV(uint32_t* cpsr, uint32_t bit) {
    assert(bit == 0 || bit == 1);
    changeBit(cpsr, V_BIT, bit);
}
