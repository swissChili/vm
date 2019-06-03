#include <stdlib.h>
#include "vector.h"


vector *new_vector()
{
    vector *new = (vector *)malloc(sizeof(vector));
    new->length = 0;
    new->size = 128;
    new->items = (int *)malloc(VEC_ALLOC_SIZE * sizeof(int));

    return new;
}

void free_vector(vector *v)
{
    free(v->items);
    free(v);
}

int vector_at(vector *v, int i, int *ret)
{
    if (i < 0 || i > v->length)
        return 0;
    else
    {
        *ret = v->items[i];
        return 1;
    }
}

int vector_set(vector *v, int i, int val)
{
    if (i < 0, i > v->length)
        return 0;
    else
    {
        v->items[i] = val;
        return 1;
    }
}

void vector_push(vector *v, int val)
{
    if (v->length + 1 >= v->size)
    {
        // Reallocate memory
        v->items = realloc(v->items, (v->size + VEC_ALLOC_SIZE) * sizeof(int));
    }
    v->items[v->length++] = val;
}
