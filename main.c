#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "stack.h"
#include "colors.h"
#include "bitcode.h"
#include "registers.h"
#include "asm.h"
#include "args.h"
#include "debug.h"


int main(int argc, char **argv)
{
    char *to_run = PARSE_STR("run", 'r');
    char *to_exec = PARSE_STR("execute", 'e');
    char *to_compile = PARSE_STR("compile", 'c');
    char *outfile = PARSE_STR("output", 'o');
    int debug = PARSE_BOOL("debug", 'D');

    if (strlen(to_compile) > 0)
    {
        if (strlen(outfile) == 0)
            critical("no output file provided. use --output <file> or -o <file>");
        status("Assembling", to_compile);
        vector *v = assemble_file(to_compile);
        status("Writing", outfile);
        
        FILE *fp = fopen(outfile, "wb");
        fwrite(v->items, sizeof(v), 1, fp);
        statusi("Written", sizeof(v));
    }
    else if (strlen(to_exec) > 0)
    {
        FILE *fp = fopen(to_exec, "rb");
        if (!fp)
            critical("unable to open file");
        
        fseek(fp, 0, SEEK_END);
        unsigned long len = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        int *buf = malloc(len);

        fread(buf, len, 1, fp);
        fclose(fp);

        stack *s = new_stack();
        stack *callstack = new_stack();
        registers r = { 0 };

        execute(buf, len / sizeof(int), s, callstack, r, debug);

        statusi("Returned", stack_pop(s));

        free_stack(s);
        free_stack(callstack);
    }
    else if (strlen(to_run) > 0)
    {
        status("Running", to_run);
        stack *s = new_stack();
        stack *callstack = new_stack();
        registers r = { 0 };

        vector *v = assemble_file(to_run);

        execute(v->items, v->length, s, callstack, r, debug);

        statusi("Returned", stack_pop(s));

        free_stack(s);
        free_stack(callstack);
    }
}
