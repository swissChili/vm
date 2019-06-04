#include <stdio.h>
#include "asm.h"
#include "colors.h"
#include "bitcode.h"


vector *assemble_file(const char *file)
{
    return new_vector();
}

void repl(handler h)
{
    int running = 1;

    while(running)
    {
        printf("repl> ");
        int length = 1;
        int assembled[2];

        int post_int;

        if (scanf("PSH %d", &post_int))
        {
            assembled[0] = PSH;
            assembled[1] = post_int;
            length = 2;

            printf("\nPSH %d\n", post_int);
        } else
        {
            printf("\nno\n");
        }
    }
}
