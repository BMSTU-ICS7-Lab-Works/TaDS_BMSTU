/*
#include "main.h"

#define CHAR_SIZE 30

typedef struct
{
    int warranty;
} new;

typedef struct
{
    int date;
    int mileage;
    int num_repairs;
    int num_owners;
} not_new;

typedef union
{
    new new1;
    not_new not_new1;
} inverse_type;

typedef struct
{
    char mark[CHAR_SIZE];
    char country[CHAR_SIZE];
    int price;
    char colour[CHAR_SIZE];
    char condition[CHAR_SIZE];
    inverse_type type;
} cars;

typedef struct
{
    int index;
    int price;
} key;
*/
