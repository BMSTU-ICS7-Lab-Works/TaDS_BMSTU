#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

//this func need to check not empty input at gets
int add_note(cars *table, int *count)
{
    char string[15] = "";
    int num = 0;
    float num1 = 0;
    FILE *f = fopen("table.txt", "r+");
    fflush(stdin);
    printf("(recommends less than 13 syms )Enter car model: ");
    if (strlen(gets(string)) == 0)
    {
        printf("Input error\n");
        fflush(stdin);
        return ERR_INP;
    }
    fflush(stdin);
    if (check_str(string) == 0)
        strcpy(table[*count + 1].mark, string);
    else
    {
        printf("Input error\n");
        fflush(stdin);
        return ERR_INP;
    }
    printf("(recommends less than 17 syms )Enter country of origin: ");
    if (strlen(gets(string)) == 0)
    {
        printf("Input error\n");
        fflush(stdin);
        return ERR_INP;
    }
    fflush(stdin);
    if (check_str(string) == 0)
        strcpy(table[*count + 1].country, string);
    else
    {
        printf("Input error\n");
        fflush(stdin);
        return ERR_INP;
    }
    printf("(recommends less than 11 nums )Enter price of a car: ");
    if (!scanf("%f", &num1))
    {
        printf("Input error\n");
        fflush(stdin);
        return ERR_INP;
    }
    num = num1;
    if (num != num1 || num < 0)
    {
        printf("Input error\n");
        fflush(stdin);
        return ERR_INP;
    }
    table[*count + 1].price = num;
    fflush(stdin);
    printf("(recommends less than 10 syms )Enter car colour: ");
    if (strlen(gets(string)) == 0)
    {
        printf("Input error\n");
        fflush(stdin);
        return ERR_INP;
    }
    fflush(stdin);
    if (check_str(string) == 0)
        strcpy(table[*count + 1].colour, string);
    else
    {
        printf("Input error\n");
        fflush(stdin);
        return ERR_INP;
    }
    printf("Warning!!! Only 'new' and 'not new' written in car condition is acceptable\n");
    printf("Enter car condition: ");
    gets(string);
    fflush(stdin);
    while (strcmp(string, "new") != 0 && strcmp(string, "not new") != 0)
    {
        printf("Try again!\n");
        printf("Enter car condition: ");
        gets(string);
        fflush(stdin);
    }
    strcpy(table[*count + 1].condition, string);
    if (strcmp(table[*count + 1].condition, "new") == 0)
    {
        printf("(recommends less than 10 nums)Enter warranty of the car: ");
        if (!scanf("%f", &num1))
        {
            printf("Input error\n");
            fflush(stdin);
            return ERR_INP;
        }
        num = num1;
        if (num != num1 || num < 0)
        {
            printf("Input error\n");
            fflush(stdin);
            return ERR_INP;
        }
        table[*count + 1].type.new1.warranty = num;
    }
    else
    {
        printf("(recommends less than 19 nums)Enter year of the manufacture: ");
        if (!scanf("%f", &num1))
        {
            printf("Input error\n");
            fflush(stdin);
            return ERR_INP;
        }
        num = num1;
        if (num != num1 || num <= 0)
        {
            printf("Input error\n");
            fflush(stdin);
            return ERR_INP;
        }
        table[*count + 1].type.not_new1.date = num;
        printf("(recommends less than 9 nums)Enter mileage of the car: ");
        if (!scanf("%f", &num1))
        {
            printf("Input error\n");
            fflush(stdin);
            return ERR_INP;
        }
        num = num1;
        if (num != num1 || num < 0)
        {
            printf("Input error\n");
            fflush(stdin);
            return ERR_INP;
        }
        table[*count + 1].type.not_new1.mileage = num;
        printf("(recommends less than 17 nums)Enter number of repairs: ");
        if (!scanf("%f", &num1))
        {
            printf("Input error\n");
            fflush(stdin);
            return ERR_INP;
        }
        num = num1;
        if (num != num1 || num < 0)
        {
            printf("Input error\n");
            fflush(stdin);
            return ERR_INP;
        }
        table[*count + 1].type.not_new1.num_repairs = num;
        printf("(recommends less than 16 nums)Enter number of owners: ");
        if (!scanf("%f", &num1))
        {
            printf("Input error\n");
            fflush(stdin);
            return ERR_INP;
        }
        num = num1;
        if (num != num1 || num <= 0)
        {
            printf("Input error\n");
            fflush(stdin);
            return ERR_INP;
        }
        table[*count + 1].type.not_new1.num_owners = num;
    }
    fseek(f, 0, SEEK_END);
    fprintf(f, "\n%s;%s;%d;%s;%s;", table[*count + 1].mark,
            table[*count + 1].country, table[*count + 1].price,
            table[*count + 1].colour, table[*count + 1].condition);
    if (strcmp(table[*count + 1].condition, "new") == 0)
    {
        fprintf(f, "%d", table[*count + 1].type.new1.warranty);
    }
    else
    {
        fprintf(f, "%d;%d;%d;%d", table[*count + 1].type.not_new1.date,
                table[*count + 1].type.not_new1.mileage, table[*count + 1].type.not_new1.num_repairs,
                table[*count + 1].type.not_new1.num_owners);
    }
    *count += 1;
    fclose(f);
    return 0;
}
