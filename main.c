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
    char *to_run = PARSE_STR("run", 'r');
    int debug = PARSE_BOOL("debug", 'D');

    if (strlen(to_run) > 0)
    {
        printf(C_CYAN "Running %s with debug mode %d\n" C_RESET, to_run, debug);
        stack *s = new_stack();
        stack *callstack = new_stack();
        registers r = { 0 };

        vector *v = assemble_file(to_run);

        execute(v->items, v->length, s, callstack, r, debug);

        printf("Returned %d\n", stack_pop(s));

        free_stack(s);
        free_stack(callstack);
    }
}
