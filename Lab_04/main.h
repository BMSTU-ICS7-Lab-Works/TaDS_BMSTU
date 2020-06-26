#ifndef MAIN_H
#define MAIN_H

#define STACK_MAX_SIZE 100000
#define CORR_END 1
#define STACK_OVERFLOW -1
#define STACK_UNDERFLOW -2
#define ERR_INPUT -3

typedef struct stack_array
{
    int address[STACK_MAX_SIZE];
    int size;
} stack_arr_t;

typedef struct stack_list
{
    int address;
    struct stack_list *next;
} stack_list_t;

typedef struct deleted_memory
{
    void *p;
    struct deleted_memory *next;
}del_mem;

int push_arr(stack_arr_t *stack, const int value);
int pop_arr(stack_arr_t *stack);
int peek_arr(const stack_arr_t *stack);
void print_stack_arr(const stack_arr_t *stack);
void print_stack_list(const stack_list_t* head);
int pop_list(stack_list_t **head, del_mem **adress);
int push_list(stack_list_t **head, del_mem **adress);
void pop_mem(del_mem **head);
void push_mem(del_mem **list, void *p);
void print_del_mem(const del_mem* head);
int push_list_comp(stack_list_t **head);
int pop_list_comp(stack_list_t **head);
void compare();
void calculate_eff(int , int);

#endif // MAIN_H
