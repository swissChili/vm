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
        // printf(line);
        char lbl[256] = {};
        if (parse_label(line, lbl))
        {
            MAP_SET(labels, lbl, instruction + labels->count);
        }
        else if (parse_single(line))
        {
            instruction++;
        }
        else if (parse_double(line))
        {
            instruction += 2;
        }
    }

    // printf("\n\n\n\n");

    fp = fopen(file, "r");

    while (fgets(line, sizeof(line), fp))
    {
        int post_int = 0;
        char post_char = 0;
        char post_str[256] = {};

        // printf("%s", line);

        if (parse_int_arg(line, "PSH", &post_int))
        {
            vector_push(vec, PSH);
            vector_push(vec, post_int);
        }
        else if (parse_label(line, post_str))
        {
        }
        else if (parse_skip(line))
        {
        }
        else if (parse_reg_arg(line, "POP", &post_char))
        {
            int reg = post_char - 'A';
            if (reg >= EAX && reg <= EDX)
            {
                vector_push(vec, POP);
                vector_push(vec, reg);
            }
            else
            {
                fprintf(
                    stderr,
                    "POP register needs to be EAX-EDX, found E%cX\n",
                    post_char
                );
                exit(1);
            }
        }
        else if (parse_reg_arg(line, "LDR", &post_char))
        {
            int reg = post_char - 'A';
            if (reg >= EAX && reg <= EDX)
            {
                vector_push(vec, LDR);
                vector_push(vec, reg);
            }
            else
            {
                fprintf(
                    stderr,
                    "LDR register needs to be EAX-EDX, found E%cX\n",
                    post_char
                );
                exit(1);
            }
        }
        else if (parse_lit(line, "ADD"))
        {
            vector_push(vec, ADD);
        }
        else if (parse_lit(line, "SUB"))
        {
            vector_push(vec, SUB);
        }
        else if (parse_lit(line, "MLT"))
        {
            vector_push(vec, MLT);
        }
        else if (parse_lit(line, "DIV"))
        {
            vector_push(vec, DIV);
        }
        else if (parse_int_arg(line, "JMP", &post_int))
        {
            vector_push(vec, JMP);
            vector_push(vec, post_int);
        }
        else if (parse_label_arg(line, "JMP", post_str))
        {
            vector_push(vec, JMP);
            vector_push(vec, MAP_GET(int, labels, post_str));
        }
        else if (parse_lit(line, "JPS"))
        {
            vector_push(vec, JPS);
        }
        else if (parse_lit(line, "CMP"))
        {
            vector_push(vec, CMP);
        }
        else if (parse_int_arg(line, "JEQ", &post_int))
        {
            vector_push(vec, JEQ);
            vector_push(vec, post_int);
        }
        else if (parse_label_arg(line, "JEQ", post_str))
        {
            vector_push(vec, JEQ);
            vector_push(vec, MAP_GET(int, labels, post_str));
        }
        else if (parse_int_arg(line, "JNE", &post_int))
        {
            vector_push(vec, JNE);
            vector_push(vec, post_int);
        }
        else if (parse_label_arg(line, "JNE", post_str))
        {
            vector_push(vec, JNE);
            vector_push(vec, MAP_GET(int, labels, post_str));
        }
        else if (parse_int_arg(line, "JLT", &post_int))
        {
            vector_push(vec, JLT);
            vector_push(vec, post_int);
        }
        else if (parse_label_arg(line, "JLT", post_str))
        {
            vector_push(vec, JLT);
            vector_push(vec, MAP_GET(int, labels, post_str));
        }
        else if (parse_int_arg(line, "JGT", &post_int))
        {
            vector_push(vec, JGT);
            vector_push(vec, post_int);
        }
        else if (parse_label_arg(line, "JGT", post_str))
        {
            vector_push(vec, JGT);
            vector_push(vec, MAP_GET(int, labels, post_str));
        }
        else if (parse_lit(line, "INC"))
        {
            vector_push(vec, INC);
        }
        else if (parse_lit(line, "DEC"))
        {
            vector_push(vec, DEC);
        }
        else if (parse_lit(line, "SWP"))
        {
            vector_push(vec, SWP);
        }
        else if (parse_lit(line, "RET"))
        {
            vector_push(vec, RET);
        }
        else if (parse_lit(line, "DUP"))
        {
            vector_push(vec, DUP);
        }
        else if (parse_int_arg(line, "CAL", &post_int))
        {
            vector_push(vec, CAL);
            vector_push(vec, post_int);
        }
        else if (parse_label_arg(line, "CAL", post_str))
        {
            vector_push(vec, CAL);
            printf("\nCalling %s\n\n", post_str);
            map_debug(labels);
            vector_push(vec, MAP_GET(int, labels, post_str));
        }
        else if (parse_lit(line, "END"))
        {
            vector_push(vec, END);
        }
        else
        {
            fprintf(stderr, "Unknown instruction %s\n", line);
            exit(1);
        }
    }
    return vec;
}
