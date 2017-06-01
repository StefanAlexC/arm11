
#ifndef ARM11_37_ASSEMBLE_H_H
#define ARM11_37_ASSEMBLE_H_H

#include "../arm11_utils.h"

#define INPUT_FILE_NAME argv[1]
#define OUTPUT_FILE_NAME argv[2]
#define SPLITTING_CHARACTERS " ,\n"
#define INSTRUCTION_STRING line[0]
#define BYTE_VALUE 8
#define BYTE_NUMBER 4

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
Map* firstPass(char **commands, int* numberNonLabels);

#endif //ARM11_37_ASSEMBLE_H_H
