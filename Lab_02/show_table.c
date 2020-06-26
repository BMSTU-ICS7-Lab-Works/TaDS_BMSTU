#include "main.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void show_table(cars *table_cars, int amount, key *table_keys, int param)
{
    printf("\nTOTAL NUM OF CARS: %d\n\n", amount);
    printf(" |    MODEL    |COUNTRY OF ORIGIN|   PRICE   |  COLOUR  | CONDITION | WARRANTY |"
           "YEAR OF MANUFACTURE| MILEAGE |NUMBER OF REPAIRS|NUMBER OF OWNERS|");
    printf("\n --------------|-----------------|-----------|----------|-----------|----------|"
           "-------------------|---------|-----------------|----------------|\n");
    if (param == 0)
    {
        for (int i = 0; i < amount; i++)
        {
            printf("%2d%13s|%17s|%11d|%10s|%11s|", i + 1,table_cars[i].mark, table_cars[i].country,
                   table_cars[i].price, table_cars[i].colour, table_cars[i].condition);
            if (strcmp(table_cars[i].condition, "new") == 0)
            {
                printf("%10d|-------------------|---------|-----------------|"
                       "----------------|\n", table_cars[i].type.new1.warranty);
            }
            else
            {
                printf("----------|%19d|%9d|%17d|%16d|\n", table_cars[i].type.not_new1.date,
                       table_cars[i].type.not_new1.mileage, table_cars[i].type.not_new1.num_repairs,
                       table_cars[i].type.not_new1.num_owners);
            }
        }
    }
    else
    {        
        for (int i = 0; i < amount; i++)
        {
            printf("%2d%13s|%17s|%11d|%10s|%11s|", i + 1,table_cars[table_keys[i].index].mark, table_cars[table_keys[i].index].country,
                   table_cars[table_keys[i].index].price, table_cars[table_keys[i].index].colour, table_cars[table_keys[i].index].condition);
            if (strcmp(table_cars[table_keys[i].index].condition, "new") == 0)
            {
                printf("%10d|-------------------|---------|-----------------|"
                       "----------------|\n", table_cars[table_keys[i].index].type.new1.warranty);
            }
            else
            {
                printf("----------|%19d|%9d|%17d|%16d|\n", table_cars[table_keys[i].index].type.not_new1.date,
                       table_cars[table_keys[i].index].type.not_new1.mileage, table_cars[table_keys[i].index].type.not_new1.num_repairs,
                       table_cars[table_keys[i].index].type.not_new1.num_owners);
            }
        }
    }
    printf("-------------------------------------------------------------------------------"
           "-----------------------------------------------------------------\n\n");
}

void show_task(cars *table_cars, int amount, char* mark, int lrng, int rrng)
{
    printf(" |    MODEL    |COUNTRY OF ORIGIN|   PRICE   |  COLOUR  | CONDITION | WARRANTY |"
           "YEAR OF MANUFACTURE| MILEAGE |NUMBER OF REPAIRS|NUMBER OF OWNERS|");
    printf("\n --------------|-----------------|-----------|----------|-----------|----------|"
           "-------------------|---------|-----------------|----------------|\n");
    for (int i = 0; i < amount; i++)
    {
        if (strcmp(table_cars[i].mark, mark) == 0 && strcmp(table_cars[i].condition, "not new") == 0 &&
                table_cars[i].type.not_new1.num_owners == 1 && table_cars[i].type.not_new1.num_repairs == 0 &&
                table_cars[i].price <= rrng && table_cars[i].price >= lrng)
        {
            printf("%2d%13s|%17s|%11d|%10s|%11s|", i + 1,table_cars[i].mark, table_cars[i].country,
                   table_cars[i].price, table_cars[i].colour, table_cars[i].condition);
            printf("----------|%19d|%9d|%17d|%16d|\n", table_cars[i].type.not_new1.date,
                   table_cars[i].type.not_new1.mileage, table_cars[i].type.not_new1.num_repairs,
                   table_cars[i].type.not_new1.num_owners);
        }
    }
    printf("-------------------------------------------------------------------------------"
           "-----------------------------------------------------------------\n\n");
}

void show_keys(key *table_keys, int amount)
{
    printf("\n\tKEY TABLE\n");
    printf("\n|INDEX|   PRICE   |");
    printf("\n------|-----------|\n");
    for (int i = 0; i < amount; i++)
        printf("%6d|%11d|\n", table_keys[i].index, table_keys[i].price);
    printf("-------------------\n\n");
}
