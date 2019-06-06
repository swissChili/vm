#include <stdio.h>
#include <string.h>

#include "stack.h"
#include "colors.h"
#include "bitcode.h"
#include "registers.h"
#include "asm.h"
#include "args.h"


int main(int argc, char **argv)
{
    int assemble = PARSE_BOOL(argc, argv, "assemble");
    char *file = PARSE_STR(argc, argv, "file");

    if (assemble && strlen(file) > 0)
    {
        stack *s = new_stack();
        stack *callstack = new_stack();
        registers r = { 0 };

        vector *v = assemble_file(file);

        execute(v->items, v->length, s, callstack, r);

        printf("Returned %d\n", stack_pop(s));

        free_stack(s);
        free_stack(callstack);
    }
}
