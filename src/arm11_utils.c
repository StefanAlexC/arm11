#include "arm11_utils.h"
#include <stdlib.h>

//TODO: remove only for testing

uint32_t genMask(int start, int end) {
    uint32_t mask = 0;
    for (int i = 31; i >= start; --i) {
        if (i == end) {
            for (int j = end; j >= start; --j) {
                mask = mask | (1 << j);
            }
        }
    }
    return mask;
}

uint32_t extractBit(uint32_t n, int start, int end) {
    uint32_t mask = genMask(start, end);
    n = n & mask;
    n = n >> start;
    return n;
}

void printBits(uint32_t instruction) {
    uint32_t i, mask;
    mask = 1;
    mask <<= 31;
    for(i = 0; i < 32; i++) {
        printf("%u", (instruction & mask) > 0);
        if (i % 8 == 7) {
            printf(" ");
        }
        instruction <<= 1;
    }
    printf("\n");
}

void* allocateArray(int size, bool mode) {
    void *array;
    if (mode) {
        array = calloc((uint)(size + 1), sizeof(Map));
    } else {
        array = calloc((uint)(size + 1), sizeof(char));
    }

    if (array == NULL) {
        perror("MALLOC-ARRAY");
        exit(EXIT_FAILURE);
    }

    return array;
}

char** allocateStringMatrix(int lines, int columns) {
    char **matrix = calloc((uint)lines, sizeof(char *));

    if (matrix == NULL) {
        perror("MALLOC-MATRIX");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < lines; i++) {
        matrix[i] = allocateArray(columns, CHAR_TYPE);
    }

    return matrix;
}

int numberArgumentsStringArray(char **array) {
    int length;

    for (length = 0; array[length] != NULL ; length++);

    return length;
}

int numberArgumentsInt32Array(int **array) {
    int length;

    for (length = 0; array[length] != NULL ; length++);

    return length;
}

void printAsChar(uint32_t number) {
    char temp = (char) extractBit(number, SECOND_BYTE_END + 1, FIRST_BYTE_END);
    printf("%c", temp);
    temp = (char) extractBit(number, THIRD_BYTE_END + 1, SECOND_BYTE_END);
    printf("%c", temp);
    temp = (char) extractBit(number, FOURTH_BYTE_END + 1, THIRD_BYTE_END);
    printf("%c", temp);
    temp = (char) extractBit(number, 0 , FOURTH_BYTE_END);
    printf("%c", temp);
}

