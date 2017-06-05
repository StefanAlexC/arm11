#ifndef ARM11_37_ARM11_H
#define ARM11_37_ARM11_H

#include <stdint.h>

#define MEMORY_SIZE 65536
#define VALID_MEMORY_SIZE 65533
#define REGISTER_SIZE 17
#define PC registers[15]
#define CPSR registers[16]

typedef struct {
    /**
     * Memory contains 32 bit words.
     * Memory locations are only byte addressable
     * All the instruction addresses are multiples of 4
     */
    uint8_t memory[MEMORY_SIZE];

    /**
    * registers[0] .. registers[12] represent Register 0 - 12
    * registers[13] represents the Program Counter(PC)
    * registers[14] represents the Flags Register(CPSR)
    */
    uint32_t registers[REGISTER_SIZE];
} ARM11;

typedef enum {STOP, NORMAL, BRANCH} FLAG;

#endif //ARM11_37_ARM11_H
