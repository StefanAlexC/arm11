//
// Created by DAVID BUTEREZ on 25/05/17.
//

#include <stdint.h>

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
static const uint32_t OPERAND2_MASK = 0xFFF;
static const uint32_t SDT_OFFSET_MASK = 0xFFF;
static const uint32_t SET_CODE_MASK = 0x100000;
static const uint32_t ACCUMULATE_MASK = 0x200000;
static const uint32_t RS_MASK = 0xF00;
static const uint32_t RM_MASK = 0xF;
static const uint32_t LOAD_MASK = 0x100000;
static const uint32_t PRE_POST_MASK = 0x1000000;
static const uint32_t UP_MASK = 0x800000;
static const uint32_t BRANCH_OFFSET_MASK = 0xFFFFFF;
static const uint32_t MSB_LITTLE_ENDIAN_MASK = 0x80000000;
static const uint32_t LAST_8_BITS_MASK = 0xFF;
static const uint32_t BITS_11_8_MASK = 0xF00;
static const uint32_t BITS_11_4_MASK = 0xFF0;
static const uint32_t BITS_27_26_MASK = 0xC000000;
static const uint32_t BITS_24_22_MASK = 0x1C00000;
static const uint32_t BITS_11_7_MASK = 0xF80;
static const uint32_t BITS_7_6_MASK = 0x60;

#endif //ARM11_37_MASKS_H
