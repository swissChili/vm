#ifndef VM_BITCODE_H
#define VM_BITCODE_H

#include <stdint.h>
#include "stack.h"
#include "registers.h"


enum instruction
{
    PSH = 0,
    POP,
    LDR,
    ADD,
    SUB,
    MLT,
    DIV,
    JMP,
    JPS,
    CMP,
    JEQ,
    JNE,
    JLT,
    JGT,
    INC,
    DEC,
    SWP,
    RET,
    DUP,
    CAL,
    END,
};

#define ifdb(a) if (debug) a

void execute(int32_t[], uint64_t, stack *, stack *, registers, int);


#endif
