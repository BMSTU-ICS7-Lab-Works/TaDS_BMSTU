#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int main()
{
    puts("The program shows how to work with stack.");
    int choice;
    float flag1 = -1;
    int flag = -1;
    puts("First choose you want to work with array or list");
    puts("0: Array_type stack");
    puts("1: List_type stacck");
    printf("\nMake your choice: ");
    if (!scanf("%f", &flag1))
    {
        printf("WRONG INPUT");
        return ERR_INPUT;
    }
    flag = flag1;
    if (flag != 0 && flag != 1)
    {
        if (flag1 - flag == 0)
        {
            printf("WRONG INPUT");
            return ERR_INPUT;
        }
    }
    //int countarr = 0;
    //int countlist = 0;
    //del_mem *address_list = NULL;
    stack_arr_t stack_arr;
    stack_arr.size = 0;
    stack_list_t *head = NULL;
    del_mem *address=NULL;
    while(1)
    {
        puts("\nMENU:");
        puts("0: Push stack");
        puts("1: Pop stack");
        puts("2: Print stack");
        puts("3: Show freed addresses");
        puts("Other actions:");
        puts("4: Compare Array and list stack efficiency");
        puts("5: Switch to Array_type stack");
        puts("6: Switch to List_type stack");
        puts("7: Exit");
        printf("Your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
            case 0:
            {
                puts("NOTE: max stack size allowed is 1000000");
                if (flag == 0)
                {
                    float inpaddress1;
                    int inpaddress;
                    printf("\nInput memory address: ");
                    if (!scanf("%f", &inpaddress1))
                    {
                        printf("WRONG INPUT\n");
                        break;
                    }
                    inpaddress = inpaddress1;
                    if (inpaddress - inpaddress1 != 0 || inpaddress < 1)
                    {
                        printf("WRONG INPUT\n");
                        break;
                    }
                    if (push_arr(&stack_arr, inpaddress) == 1)
                        puts("Successfully added element");
                }
                else
                {
                    if (push_list(&head, &address) > -1)
                        puts("Successfully added element");
                }
                break;
            }
            case 1:
            {
                if (flag == 0)
                {
                    if (pop_arr(&stack_arr) > -1)
                        puts("Successfully popped element");
                }
                else
                {
                    if (pop_list(&head, &address) > -1)
                        puts("Successfully popped element");
                }
                break;
            }
            case 2:
                if (flag == 0)
                {
                    print_stack_arr(&stack_arr);
                    puts("");
                }
                else
                {
                    print_stack_list(head);
                    puts("");
                }
                break;
            case 3:
                if (flag == 0)
                    puts("This function is only for list_type stack!");
                else
                {
                    print_del_mem(address);
                    continue;
                }
                break;
            case 4:
                compare();
                break;
            case 5:
                if (flag == 1)
                {
                    flag = 0;
                    puts("Successfully switched to array_type stack");
                }
                else
                    puts("You are already working with array_type stack!");
                break;
            case 6:
                if (flag == 0)
                {
                    flag = 1;
                    puts("Successfully switched to list_type stack");
                }
                else
                    puts("You are already working with list_type stack!");
                break;
            //to add switching here
            case 7:
                printf("Exit...");
                return CORR_END;
            default:
                puts("WRONG INPUT");
                break;
        }
    }
    return CORR_END;
}
