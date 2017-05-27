#ifndef ARM11_37_EXECUTE_H
#define ARM11_37_EXECUTE_H

#include <stdio.h>;
#include "../emulate.h";

typedef enum flag {STOP, NORMAL, BRANCH};

//TODO: Add definition
enum flag execute(char decoded, struct ARM11* arm11);

#endif //ARM11_37_EXECUTE_H
