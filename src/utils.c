//
// Created by DAVID BUTEREZ on 25/05/17.
//

#include "utils.h"
#include <stdio.h>

void printBits(uint32_t bits) {
    uint32_t mask = (uint32_t) (1 << (INSTR_BITS - 1));

    for (int i = 0; i < INSTR_BITS; i++) {
        printf("%i", (bits & mask) != 0);
        bits <<= 1;
    }

    printf("\n");
}

uint32_t setBit(uint32_t bits, int n, int b) {
    return (-b ^ bits) & (1 << n);
}

void changeBit(uint32_t *bits, int n, int b) {
    *bits = setBit(*bits, n, b);
}

uint32_t getBit(uint32_t bits, int n) {
    return (bits >> n) & 1;
}

uint32_t highestSetBitIndex(uint32_t bits) {
    int p = 0;
    while (bits != 0) {
        p++;
        bits >>= 1;
    }

    return (uint32_t) p;
}

uint32_t lowestSetBitIndex(uint32_t bits) {
    int p = 0;
    while ((bits & 1) == 0) {
        bits >>= 1;
        p++;
    }

    return (uint32_t) p;
}

uint32_t simpleMask(uint32_t bits, uint32_t mask) {
    return (bits & mask);
}

uint32_t mask(uint32_t bits, uint32_t mask) {
    bits &= mask;
    return (bits >> lowestSetBitIndex(mask));
}

//int main(void) {
//    printBits(0);
//    printf("%i", highestSetBitIndex(0));
//    printBits(RD_MASK);
//    printf("%i", lowestSetBitIndex(212425)); printf("%s", "\n");
//    printBits(mask(212425, RD_MASK));
//}

