
#ifndef ARM11_37_ASSEMBLE_H_H
#define ARM11_37_ASSEMBLE_H_H

#include "utils.h"

#define MAX_COMMAND_SIZE 50
#define MAX_NUMBER_COMMANDS 50
#define MAX_ARGUMENT_NUMBER 15
#define MAX_ARGUMENT_SIZE 15
#define CHAR_TYPE 0
#define MAP_TYPE 1
#define FILE_NAME argv[1]
#define SPLITTING_CHARACTERS " ,\n"
#define INSTRUCTION_STRING line[0]
#define BYTE_VALUE 8
#define BYTE_NUMBER 4



/**
 * Safely allocates a String of specified size.
 * @param size The length of the String.
 * @param Defines the return type, if mode is True then the returned array is int32_t otherwise it is a char array.
 * @return A pointer to the created String.
 */
void* allocateArray(int size, bool mode);

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

/**
 * Countrs the number of arguments in a Int32_t Array
 * @param array The Int32_t Array, whose arguments we need to count
 * @return The number of arguments
 */
int numberArgumentsInt32Array(int **array);

/**
 * Checks if the commands is a label.
 * @param command The commands which we want to check.
 * @return Whether or not the given command is a label.
 */
bool isLabel(char *command);

/**
 * Does a first pass over all commands to create a mapping from labels to memory locations.
 * @param commands The Array of Strings containing all commands.
 * @return An array of the desired mappings.
 */
Map* firstPass(char **commands);

#endif //ARM11_37_ASSEMBLE_H_H
