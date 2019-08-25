#include <stdio.h>
#include <stdlib.h>
#include "asm.h"
#include "colors.h"
#include "bitcode.h"
#include "map.h"
#include "parse.h"


vector *assemble_file(const char *file)
{
    vector *vec = new_vector();
    FILE *fp = fopen(file, "r");
    char line[512];

    map *labels = new_map();

    uint64_t instruction = 0;

    while (fgets(line, sizeof(line), fp))
    {
        printf(line);
        char lbl[256];
        if (parse_label(line, lbl))
        {
            MAP_SET(labels, lbl, instruction);
            printf(C_CYAN "is label '%s' at %d\n" C_RESET, lbl, instruction);
        }
        else if (!parse_skip(line))
        {
            instruction++;
            puts(C_GREEN "Instruction++" C_RESET);
        }
    }

    printf("\n\n\n\n");

    fp = fopen(file, "r");

    while (fgets(line, sizeof(line), fp))
    {
        int post_int = 0;
        char post_char = 0;
        char post_str[256];

        printf("%s", line);

        if (sscanf(line, "PSH %d", &post_int))
        {
            vector_push(vec, PSH);
            vector_push(vec, post_int);
        }
        else if (parse_label(line, post_str))
        {
            printf("!!skipping\n");
        }
        else if (sscanf(line, "POP E%cX", &post_char))
        {
            int reg = post_char - 'A';
            if (reg >= EAX && reg <= EDX)
            {
                vector_push(vec, POP);
                vector_push(vec, reg);
            } else
            {
                fprintf(
                    stderr,
                    "POP register needs to be EAX-EDX, found E%cX\n",
                    post_char
                );
                exit(1);
            }
        }
        else if (sscanf(line, "LDR E%cX", &post_char))
        {
            int reg = post_char - 'A';
            if (reg >= EAX && reg <= EDX)
            {
                vector_push(vec, LDR);
                vector_push(vec, reg);
            } else
            {
                fprintf(
                    stderr,
                    "LDR register needs to be EAX-EDX, found E%cX\n",
                    post_char
                );
                exit(1);
            }
        }
        else if (sscanf(line, "ADD"))
        {
            vector_push(vec, ADD);
        }
        else if (sscanf(line, "SUB"))
        {
            vector_push(vec, SUB);
        }
        else if (sscanf(line, "MLT"))
        {
            vector_push(vec, MLT);
        }
        else if (sscanf(line, "DIV"))
        {
            vector_push(vec, DIV);
        }
        else if (sscanf(line, "JMP %d", &post_int))
        {
            vector_push(vec, JMP);
            vector_push(vec, post_int);
        }
        else if (sscanf(line, "JMP @ %s", post_str))
        {
            vector_push(vec, JMP);
            vector_push(vec, MAP_GET(int, labels, post_str));
        }
        else if (sscanf(line, "JPS"))
        {
            vector_push(vec, JPS);
        }
        else if (sscanf(line, "CMP"))
        {
            vector_push(vec, CMP);
        }
        else if (sscanf(line, "JEQ %d", &post_int))
        {
            vector_push(vec, JEQ);
            vector_push(vec, post_int);
        }
        else if (sscanf(line, "JEQ @ %s", post_str))
        {
            vector_push(vec, JEQ);
            vector_push(vec, MAP_GET(int, labels, post_str));
        }
        else if (sscanf(line, "JNE %d", &post_int))
        {
            vector_push(vec, JNE);
            vector_push(vec, post_int);
        }
        else if (sscanf(line, "JNE @ %s", post_str))
        {
            vector_push(vec, JNE);
            vector_push(vec, MAP_GET(int, labels, post_str));
        }
        else if (sscanf(line, "JLT, %d", &post_int))
        {
            vector_push(vec, JLT);
            vector_push(vec, post_int);
        }
        else if (sscanf(line, "JGT %d", &post_int))
        {
            vector_push(vec, JGT);
            vector_push(vec, post_int);
        }
        else if (sscanf(line, "JGT @ %s", post_str))
        {
            vector_push(vec, JGT);
            vector_push(vec, MAP_GET(int, labels, post_str));
        }
        else if (sscanf(line, "INC"))
        {
            vector_push(vec, INC);
        }
        else if (sscanf(line, "DEC"))
        {
            vector_push(vec, DEC);
        }
        else if (sscanf(line, "SWP"))
        {
            vector_push(vec, SWP);
        }
        else if (sscanf(line, "RET"))
        {
            vector_push(vec, RET);
        }
        else if (sscanf(line, "DUP"))
        {
            vector_push(vec, DUP);
        }
        else if (sscanf(line, "CAL %d", &post_int))
        {
            vector_push(vec, CAL);
            vector_push(vec, post_int);
        }
        else if (sscanf(line, "CAL @ %s", post_str))
        {
            vector_push(vec, CAL);
            vector_push(vec, MAP_GET(int, labels, post_str));
        }
        else if (sscanf(line, "END"))
        {
            vector_push(vec, END);
        }
        else if (sscanf(line, ";"))
        {
            /* nothing */
        }
        else
        {
            fprintf(stderr, "Unknown instruction %s\n", line);
            exit(1);
        }
    }
    return vec;
}
