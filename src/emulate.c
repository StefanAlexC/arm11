#include "emulate.h"

void initialize(struct ARM11 *arm11) {
    int i;
    for (i = 0; i < MEMORY_SIZE; i++) {
        arm11->memory[i] = DEFAULT_VALUE;
    }
    for (i = 0; i < REGISTER_SIZE; i++) {
        arm11->registers[i] = DEFAULT_VALUE;
    }
}

uint32_t littleToBig(int i, struct ARM11 *arm11) {
    uint32_t value = 0;
    int j;
    for (j = 3; j >= 0; j--) {
        value <<= 8;
        value += arm11->memory[i + j];
    }
    return value;
}

uint32_t getMemoryValue(int i, struct ARM11 *arm11) {
    uint32_t value = 0;
    int j;
    for (j = 0; j < 4; j++) {
        value <<= 8;
        value += arm11->memory[i + j];
    }
    return value;
}

void print(struct ARM11 *arm11) {
    //TODO: replace 65536 and 15 with macros
    int i;
    printf("%s\n", "Registers:");
    for (i = 0; i < 12; i++) {
        printf("$%-2i :%8i (0x%08x) \n", i, arm11->registers[i], arm11->registers[i]);
    }
    printf("PC  :%8i (0x%08x) \n", arm11->PC, arm11->PC);
    printf("CSPR:%8i (0x%08x) \n", arm11->CSPR, arm11->CSPR);

    printf("%s\n", "Non-zero memory:");
    for (i = 0; i < 65536; i += 4) {
        uint32_t value = getMemoryValue(i, arm11);
        if (value != 0) {
            printf("%08x:  0x%08x \n", i, value);
        }
    }
}

uint32_t fetch(struct ARM11 *arm11) {
    //TODO: Might need to add error if not multiple of 4
    return littleToBig(arm11->PC, arm11);
}

void printByte_inBinary(uint8_t byte) {
    uint8_t mask = 0;

    for (int i = 7; i >= 0; i--) {
        mask = (uint8_t) (1 << i);
        if ((mask & byte) > 0)
            printf("1");
        else
            printf("0");
    }
    printf("\n");
}

void readFile(char *fileName, struct ARM11 *arm11) {
    FILE *file = fopen(fileName, "r");
    char byte;
    int memoryLocation = 0;

    while ((byte = (char) fgetc(file)) != EOF) {
        //printf("%d - ",c);
        //printByte_inBinary(charToByte(c));
        arm11->memory[memoryLocation++] = (uint8_t) byte;
    }

    fclose(file);
}

//TODO: check if it goes out of memory
void fillPipeline(char *decoded, uint32_t *fetched, struct ARM11 *arm11) {

    *fetched = fetch(arm11);
    *decoded = decode(*fetched);
    *fetched = fetch(arm11);
}

//TODO: Place holder for real decode
char decode(uint32_t fetched) {
    return (char) fetched;
}

int main(int argc, char **argv) {
    struct ARM11 arm11;
    initialize(&arm11);
    readFile(argv[1], &arm11);

    uint32_t fetched;
    //TODO: Change type to struct from David
    char decoded;
    short int flag = 0;

    fillPipeline(&decoded, &fetched, &arm11);
    do {
        flag = execute(decoded, &arm11);

        if (flag == 1) {

        }
        decoded = decode(fetched);
        fetched = fetch(&arm11);
    } while (flag == -1);

    print(&arm11);
    return EXIT_SUCCESS;
}

