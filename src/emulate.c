#include <stdlib.h>

struct ARM11 {
    /**
     * Memory contains 32 bit words.
     * Memory locations are only byte addressable
     * All the instruction addresses are multiples of 4
     */
    //TODO: need to add macro for 65536, once we learn what a macro is
    uint8_t memory[65536];

    /**
    * registers[0] .. registers[12] represent Register 0 - 12
    * registers[13] represents the Program Counter(PC)
    * registers[14] represents the Flags Register(CPSR)
    */
    uint32_t registers[15];
};

int main(int argc, char **argv) {
  return EXIT_SUCCESS;
}
