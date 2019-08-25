#include "parse.h"
#include <stdio.h>


int is_whitespace(char c)
{
    switch (c)
    {
        case ' ':
        case '\t':
        case '\n':
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
}
