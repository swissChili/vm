#include <stdio.h>
#include <stdlib.h>

#include "debug.h"
#include "colors.h"


void status(const char *title, const char *body)
{
    printf(C_CYAN PADDING C_RESET " %s\n", title, body);
}

void statusi(const char *title, int body)
{
    printf(C_CYAN PADDING C_RESET " %d\n", title, body);
}

void critical(const char *error)
{
    printf(C_RED PADDING C_RESET " %s\n", "Error", error);
    exit(1);
}

void warning(const char *warning)
{
    printf(C_YELLOW PADDING C_RESET " %s\n", "Warning", warning);
}
