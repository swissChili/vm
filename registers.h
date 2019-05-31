#ifndef VM_REGISTERS_H
#define VM_REGISTERS_H


struct registers
{
    int lt;
    int gt;
    int eq;
};
typedef int registers[7];

enum reg {
    EAX = 0,
    EBX,
    ECX,
    EDX,
    LT,
    GT,
    EQ
};

char get_regname(int);


#endif
