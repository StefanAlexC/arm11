//
// Created by DAVID BUTEREZ on 25/05/17.
//

#include <stdint.h>
#include "utils.h"

#ifndef ARM11_37_MASKS_H
#define ARM11_37_MASKS_H


static const uint32_t INSTR_BITS = 32;
static const uint32_t COND_MASK = 0xF0000000;
static const uint32_t IMMEDIATE_OP_MASK = 0x2000000;
static const uint32_t OPCODE_MASK = 0x1E00000;
static const uint32_t RN_MASK = 0xF0000;
static const uint32_t RD_MULTIPLY = 0xF0000;
static const uint32_t RD_MASK = 0xF000;
static const uint32_t RN_MULTIPLY = 0xF000;
static const uint32_t OPERAND2_MASK = 0xFFFF;
static const uint32_t SDT_OFFSET_MASK = 0xFFFF;
static const uint32_t SET_CODE_MASK = 0x100000;
static const uint32_t ACCUMULATE_MASK = 0x200000;
static const uint32_t RS_MASK = 0xF00;
static const uint32_t RM_MASK = 0xF;
static const uint32_t LOAD_MASK = 0x100000;
static const uint32_t PRE_POST_MASK = 0x1000000;
static const uint32_t UP_MASK = 0x800000;
static const uint32_t BRANCH_OFFSET_MASK = 0xFFFFFF;

// bits 27-26
static const uint32_t CHECK_BITS = 0xC000000;

// bits 24-22
static const uint32_t DATA_PROCESSING_HELPER_MASK = 0x1C00000;

#endif //ARM11_37_MASKS_H
