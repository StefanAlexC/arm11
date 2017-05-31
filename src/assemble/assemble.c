#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "assemble.h"
#include "encode.h"
#include "utils.h"

void* allocateArray(int size, bool mode) {
    void *array;
    if (mode) {
        array = malloc((size + 1) * sizeof(Map));
    } else {
        array = malloc((size + 1) * sizeof(char));
    }

    if (array == NULL) {
        perror("MALLOC-ARRAY");
        exit(EXIT_FAILURE);
    }

    return array;
}

char **allocateStringMatrix(int lines, int columns) {
    char **matrix = malloc(lines * sizeof(char *));

    if (matrix == NULL) {
        perror("MALLOC-MATRIX");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < lines; i++) {
        matrix[i] = (char *)allocateArray(columns, CHAR_TYPE);
    }

    return matrix;
}

char **parse(char *string) {
    char *token = strtok(string, SPLITTING_CHARACTERS);
    char **parsedString = allocateStringMatrix(MAX_ARGUMENT_NUMBER, MAX_ARGUMENT_SIZE);
    int arguments = 0;

    while (token != NULL) {
        parsedString[arguments++] = token;
        //printf("%s\n",parsedString[arguments - 1]);
        token = strtok(NULL, SPLITTING_CHARACTERS);
    }
    parsedString[arguments] = END_OF_MATRIX;

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

    commandLines[lines] = END_OF_MATRIX;

    for (int i = lines + 1; i < MAX_NUMBER_COMMANDS; i++) {
        free(commandLines[i]);
    }
    commandLines = realloc(commandLines, (lines + 1) * sizeof(char *));
    fclose(file);

    return commandLines;
}

int numberArgumentsStringArray(char **array) {
    int length;

    for (length = 0; array[length] != END_OF_MATRIX; length++);

    return length;
}

int numberArgumentsInt32Array(int **array) {
    int length;

    for (length = 0; array[length] != END_OF_MATRIX; length++);

    return length;
}

bool isLabel(char *command) {
    return strstr(command, ":") != NULL;
}

//TODO: Might need to modify address
Map* firstPass(char **commands) {
    Map *labels = allocateArray(MAX_NUMBER_COMMANDS, MAP_TYPE);
    int numberLabels = 0;
    int numberNonLabels = 0;

    for (int i = 0 ; commands[i] != END_OF_MATRIX ; i++) {
        if (isLabel(commands[i])) {
            labels[numberLabels].key = commands[i];
            labels[numberLabels++].value = numberNonLabels + 1;
        } else {
            numberNonLabels++;
        }
    }
    labels[numberLabels].value = END_OF_MAP;

    return realloc(labels, (numberLabels + 1) * sizeof(Map));
}


int main(int argc, char **argv) {
    char **commands = readFile(FILE_NAME);
    Map *labels = firstPass(commands);

    char **line;
/*    for (int i = 0 ; commands[i] != END_OF_MATRIX; i++) {
        line = parse(commands[i]);
        //printf("%d\n", numberArgumentsStringArray(line));
        printf("%d\n",encode(numberArgumentsStringArray(line), line, labels));
    }*/

    for (int i = 0 ; labels[i].value != END_OF_MAP ; i++) {
        printf("%s -> %d\n", labels[i].key, labels[i].value);
    }

    return EXIT_SUCCESS;
}
