#include <stdlib.h>
#include <stdint.h>
#include "vector.h"


vector *new_vector_sized(uint64_t size)
{
    vector *new = (vector *)malloc(sizeof(vector));
    new->length = 0;
    new->size = 128;
    new->items = malloc(size * sizeof(int));

    return new;
}

vector *new_vector()
{
    return new_vector_sized(VEC_ALLOC_SIZE);
}

void free_vector(vector *v)
{
    free(v->items);
    free(v);
}

int vector_at(vector *v, uint64_t i, int32_t *ret)
{
    if (i < 0 || i > v->length)
        return 0;
    else
    {
        *ret = v->items[i];
        return 1;
    }
}

int vector_set(vector *v, uint64_t i, int32_t val)
{
    if (i >= v->size)
    {
        uint64_t new_len = v->size;

        while (i > new_len)
        {
            new_len *= 2;
        }
        
        v->items = realloc(v->items, new_len * sizeof(int32_t));

        if (v->items == NULL)
            return 0;
    }
    v->items[i] = val;
    return 1;
}

void vector_push(vector *v, int32_t val)
{
    if (v->length + 1 >= v->size)
    {
        // Reallocate memory
        v->items = realloc(v->items, (v->size * 2) * sizeof(int32_t));
    }
    v->items[v->length++] = val;
}
