#include <stdlib.h>
#include <stdint.h>
#include "vector.h"


vector *new_vector()
{
    vector *new = (vector *)malloc(sizeof(vector));
    new->length = 0;
    new->size = 128;
    new->items = malloc(VEC_ALLOC_SIZE * sizeof(int));

    return new;
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
    if (i < 0 || i > v->length)
        return 0;
    else
    {
        v->items[i] = val;
        return 1;
    }
}

void vector_push(vector *v, int32_t val)
{
    if (v->length + 1 >= v->size)
    {
        // Reallocate memory
        v->items = realloc(v->items, (v->size + VEC_ALLOC_SIZE) * sizeof(int32_t));
    }
    v->items[v->length++] = val;
}
