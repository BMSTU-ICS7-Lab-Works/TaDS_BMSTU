#include "main.h"
#include <stdio.h>
#include <string.h>

int check_str(char str[])
{
    for (int i = 0; i < strlen(str); i++)
    {
        if ((str[i] <= 'Z' && str[i] >= 'A') || (str[i] <= 'z' && str[i] >= 'a') || str[i] == '_' || str[i] == '-')
            continue;
        else
            return ERR_INP;
    }
    return CORR_END;
}

int search_notes(int field, cars *table, int amount, char str[], int ignoreind[], int num)
{
    int k = 0;
    for (int i = 0; i < amount; i++)
    {
        switch (field)
        {
            case 1:
            if (strcmp(table[i].mark, str) == 0)
                {
                    ignoreind[k] = i;
                    k++;
                }
            break;
            case 2:
                if (strcmp(table[i].country, str) == 0)
                {
                    ignoreind[k] = i;
                    k++;
                }
            break;
            case 3:
                if (table[i].price == num)
                {
                    ignoreind[k] = i;
                    k++;
                }
            break;
            case 4:
                if (strcmp(table[i].colour, str) == 0)
                {
                    ignoreind[k] = i;
                    k++;
                }
            break;
            case 5:
                if (strcmp(table[i].condition, str) == 0)
                {
                    ignoreind[k] = i;
                    k++;
                }
            break;
            case 6:
            if (strcmp(table[i].condition, "new") == 0)
            {
                if (table[i].type.new1.warranty == num)
                {
                    ignoreind[k] = i;
                    k++;
                }
            }
            break;
            case 7:
            if (strcmp(table[i].condition, "not new") == 0)
            {
                if (table[i].type.not_new1.date == num)
                {
                    ignoreind[k] = i;
                    k++;
                }
            }
            break;
            case 8:
            if (strcmp(table[i].condition, "not new") == 0)
            {
                if (table[i].type.not_new1.mileage == num)
                {
                    ignoreind[k] = i;
                    k++;
                }
            }
            break;
            case 9:
            if (strcmp(table[i].condition, "not new") == 0)
            {
                if (table[i].type.not_new1.num_repairs == num)
                {
                    ignoreind[k] = i;
                    k++;
                }
            }
            break;
            case 10:
            if (strcmp(table[i].condition, "not new") == 0)
            {
                if (table[i].type.not_new1.num_owners == num)
                {
                    ignoreind[k] = i;
                    k++;
                }
            }
            break;
        }
    }
    return k;
}

