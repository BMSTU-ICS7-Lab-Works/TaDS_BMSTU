#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include <string.h>

#define CORR_END 0
#define ERR_INP -1
#define MAX_SIZE 100

int main()
{
    int count = 0;
    int lrng, rrng;
    char mark[20];
    float lrng1, rrng1;
    cars table_cars[MAX_SIZE];
    key table_keys[MAX_SIZE];
    count = fill_table(table_cars, table_keys);
    printf("This program works with table, containing information about 40 or more cars in the autoshop.\n"
           "It has information about its:\nmarks (string);\ncountry (string);\nprice (int);"
           "\ncolor (string);\nstate (string)"
           "\nif car is new here is information about it warranty in years (int);\n"
           "if car is not new, the table shows the year of manufacture (int), its mileage (int), number\n"
           "of repairs (int) and number of owners (int).\n\n");
    while (1)
    {
        printf("\t\tLIST OF TASKS\n\n"
               "press 1 to show the table\n"
               "press 2 to add new car\n"
               "press 3 to delete car(s) by chosen field\n"
               "press 4 to show sorted key table\n"
               "press 5 to show sorted table\n"
               "press 6 to show sorted by the key table\n"
               "press 7 to show efficiency of different sorts\n"
               "press 8 to show prices of not new cars with chosen mark, one previous owner,\n"
               " without repairs and in written value range\n"
               "press 9 to close the program\n\n");
        int s;
        float s1;
        printf("YOUR CHOICE: ");
        if (!scanf("%f", &s1))
        {
            printf("Input error\n");
            return ERR_INP;
        }
        s = s1;
        if (s != s1)
        {
            printf("Input error\n");
            return ERR_INP;
        }
        switch (s)
        {
        case 1:
            count = fill_table(table_cars, table_keys);
            show_table(table_cars, count, table_keys, 0);
            break;
        case 2:
            if (count > 99)
                printf("Too much notes already (needs to be less than 100)\n");
            else
            {
                //cars table_cars[MAX_SIZE];
                //key table_keys[MAX_SIZE];
                add_note(table_cars, &count);
                count = fill_table(table_cars, table_keys);
                show_table(table_cars, count, table_keys, 0);            
            }
            break;
        case 3:
            if (delete_note(&count, table_cars) == 0)
            {            
                count = fill_table(table_cars, table_keys);
                show_table(table_cars, count, table_keys, 0);
            }
            fflush(stdin);
            break;
        case 4:
            sortkey(table_keys, 0, count);
            show_keys(table_keys, count);
            break;
        case 5:
            sortcars(table_cars, 1, count);
            sortkey(table_keys, 1, count);
            show_table(table_cars, count, table_keys, 0);
            break;
        case 6:
            count = fill_table(table_cars, table_keys);
            sortkey(table_keys, 1, count);
            show_table(table_cars, count, table_keys, 1);
            break;
        case 7:
            check_efficiency(table_cars, table_keys, count);
            break;
        case 8:
            fflush(stdin);
            printf("Enter mark of a car: ");
            if (gets(mark))
            {
                if (check_str(mark) == 0)
                {
                    printf("Enter left end of range: ");
                    if (!scanf("%f", &lrng1))
                    {
                        printf("Input error\n");
                        break;
                    }
                    lrng = lrng1;
                    if (lrng != lrng1 || lrng < 0)
                    {
                        printf("Input error\n");
                        break;
                    }
                    printf("Enter right end of range: ");
                    if (!scanf("%f", &rrng1))
                    {
                        printf("Input error\n");
                        break;
                    }
                    rrng = rrng1;
                    if (rrng != rrng1 || rrng < lrng)
                    {
                        printf("Input error\n");
                        break;
                    }
                    show_task(table_cars, count, mark, lrng, rrng);
                }
                else
                {
                    printf("Input error\n");
                    fflush(stdin);
                    break;
                }
            }
            fflush(stdin);
            break;
        case 9:
            printf("Exit...");
            return CORR_END;
        default:
            printf("ERR input");
            return ERR_INP;
        }
    }
    return CORR_END;
}
