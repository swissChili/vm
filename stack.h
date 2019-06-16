#ifndef VM_STACK_H
#define VM_STACK_H


#include <stdint.h>

struct node {
    int32_t value;
    struct node *next;
    struct node *prev;
};
typedef struct node node;

node *new_node(int32_t);
void free_node(node*);


struct stack {
    node *first;
    node *last;
    uint64_t length;
};
typedef struct stack stack;

stack *new_stack();
void free_stack(stack*);
void stack_push(stack*, int32_t);
int32_t stack_pop(stack*);
void stack_print(stack*);


#endif
