#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"


node *new_node(int value) {
    node *ret = (node *) malloc(sizeof(node));
    ret->value = value;
    ret->prev = NULL;
    ret->next = NULL;
    return ret;
}

void free_node(node *n)
{
    free(n);
}

stack *new_stack()
{
    stack *ret = (stack *) malloc(sizeof(stack));
    ret->first = NULL;
    ret->last = NULL;
    ret->length = 0;
    return ret;
}

void free_stack(stack *s)
{
    if (s->length == 0)
    {
        free(s);
        return;
    }
    node *current = s->first;
    for (int i = 0; i < s->length; i++)
    {
        node *next = current->next;
        free_node(current);
        current = next;
    }
}

void stack_push(stack *s, int value)
{
    node *new = new_node(value);
    if (s->length > 0)
    {
        new->prev = s->last;
        s->last->next = new;
    } else {
        s->first = new;
    }
    s->length++;
    s->last = new;
}

int stack_pop(stack *s)
{
    if (s->length == 0)
        return 0;
    int last = s->last->value;
    node *new_last = s->last->prev;
    free_node(s->last);
    s->length--;
    s->last = new_last;
    return last;
}

void stack_print(stack *s)
{
    if (s->length == 0)
        printf("[ ]\n");
    else
    {
        printf("[");
        node *current = s->first;
        for (int i = 0; i < s->length; ++i)
        {
            printf(" %d", current->value);
            current = current->next;
        }
        printf(" ]\n");
    }
}
