#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "assemble.h"

char *allocateString(int size) {
    char *line = malloc((size + 1) * sizeof(char));

    if (line == NULL) {
        perror("MALLOC-MATRIX_LINE");
        exit(EXIT_FAILURE);
    }

    return line;
}

char **allocateStringMatrix(int lines, int columns) {
    char **matrix = malloc(lines * sizeof(char *));

    if (matrix == NULL) {
        perror("MALLOC-MATRIX");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < lines; i++) {
        matrix[i] = allocateString(columns);
    }

    return matrix;
}

char** parse(char *string) {
    char *token = strtok(string, SPLITTING_CHARACTERS);
    char **parsedString = allocateStringMatrix(MAX_ARGUMENT_NUMBER, MAX_ARGUMENT_SIZE);
    int arguments = 0;

    while (token != NULL) {
        parsedString[arguments++] = token;
        //printf("%s\n",parsedString[arguments - 1]);
        token = strtok(NULL, SPLITTING_CHARACTERS);
    }
    parsedString[arguments] = END_OF_MATRIX;

    for (int i = arguments + 1 ; i < MAX_ARGUMENT_NUMBER ; i++) {
        free(parsedString[arguments]);
    }

    return realloc(parsedString, (arguments + 1) * sizeof(char *));
}

char** readFile(char *fileName) {
    FILE *file = fopen(fileName, "r");
    char **commandLines = allocateStringMatrix(MAX_COMMAND_SIZE, MAX_COMMAND_SIZE);
    int lines = 0;

    while (!feof(file)) {
        fgets(commandLines[lines++], MAX_COMMAND_SIZE, file);
        //printf("%s", commandLines[lines - 1]);
    }

    commandLines[--lines] = END_OF_MATRIX;

    for (int i = lines + 1; i < MAX_NUMBER_COMMANDS; i++) {
        free(commandLines[i]);
    }
    commandLines = realloc(commandLines, (lines + 1) * sizeof(char *));
    fclose(file);

    return commandLines;
}

int numberArgumentsStringArray(char** array) {
    int length;

    for (length = 0 ; array[length] != END_OF_MATRIX ; length++);

    return length;
}

int main(int argc, char **argv) {
    char **commands = readFile(FILE_NAME);

    for (int i = 0 ; commands[i] != END_OF_MATRIX ; i++) {
        char **line = parse(commands[i]);
        //printf("%d\n", numberArgumentsStringArray(line));
    }

    return EXIT_SUCCESS;
}
