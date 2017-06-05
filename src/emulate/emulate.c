#include "emulate.h"

void initialize(ARM11 *arm11) {

    for (int i = 0; i < MEMORY_SIZE; i++) {
        arm11->memory[i] = DEFAULT_VALUE;
    }

    for (int i = 0; i < REGISTER_SIZE; i++) {
        arm11->registers[i] = DEFAULT_VALUE;
    }

}

bool pinAccess(int address) {

    return (address == ACC_PINS_0_9 || address == ACC_PINS_10_19 || address == ACC_PINS_20_29
           || address == CLEAR_PINS || address == SET_PINS);

}

bool isPinAddress(int address) {

    if(address == ACC_PINS_0_9) {
        printf("One GPIO pin from 0 to 9 has been accessed\n");
        return true;
    }
    if(address == ACC_PINS_10_19) {
        printf("One GPIO pin from 10 to 19 has been accessed\n");
        return true;
    }
    if(address == ACC_PINS_20_29) {
        printf("One GPIO pin from 20 to 29 has been accessed\n");
        return true;
    }
    if(address == CLEAR_PINS) {
        printf("PIN OFF\n");
        return true;
    }
    if(address == SET_PINS) {
        printf("PIN ON\n");
        return true;
    }

    return false;
}

bool validMemoryAccess(int address) {

    if(address > VALID_MEMORY_SIZE && !pinAccess(address)) {
        printf("Error: Out of bounds memory access at address 0x%08x\n", address);
        return false;
    }

    return true;
}

uint32_t littleToBig(int address, ARM11 *arm11) {
    uint32_t value = 0;

    if(validMemoryAccess(address)) {
        if(isPinAddress(address)) {
            return (uint32_t)address;
        }

        for (int j = BYTE_NUMBER - 1; j >= 0; j--) {
            value <<= BYTE_VALUE;
            value += arm11->memory[address + j];
        }

        return value;
    }

    return DEFAULT_VALUE;
}

uint32_t getMemoryValue(int address, ARM11 *arm11) {
    uint32_t value = 0;

    if(validMemoryAccess(address)) {
        if(isPinAddress(address)) {
            return (uint32_t)address;
        }

        for (int j = 0; j < BYTE_NUMBER; j++) {
            value <<= BYTE_VALUE;
            value += arm11->memory[address + j];
        }

        return value;
    }

    return DEFAULT_VALUE;
}

void print(ARM11 *arm11) {
    uint32_t value;

    printf("%s\n", "Registers:");
    for (int i = 0; i <= GP_REGISTERS; i++) {
        printf("$%-2i : %10i (0x%08x)\n", i, arm11->registers[i], arm11->registers[i]);
    }
    printf("PC  : %10i (0x%08x)\n", arm11->PC, arm11->PC);
    printf("CPSR: %10i (0x%08x)\n", arm11->CPSR, arm11->CPSR);

    printf("%s\n", "Non-zero memory:");
    for (int i = 0; i < MEMORY_SIZE; i += 4) {
        value = getMemoryValue(i, arm11);
        if (value != DEFAULT_VALUE) {
            printf("0x%08x: 0x%08x\n", i, value);
        }
    }

}

uint32_t fetch(ARM11 *arm11) {

    uint32_t fetchedData = littleToBig(arm11->PC, arm11);
    arm11->PC += 4;

    return fetchedData;
}

void readFile(char *fileName, ARM11 *arm11) {
    FILE *file = fopen(fileName, "r");
    char byte;
    int memoryLocation = 0;

    if (!feof(file)) {
        byte = (char) fgetc(file);
        while (!feof(file)) {
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
    uint32_t fetched;
    void* decoded;
    FLAG flagExecute;

    /**
     * Creates and initializes the ARM11 processor structure.
     */
    ARM11 arm11;
    initialize(&arm11);

    /**
     * Reads the input file.
     */
    readFile(FILE_NAME, &arm11);

    /**
     * Simulates the execution loop and pipeline of the ARM11
     */
    fillPipeline(&decoded, &fetched, &arm11);
    do {
        flagExecute = execute(decoded, &arm11);
        /**
         * Checks if the instruction is Branch Instruction.
         */
        if (flagExecute == BRANCH) {
            /**
             * Refills the pipeline, after modifying the program counter to its new value.
             */
            fillPipeline(&decoded, &fetched, &arm11);
        } else if (flagExecute == NORMAL) {
            decoded = decode(fetched);
            fetched = fetch(&arm11);
        }

    } while (flagExecute != STOP);

    /**
     * Prints the final state of the ARM11 processor.
     */
    print(&arm11);

    return EXIT_SUCCESS;

}

