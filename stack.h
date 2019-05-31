#ifndef VM_STACK_H
#define VM_STACK_H


struct node {
    int value;
    struct node *next;
    struct node *prev;
};
typedef struct node node;

node *new_node(int);
void free_node(node*);


struct stack {
    node *first;
    node *last;
    int length;
};
typedef struct stack stack;

stack *new_stack();
void free_stack(stack*);
void stack_push(stack*, int);
int stack_pop(stack*);
void stack_print(stack*);


#endif
