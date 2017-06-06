#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "assemble.h"
#include "encode.h"

static FILE* outputFile;



char **parse(char *string, int *numberOfElems) {
    char *token = strtok(string, SPLITTING_CHARACTERS);
    char **parsedString = allocateStringMatrix(MAX_ARGUMENT_NUMBER, MAX_ARGUMENT_SIZE);
    int arguments = 0;

    while (token != NULL) {
        strcpy(parsedString[arguments++], token);
        token = strtok(NULL, SPLITTING_CHARACTERS);
    }

    parsedString[arguments] = NULL;

    for (int i = arguments + 1; i < MAX_ARGUMENT_NUMBER; i++) {
        free(parsedString[i]);
    }

    *numberOfElems = arguments + 1;

    return realloc(parsedString, (arguments + 1) * sizeof(char *));
}

bool isEmpty(char *string) {
    for (int i = 0 ; string[i] ; i++) {
        if (isalpha(string[i]))
            return false;
    }
    return true;
}

char **readFile(char *fileName) {
    FILE *file = fopen(fileName, "r");
    char **commandLines = allocateStringMatrix(MAX_COMMAND_SIZE, MAX_COMMAND_SIZE);
    int lines = 0;

    while (!feof(file)) {
        fgets(commandLines[lines++], MAX_COMMAND_SIZE, file);
        if (isEmpty(commandLines[lines - 1])) {
            lines--;
        }

    }

    commandLines[lines] = NULL;

    for (int i = lines + 1; i < MAX_NUMBER_COMMANDS; i++) {
        free(commandLines[i]);
    }
    commandLines = realloc(commandLines, (lines + 1) * sizeof(char *));
    fclose(file);

    return commandLines;
}

bool isLabel(char *command) {
    return strstr(command, ":") != NULL;
}

Map *firstPass(char **commands, int* numberNonLabels) {
    Map *labels = allocateArray(MAX_NUMBER_COMMANDS, MAP_TYPE);
    int numberLabels = 0;

    for (int i = 0; commands[i] != NULL ; i++) {
        if (isLabel(commands[i])) {
            labels[numberLabels].key = commands[i];
            labels[numberLabels++].value = *numberNonLabels;
        } else {
            *numberNonLabels += 1;
        }
    }
    *numberNonLabels *= BYTE_NUMBER;
    labels[numberLabels].value = END_OF_MAP;

    return realloc(labels, (numberLabels + 1) * sizeof(Map));
}

void freeStringMatrix(char** strMatrix, int rows) {
    if (!strMatrix) {
        return;
    }

    for (int i = 0; i < rows; i++) {
        free(strMatrix[i]);
    }
    free(strMatrix);
}

int main(int argc, char **argv) {
    char **commands = readFile(INPUT_FILE_NAME);
    int numberOperations = 0;
    Map *labels = firstPass(commands, &numberOperations);
    int32_t currentOperationNumber = 0;
    char **line;
    uint32_t remenants[MAX_NUMBER_COMMANDS];
    remenants[0] = 0;

    outputFile = freopen(OUTPUT_FILE_NAME, "w", stdout);

    int elems = 0;

    for (int i = 0 ; commands[i] != NULL ; i++) {
        line = parse(commands[i], &elems);
        if (!isLabel(INSTRUCTION_STRING)) {
            encode(numberArgumentsStringArray(line), line, labels, currentOperationNumber, &numberOperations, remenants);
            currentOperationNumber++;
        }
        freeStringMatrix(line, elems);
    }

    free(labels);
    freeStringMatrix(commands, currentOperationNumber);

    for (uint32_t i = 1 ; i <= remenants[0] ; i++) {
        printAsChar(remenants[i]);
    }

    fclose(outputFile);




    return EXIT_SUCCESS;
}
