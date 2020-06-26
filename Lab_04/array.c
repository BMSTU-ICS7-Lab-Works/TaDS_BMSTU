#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int push_arr(stack_arr_t *stack, const int value)
{
    if (stack->size >= STACK_MAX_SIZE)
    {
        puts("STACK OVERFLOW!");
        return STACK_OVERFLOW;
    }
    stack->address[stack->size] = value;
    stack->size++;
    return CORR_END;
}


int pop_arr(stack_arr_t *stack)
{
    if (stack->size == 0)
    {
        puts("STACK UNDERFLOW!");
        return STACK_UNDERFLOW;
    }
    stack->size--;
    return stack->address[stack->size];
}

int peek_arr(const stack_arr_t *stack)
{
    if (stack->size <= 0)
    {
        puts("STACK UNDERFLOW!");
        return STACK_UNDERFLOW;
    }
    return stack->address[stack->size - 1];
}

void print_stack_arr(const stack_arr_t *stack)
{
    int i;
    int len = stack->size - 1;
    printf("stack %d --> \n", stack->size);
    for (i = len; i > 0; i--)
    {
        printf("\t   %d|\n", stack->address[i]);
    }
    if (stack->size != 0)
    {
        printf("\t   %d|", stack->address[i]);
    }
    printf("\n");
}