int delete_note(int *amount, cars *table)
{
    FILE *f = fopen("table.txt", "r+");
    printf("\n\t\tCHOOSE FIELD TO DELETE CAR(S)\n\n"
           "press 1 to delete by the marks field\n"
           "press 2 to delete by the country field\n"
           "press 3 to delete by the price field\n"
           "press 4 to delete by the colour field\n"
           "press 5 to delete by the state field\n"
           "press 6 to delete by the warranty\n"
           "press 7 to delete by the year of manufacture\n"
           "press 8 to delete by the mileage\n"
           "press 9 to delete by the number of repairs\n"
           "press 10 to delete by the number of owners\n");
    int s;
    float s1;
    printf("YOUR CHOICE: ");
    if (!scanf("%f", &s1))
    {
        printf("Input error\n");
        fflush(stdin);
        return ERR_INP;
    }
    s = s1;
    if (s != s1)
    {
        printf("Input error\n");
        fflush(stdin);
        return ERR_INP;
    }
    int ignoreind[200];
    char string[300];
    int num;
    float num1;
    int ignorenum;
    fflush(stdin);
    switch (s)
    {
        case 1:
            printf("Enter mark of the car(s)cars you want to delete: ");
            if (strlen(gets(string)) == 0)
            {
                printf("Input error\n");
                fflush(stdin);
                return ERR_INP;
            }
            if (check_str(string) == 0)
                ignorenum = search_notes(1, table, *amount, string, ignoreind, 0);
            else
            {
                printf("Input error\n");
                fflush(stdin);
                return ERR_INP;
            }
            fflush(stdin);
            break;
        case 2:
            printf("Enter country of the car(s) you want to delete: ");
            if (strlen(gets(string)) == 0)
            {
                printf("Input error\n");
                fflush(stdin);
                return ERR_INP;
            }
            if (check_str(string) == 0)
                ignorenum = search_notes(2, table, *amount, string, ignoreind, 0);
            else
            {
                printf("Input error\n");
                fflush(stdin);
                return ERR_INP;
            }
            fflush(stdin);
            break;
        case 3:
            printf("Enter price of the car(s) you want to delete: ");
            if (!scanf("%f", &num1))
            {
                printf("Input error\n");
                return ERR_INP;
            }
            num = num1;
            if (num != num1 || num <= 0)
            {
                printf("Input error\n");
                return ERR_INP;
            }
            ignorenum = search_notes(3, table, *amount, string, ignoreind, num);
            break;
        case 4:
            printf("Enter colour of the car(s) you want to delete: ");
            if (strlen(gets(string)) == 0)
            {
                printf("Input error\n");
                fflush(stdin);
                return ERR_INP;
            }
            if (check_str(string) == 0)
                ignorenum = search_notes(4, table, *amount, string, ignoreind, 0);
            else
            {
                printf("Input error\n");
                fflush(stdin);
                return ERR_INP;
            }
            fflush(stdin);
            break;
        case 5:
            printf("Enter state of the car(s) you want to delete: ");
            if (strlen(gets(string)) == 0)
            {
                printf("Input error\n");
                fflush(stdin);
                return ERR_INP;
            }
            if (check_str(string) == 0)
                ignorenum = search_notes(5, table, *amount, string, ignoreind, 0);
            else
            {
                printf("Input error\n");
                fflush(stdin);
                return ERR_INP;
            }
            fflush(stdin);
            break;
        case 6:
            printf("Enter warranty of the car(s) you want to delete: ");
            if (!scanf("%f", &num1))
            {
                printf("Input error\n");
                return ERR_INP;
            }
            num = num1;
            if (num != num1 || num < 0)
            {
                printf("Input error\n");
                return ERR_INP;
            }
            ignorenum = search_notes(6, table, *amount, string, ignoreind, num);
            break;
        case 7:
            printf("Enter year of manufacture of the car(s) you want to delete: ");
            if (!scanf("%f", &num1))
            {
                printf("Input error\n");
                return ERR_INP;
            }
            num = num1;
            if (num != num1 || num <= 0)
            {
                printf("Input error\n");
                return ERR_INP;
            }
            ignorenum = search_notes(7, table, *amount, string, ignoreind, num);
            break;
        case 8:
            printf("Enter mileage of the car(s) you want to delete: ");
            if (!scanf("%f", &num1))
            {
                printf("Input error\n");
                return ERR_INP;
            }
            num = num1;
            if (num != num1 || num < 0)
            {
                printf("Input error\n");
                return ERR_INP;
            }
            ignorenum = search_notes(8, table, *amount, string, ignoreind, num);
            break;
        case 9:
            printf("Enter number of repairs of the car(s) you want to delete: ");
            if (!scanf("%f", &num1))
            {
                printf("Input error\n");
                return ERR_INP;
            }
            num = num1;
            if (num != num1 || num < 0)
            {
                printf("Input error\n");
                return ERR_INP;
            }
            ignorenum = search_notes(9, table, *amount, string, ignoreind, num);
            break;
        case 10:
            printf("Enter number of owners of the car(s) you want to delete: ");
            if (!scanf("%f", &num1))
            {
                printf("Input error\n");
                return ERR_INP;
            }
            num = num1;
            if (num != num1 || num <= 0)
            {
                printf("Input error\n");
                return ERR_INP;
            }
            ignorenum = search_notes(10, table, *amount, string, ignoreind, num);
            break;
        default:
            printf("ERR input");
            return ERR_INP;
    }
    fflush(stdin);
    if (f)
    {
        char string[300];
        fseek(f, 0, SEEK_END);
        char tabledata[100*300] = "";
        char *ptr = tabledata;
        fseek(f, 0, SEEK_SET);
        int i = 0;
        int flag = 0;
        while (fgets(string, 300, f))
        {
            flag = 0;
            for (int l = 0; l < ignorenum; l++)
            {
                if (i == ignoreind[l])
                {
                    (*amount)--;
                    printf("This is a string you want to delete: ");
                    puts(string);
                    flag = 1;
                    break;
                }
            }
            i++;
            if (flag == 0)
            {
                strcat(ptr, string);
                ptr += strlen(string);
            }
        }
        fclose(f);
        f = fopen("table.txt", "w");
        fputs(tabledata, f);
        fclose(f);
    }
    return CORR_END;
}
