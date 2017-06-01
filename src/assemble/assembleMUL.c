#include "assembleMUL.h"
#include "assembleSDT.h"

uint32_t assembleMultiply(char **parameters) {
    uint32_t rd = intFromString(RD);
    uint32_t rm = intFromString(RM);
    uint32_t rs = intFromString(RS);
    uint32_t rn = 0;

    /**
     * Default condition is AL
     */
    uint32_t result = DEFAULT_CONDITION_CODE;

    /**
     * Shifted right to create the pattern
     */
    result <<= (MUL_PATTERN_SIZE + 1);

    /**
     * Checks the A flag and if we need to calculate the Rn register
     */
    if (strcmp(MUL_OPCODE, MLA) == 0) {
        result += 1;
        rn = intFromString(RN);
    }

    /**
     * Adds the S flag
     */
    result <<= 1;

    /**
     * Adds the Rd register
     */
    result <<= REG_SIZE;
    result += rd;

    /**
     * Adds the Rn register
     */
    result <<= REG_SIZE;
    result += rn;

    /**
     * Adds the Rs register
     */
    result <<= REG_SIZE;
    result += rs;

    /**
     * Adds operation pattern 1001
     */
    result <<= REG_SIZE;
    result += MUL_PATTERN;

    /**
     * Adds the Rm register
     */
    result <<= REG_SIZE;
    result += rm;

    return result;
}
