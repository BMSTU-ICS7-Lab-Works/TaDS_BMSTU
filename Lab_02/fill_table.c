#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int fill_str(char *tstring, char *string, int *start)
{
    int i, j;
    for (i = *start, j = 0; string[i] != ';'; i++, j++)
        tstring[j] = string[i];
    tstring[j] = '\0';
    *start = i + 1;
    return 0;
}

int fill_num(int *num, char *string, int *start, int param)
{
    int res = 0, i;
    if (param == 1)
    {
        for (i = *start; i < strlen(string) - 1; i++)
        {
            if (i == *start)
                res = string[i] - '0';
            else
                res = res * 10 + string[i] - '0';
        }
        if (string[strlen(string) - 1] <= '9' && string[strlen(string) - 1] >= '0')
            res = res * 10 + string[strlen(string) - 1] - '0';
        *num = res;
        return 0;
    }
    for (i = *start; string[i] != ';'; i++)
    {
        if (i == *start)
            res = string[i] - '0';
        else
            res = res * 10 + string[i] - '0';
    }
    *start = i + 1;
    *num = res;
    return 0;
}

int fill_table(cars *table, key *table_keys)
{
    int count = 0;
    int start = 0;
    FILE *f = fopen("F:/TiSD 2qrs/Lab_02/table.txt", "r+");
    rewind(f);
    while (1)
    {
        char string[300] = "";
        if (fgets(string, 300, f) == NULL)
            break;
        start = 0;   
        fill_str(table[count].mark, string, &start);
        fill_str(table[count].country, string, &start);
        fill_num(&table[count].price, string, &start, 0);
        //keys fill
        table_keys[count].index = count;
        table_keys[count].price = table[count].price;
        fill_str(table[count].colour, string, &start);
        fill_str(table[count].condition, string, &start);
        if (strcmp(table[count].condition, "new") == 0)
            fill_num(&table[count].type.new1.warranty, string, &start, 1);
        if (strcmp(table[count].condition, "not new") == 0)
        {
            fill_num(&table[count].type.not_new1.date, string, &start, 0);
            fill_num(&table[count].type.not_new1.mileage, string, &start, 0);
            fill_num(&table[count].type.not_new1.num_repairs, string, &start, 0);
            fill_num(&table[count].type.not_new1.num_owners, string, &start, 1);
        }
        count++;
    }
    fclose(f);
    return count;
}
