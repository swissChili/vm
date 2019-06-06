#ifndef VM_ARGS_H
#define VM_ARGS_H


enum arg_status
{
    PROGRAM = 0,
    FLAG,
    NONE,
};

enum arg_type
{
    ARG_BOOL,
    ARG_STRING,
};

void *parse_arg(int, char **, int, char *);

// this is horribly unsafe but it's c and I don't have a choice. I'm casting a
// void * to an int so I don't have to use the heap to return a pointer to the
// value and end up dereferencing it right after anyway.
#define PARSE_BOOL(argc, argv, name) (int)parse_arg(argc, argv, ARG_BOOL, name)
#define PARSE_STR(argc, argv, name) (char *)parse_arg(argc, argv, ARG_STRING, name)

#endif
