#include "parse.h"
#include <stdio.h>

#define SINGLES_LEN 3
#define DOUBLES_LEN 10

static char singles[][4] = {
    "ADD",
    "SUB",
    "MLT",
    "DIV",
    "JPS",
    "CMP",
    "INC",
    "DEC",
    "SWP",
    "RET",
    "DUP",
    "END",
};

static char doubles[DOUBLES_LEN][4] = {
    "PSH",
    "POP",
    "LDR",
    "JMP",
    "JPS",
    "JEQ",
    "JNE",
    "JLT",
    "JGT",
    "CAL"
};

int is_whitespace(char c)
{
    switch (c)
    {
        case ' ':
        case '\t':
        case '\n':
        case '\r':
            return 1;
        default:
            return 0;
    }
}

int is_valid_ident(char c)
{
    switch (c)
    {
        case 0:
        case ' ':
        case '\t':
        case '\n':
        case '\r':
        case '\\':
        case '\'':
        case '"':
            return 0;
        default:
            return 1;
    }
}

#define SKIP_WS() while (is_whitespace(*line)) line++

int parse_label(char line[], char label[])
{
    SKIP_WS();

    if (*line != '@')
        return 0;

    line++;

    SKIP_WS();

    int i = 0;

    while (is_valid_ident(*line))
        label[i++] = *line++;

    return 1;
}

int parse_skip(char line[])
{
    SKIP_WS();
    if (*line)
        if (*line == ';')
            return 1;
        else
            return 0;
    else
        return 1;
}

int parse_lit(char line[], char lit[])
{
    int i = 0;
    while (is_whitespace(*line))
    {
        line++;
        i++;
    }

    while (*lit)
    {
        if (*lit != *line)
            return 0;
    
        lit++;
        line++;
        i++;
    }
    // printf("line ended with %s (%s)", line, lit);
    return i;
}

int parse_int_arg(char line[], char lit[], int *parsed)
{
    int i;
    if ((i = parse_lit(line, lit)))
    {
        // printf("i is %d, '%s'\n", i, line + i);
        return parse_int(line + i, parsed);
    }
    return 0;
}

int parse_int(char line[], int *parsed)
{
    SKIP_WS();
    // printf("\n\nparse_int line = '%s'", line);
    int res = sscanf(line, "%d", parsed);

    // printf("res %d, given %d\n", res, *parsed);
    return res;
}

int parse_reg_arg(char line[], char lit[], char reg[])
{
    int i;
    if ((i = parse_lit(line, lit)))
    {
        // printf("i is %d\n", i);
        return parse_register(line + i, reg);
    }
    return 0;
}

int parse_register(char line[], char *reg)
{
    SKIP_WS();

    // printf("\n\nregister line = %s", line);

    int res = sscanf(line, "E%cX", reg);

    // printf("Register %c, is %dth\n", *reg, *reg - 'A');

    // printf("res %d, given %c\n", res, *reg);

    return res;
}

int parse_label_arg(char line[], char lit[], char label[])
{
    int i;
    if ((i = parse_lit(line, lit)))
    {
        return parse_label(line + i, label);
    }
    return 0;
}

int parse_single(char line[])
{
    for (int i = 0; i < SINGLES_LEN; ++i)
    {
        if (parse_lit(line, singles[i]))
            return 1;
    }
    return 0;
}

int parse_double(char line[])
{
    for (int i = 0; i < DOUBLES_LEN; ++i)
    {
        if (parse_lit(line, doubles[i]))
            return 1;
    }
    return 0;
}
