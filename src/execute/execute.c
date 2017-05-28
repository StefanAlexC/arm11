#include "execute.h"

FLAG execute(char decoded, struct ARM11* arm11) {
    enum FLAG temp = NORMAL;
    if (decoded == 'a') {
        temp = STOP;
        return temp;
    }
    arm11->registers[10] += 1;
    return temp;
}

