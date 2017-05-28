#ifndef ARM11_37_EXECUTE_H
#define ARM11_37_EXECUTE_H

#include "../emulate.h"

typedef enum FLAG {STOP, NORMAL, BRANCH} FLAG;

//TODO: Add definition
FLAG execute(char decoded, struct ARM11* arm11);

#endif //ARM11_37_EXECUTE_H
