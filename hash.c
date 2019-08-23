#include "hash.h"

uint64_t hash(char *str)
{
    uint64_t hash = 5381;
    char c;

    while (c = *str++)
        hash = (hash << 5) + hash + c;

    return hash;
}
