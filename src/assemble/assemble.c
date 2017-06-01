#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "assemble.h"
#include "encode.h"



char **parse(char *string) {
    char *token = strtok(string, SPLITTING_CHARACTERS);
    char **parsedString = allocateStringMatrix(MAX_ARGUMENT_NUMBER, MAX_ARGUMENT_SIZE);
    int arguments = 0;

    while (token != NULL) {
        parsedString[arguments++] = token;
        //printf("%s\n",parsedString[arguments - 1]);
        token = strtok(NULL, SPLITTING_CHARACTERS);
    }
    parsedString[arguments] = NULL;

    for (int i = arguments + 1; i < MAX_ARGUMENT_NUMBER; i++) {
        free(parsedString[arguments]);
    }

    return realloc(parsedString, (arguments + 1) * sizeof(char *));
}

char **readFile(char *fileName) {
    FILE *file = fopen(fileName, "r");
    char **commandLines = allocateStringMatrix(MAX_COMMAND_SIZE, MAX_COMMAND_SIZE);
    int lines = 0;

    while (!feof(file)) {
        fgets(commandLines[lines++], MAX_COMMAND_SIZE, file);
        //printf("%s", commandLines[lines - 1]);
    }

    commandLines[--lines] = NULL;

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
    *numberNonLabels *= BYTE_VALUE;
    labels[numberLabels].value = END_OF_MAP;

    return realloc(labels, (numberLabels + 1) * sizeof(Map));
}

int main(int argc, char **argv) {
    char **commands = readFile(FILE_NAME);
    int numberOperations = 0;
    Map *labels = firstPass(commands, &numberOperations);
    int32_t currentOperationNumber = 0;
    char **line;
    uint32_t remenants[MAX_NUMBER_COMMANDS];

    for (int i = 0 ; commands[i] != NULL ; i++) {
        line = parse(commands[i]);
        if (!isLabel(INSTRUCTION_STRING)) {
            encode(numberArgumentsStringArray(line), line, labels, currentOperationNumber, &numberOperations, remenants);
            currentOperationNumber++;
        }
    }

    for (uint32_t i = 1 ; i <= remenants[0] ; i++) {
        printBits(remenants[i]);
    }

    return EXIT_SUCCESS;
}
