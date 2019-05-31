#include "registers.h"

char get_regname(int reg)
{
    char regname;
    switch (reg)
    {
        case EAX:
            regname = 'A';
            break;
        case EBX:
            regname = 'B';
            break;
        case ECX:
            regname = 'C';
            break;
        case EDX:
            regname = 'D';
            break;
    }
    return regname;
}
