#include <stdio.h>
#include <stdlib.h>
#include "main.h"


void push_mem(del_mem **list, void *p)
{
    del_mem *node = malloc(sizeof(stack_list_t));
    node->p = p;
    node->next = *list;
    *list = node;
}

void pop_mem(del_mem **head)
{
    del_mem *out;
    if (*head != NULL)
    {
        out = *head;
        *head = (*head)->next;
        free(out);
    }
}

int push_list(stack_list_t **head, del_mem **address)
{
    stack_list_t *tmp = malloc(sizeof(stack_list_t));
    if (tmp == NULL)
    {
        puts("STACK OVERFLOW!");
        return STACK_OVERFLOW;
    }
    tmp->next = *head;
    tmp->address = 1;
    pop_mem(address);
    *head = tmp;
    return CORR_END;
}


int pop_list(stack_list_t **head, del_mem **address)
{
    stack_list_t *out;
    if ((*head) == NULL)
    {
        puts("STACK UNDERFLOW!");
        return STACK_UNDERFLOW;
    }
    out = *head;
    push_mem(address, &out->address);
    *head = (*head)->next;
    free(out);
    return CORR_END;
}


void print_stack_list(const stack_list_t* head)
{
    printf("stack >");
    while (head)
    {
        printf("\t%p\n", &head->address);
        head = head->next;
    }
}

void print_del_mem(const del_mem* head)
{
    printf("FREED ADDRESSES -->\n");
    if (head == NULL)
        printf("NO ADDRESSES WERE FREED YET");
    puts("");
    while (head)
    {
        printf("\t%p\n", head->p);
        head = head->next;
    }
}

int push_list_comp(stack_list_t **head)
{
    stack_list_t *tmp = malloc(sizeof(stack_list_t));
    if (tmp == NULL)
    {
        puts("STACK OVERFLOW!");
        return STACK_OVERFLOW;
    }
    tmp->next = *head;
    tmp->address = 1;
    *head = tmp;
    return CORR_END;
}


int pop_list_comp(stack_list_t **head)
{
    stack_list_t *out;
    if ((*head) == NULL)
    {
        puts("STACK UNDERFLOW!");
        return STACK_UNDERFLOW;
    }
    out = *head;
    *head = (*head)->next;
    free(out);
    return CORR_END;
}
