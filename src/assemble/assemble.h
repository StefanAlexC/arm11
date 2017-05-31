
#ifndef ARM11_37_ASSEMBLE_H_H
#define ARM11_37_ASSEMBLE_H_H

#define MAX_COMMAND_SIZE 50
#define MAX_NUMBER_COMMANDS 50
#define MAX_ARGUMENT_NUMBER 15
#define MAX_ARGUMENT_SIZE 15
#define FILE_NAME argv[1]
#define END_OF_MATRIX 0
#define SPLITTING_CHARACTERS " ,\n"

/**
 * Safely allocates a String of specified size.
 * @param size The length of the String.
 * @return A pointer to the created String.
 */
char *allocateString(int size);

/**
 * Safely allocate a String Matrix .
 * @param lines The number of line of the Matrix.
 * @param columns The length of each line of the Matrix.
 * @return A pointer to the created String Matrix.
 */
char **allocateStringMatrix(int lines, int columns);

/**
 * Parses a single String into an Array of Strings.
 * @param string The string the need to be parsed.
 * @return A pointer to the created Arrays of Strings
 */
char** parse(char *string);

/**
 * Reads line by line all the contents of a file.
 * @param fileName The file that need to be read.
 * @return A matrix containing the instructions from the given file
 */
char** readFile(char *fileName);

/**
 * Counts the number of arguments in a String Array.
 * @param array The String Array, whose arguments we need to count
 * @return The number of arguments.
 */
int numberArgumentsStringArray(char** array);

#endif //ARM11_37_ASSEMBLE_H_H
