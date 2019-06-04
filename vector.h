#ifndef VM_VECTOR_H
#define VM_VECTOR_H

#define VEC_ALLOC_SIZE 256


struct vector
{
    int length;
    int size;
    int *items;
};

typedef struct vector vector;

vector *new_vector();
void free_vector(vector *);
// Returns 0 on error, 1 otherwise.
int vector_at(vector *, int, int *);
int vector_set(vector *, int, int);
void vector_push(vector *, int);


#endif
