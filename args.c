#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "args.h"
#include "colors.h"


void *parse_arg(int argc, char **argv, int t, char *name, char shortname)
{
    int type = PROGRAM;
    int arg_bool = 0;
    int done = 0;
    char *last = (char *)malloc(sizeof(char[128]));
    char *arg_str = (char *)malloc(sizeof(char[128]));

    for (int i = 0; i < argc && !done; i++)
    {
        switch (type)
        {
            case PROGRAM:
                type = NONE;
                break;
            case NONE:
                if (strlen(argv[i]) > 1 && argv[i][0] == '-')
                {
                    if (strlen(argv[i]) > 2 && argv[i][1] == '-')
                    {
                        strncpy(last, &argv[i][2], 128);
                        type = FLAG;
                    }
                    else
                    {
                        int len = strlen(argv[i]);
                        if (argv[i][len - 1] == shortname && t == ARG_STRING)
                        {
                            type = FLAG;
                            strcpy(last, name);
                            break;
                        }
                        // skip the - so j == 1
                        for (int j = 1; j < len; j++)
                        {
                            if (argv[i][j] == shortname)
                            {
                                arg_bool = 1;
                                done = 1;
                            }
                        }
                    }
                    
                }
                break;
            case FLAG:
                switch (t)
                {
                    case ARG_BOOL:
                        if (strcmp(last, name) == 0)
                        {
                            if (strcmp(argv[i], "true") == 0)
                                arg_bool = 1;
                            else
                                arg_bool = 0;
                            done = 1;
                        }
                        break;
                    case ARG_STRING:
                        if (strcmp(last, name) == 0)
                        {
                            strcpy(arg_str, argv[i]);
                            done = 1;
                        }
                }
                type = NONE;
        }
    }

    switch(t)
    {
        case ARG_BOOL:
            return arg_bool;
        case ARG_STRING:
            return (void *) arg_str;
    }
    // if execution reaches this point something has gone horribly wrong
    return NULL;
}
