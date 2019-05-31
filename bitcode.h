#ifndef VM_BITCODE_H
#define VM_BITCODE_H

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
};

void execute(int[], int, stack *, registers);


#endif
