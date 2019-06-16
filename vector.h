#ifndef VM_VECTOR_H
#define VM_VECTOR_H

#include <stdint.h>
#define VEC_ALLOC_SIZE 256


struct vector
{
    uint64_t length;
    uint64_t size;
    int32_t *items;
};

typedef struct vector vector;

vector *new_vector();
void free_vector(vector *);
// Returns 0 on error, 1 otherwise.
int vector_at(vector *, uint64_t, int32_t *);
int vector_set(vector *, uint64_t, int32_t);
void vector_push(vector *, int32_t);


#endif
