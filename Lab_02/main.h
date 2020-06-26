#ifndef MAIN_H
#define MAIN_H

#define CORR_END 0
#define ERR_INP -1
#define MAX_SIZE 100
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

void show_table(cars *table_cars, int, key *table_keys, int);
int fill_table(cars *table, key *table_key);
int fill_num(int*, char*, int*, int);
int fill_str(char*, char*, int*);
int add_note(cars *table, int*);
int delete_note(int*, cars *table);
int search_notes(int, cars *table, int, char*, int*, int);
int check_str(char*);
void show_task(cars *table_cars, int, char*, int, int);
void show_keys(key *table_key, int);
void sortkey(key *table_key, int, int);
void sortcars(cars *table_cars, int, int);
void check_efficiency(cars *table_cars, key *table_keys, int);
void shuffle(cars *table_cars, key *table_keys, int, int);

#endif // MAIN_H
