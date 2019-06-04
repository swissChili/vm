#ifndef VM_ASM_H
#define VM_ASM_H

#include "vector.h"


typedef int (*handler)(int *, int);

vector *assemble_file(const char*);

void repl(handler);


#endif
