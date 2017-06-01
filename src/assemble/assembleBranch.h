#ifndef ARM11_37_ASSEMBLEBRANCH_H
#define ARM11_37_ASSEMBLEBRANCH_H

#include <stdint.h>
#include "../arm11_utils.h"

#define BEQ "beq"
#define BNE "bne"
#define BGE "bge"
#define BLT "blt"
#define BGT "bgt"
#define BLE "ble"
#define BAL "b"
#define BEQ_BYTES 0
#define BNE_BYTES 1
#define BGE_BYTES 10
#define BLT_BYTES 11
#define BGT_BYTES 12
#define BLE_BYTES 13
#define BAL_BYTES 14
#define CONDITION_OFFSET 4
#define OFFSET_OFFSET 24
#define BRANCH_OPCODE 10
#define MEMORY_MULTIPLIER 4
#define PIPELINE_OFFSET 8
#define PADDING 4278190080
#define SIGN_BIT 8388608

uint32_t encodeBranch(char**argv, Map* labels, int32_t currentOperationNumber);

#endif //ARM11_37_ASSEMBLEBRANCH_H
