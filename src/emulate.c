#include "emulate.h"
#include "decode/decode_utils.h"
#include "ARM11.h"

void initialize(ARM11 *arm11) {
    int i;
    for (i = 0; i < MEMORY_SIZE; i++) {
        arm11->memory[i] = DEFAULT_VALUE;
    }
    for (i = 0; i < REGISTER_SIZE; i++) {
        arm11->registers[i] = DEFAULT_VALUE;
    }
}

uint32_t littleToBig(int address, ARM11 *arm11) {
    uint32_t value = 0;
    int j;
    if(address > 65533) {
        printf("Error: Out of bounds memory access at address 0x%08x\n", address);
        return 0;
    }
    for (j = BYTE_NUMBER - 1 ; j >= 0; j--) {
        value <<= BYTE_VALUE;
        value += arm11->memory[address + j];
    }
    return value;
}

uint32_t getMemoryValue(int i, ARM11 *arm11) {
    uint32_t value = 0;
    int j;
    for (j = 0; j < BYTE_NUMBER; j++) {
        value <<= BYTE_VALUE;
        value += arm11->memory[i + j];
    }
    return value;
}

void print(ARM11 *arm11) {
    int i;
    printf("%s\n", "Registers:");
    for (i = 0; i < GP_REGISTERS; i++) {
        printf("$%-2i : %10i (0x%08x) \n", i, arm11->registers[i], arm11->registers[i]);
    }
    printf("PC  : %10i (0x%08x) \n", arm11->PC, arm11->PC);
    printf("CSPR: %10i (0x%08x) \n", arm11->CPSR, arm11->CPSR);

    printf("%s\n", "Non-zero memory:");
    for (i = 0; i < MEMORY_SIZE; i += 4) {
        uint32_t value = getMemoryValue(i, arm11);
        if (value != 0) {
            printf("0x%08x: 0x%08x \n", i, value);
        }
    }
}

uint32_t fetch(ARM11 *arm11) {
    //TODO: Might need to add error if not multiple of 4
    uint32_t fetchedData = littleToBig(arm11->PC, arm11);
    arm11->PC += 4;
    return fetchedData;
}

void printByte_inBinary(uint8_t byte) {
    uint8_t mask;

    for (int i = BYTE_VALUE - 1 ; i >= 0; i--) {
        mask = (uint8_t) (1 << i);
        if ((mask & byte) > 0)
            printf("1");
        else
            printf("0");
    }
    printf("\n");
}

void readFile(char *fileName, ARM11 *arm11) {
    FILE *file = fopen(fileName, "r");
    char byte;
    int memoryLocation = 0;

    if (!feof(file)) {
        byte = (char) fgetc(file);
        while (!feof(file)) {
            //printByte_inBinary((uint8_t) byte);
            arm11->memory[memoryLocation++] = (uint8_t) byte;
            byte = (char) fgetc(file);
        }
    }

    fclose(file);
}

//TODO: check if it goes out of memory
void fillPipeline(void **decoded, uint32_t *fetched, ARM11 *arm11) {

    *fetched = fetch(arm11);
    *decoded = decode(*fetched);
    *fetched = fetch(arm11);
}

int main(int argc, char **argv) {
    ARM11 arm11;
    initialize(&arm11);
    readFile(FILE_NAME, &arm11);

    uint32_t fetched;
    void* decoded;
    FLAG flagExecute;

    /**
     * This simulates the execution loop and pipeline of the ARM11
     */
    fillPipeline(&decoded, &fetched, &arm11);
    do {
        flagExecute = execute(decoded, &arm11);
        if (flagExecute == BRANCH) {
            fillPipeline(&decoded, &fetched, &arm11);
        } else if (flagExecute == NORMAL) {
            decoded = decode(fetched);
            fetched = fetch(&arm11);
        }
    } while (flagExecute != STOP);

    print(&arm11);

    return EXIT_SUCCESS;

}

