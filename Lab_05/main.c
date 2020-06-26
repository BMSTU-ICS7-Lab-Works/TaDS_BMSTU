#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"

void print_interface(void)
{
    puts("******************************");
    puts("Select menu item: ");
    puts("0: Work, using queue array");
    puts("1: Work, using queue list");
    puts("2: Show memory fragmentation");
    printf("Your choice: ");

}

int main()
{
    srand(time(NULL ));
    queue_t *q1;
    queue_t *q2;
    q1 = (queue_t*)malloc(sizeof(queue_t*));
    q2 = (queue_t*)malloc(sizeof(queue_t*));
    int countq1 = 0, countq2 = 0;
    mas_t *m1;
    mas_t *m2;
    m1 = (mas_t*)malloc(sizeof(mas_t));
    m2 = (mas_t*)malloc(sizeof(mas_t));
    int countm1 = 0, countm2 = 0;
    int choice;
    while (1)
    {
        print_interface();
        scanf("%d", &choice);
        switch (choice)
        {

            case 0:
            {
                m1 = (mas_t*)malloc(sizeof(mas_t));
                m2 = (mas_t*)malloc(sizeof(mas_t));
                masservice(q1, q2, &countq1, &countq2, 1, m1, m2, &countm1, &countm2);
                free(m1);
                free(m2);
                countm1 = 0;
                countm2 = 0;
                break;
            }
            case 1:
            {
            /*
                printf("\nSHOW FREE ADDRESSES?\n");
                printf("1.YES\n2.NO\nYOUR CHOICE: ");
                scanf("%d", &choicefree);
                */
                masservice(q1, q2, &countq1, &countq2, 0, m1, m2, &countm1, &countm2);
                /*
                if (choicefree == 1)
                {
                    printf("\nFREED ADDRESSES OF FIRST QUEUE\n");
                    for (int i = 0; i < countq1; i++)
                    {
                        printf("%p\n", q1->frnt);
                        remove_elem(q1);
                    }
                    printf("\nFREED ADDRESSES OF SECOND QUEUE\n");
                    for (int j = 0; j < countq2; j++)
                    {
                        printf("%p\n", q2->frnt);
                        remove_elem(q2);
                    }
                }
                else
                {
                    for (int i = 0; i < countq1; i++)
                    {
                        remove_elem(q1);
                    }
                    for (int j = 0; j < countq2; j++)
                    {
                        remove_elem(q2);
                    }
                }
                */
                countq1 = 0;
                countq2 = 0;
                break;
            }
            case 2:
            {
                int count = 0;
                printf("STEP 1: ADD 10 ELEMENTS AND DELETE ELEMENTS\n");
                printf("SHOWING FREE ADDRESSES...\n");
                queue_t *q;
                q = (queue_t*)malloc(sizeof(queue_t*));
                q->rear = init(float_rand(T1_MIN, T1_MAX));
                q->frnt = q->rear;
                for (int i = 0; i < 9; i++)
                    insert(q, float_rand(T1_MIN, T1_MAX));
                for (int i = 0; i < 10; i++)
                {
                    printf("%p\n", q->frnt);
                    remove_elem(q);
                }
                printf("STEP 2: ADD 10 ELEMENTS AND SHOW FREE ADDRESSES");
                q->rear = init(float_rand(T1_MIN, T1_MAX));
                q->frnt = q->rear;
                for (int i = 0; i < 9; i++)
                    insert(q, float_rand(T1_MIN, T1_MAX));
                if (count == 0)
                {
                    puts("\nNULL");
                    printf("Everything is OK\n");
                }
                for (int i = 0; i < 10; i++)
                    remove_elem(q);
                break;
            }

        }
    }
    free(m1);
    free(m2);
    return CORR_END;
}
