#ifndef MAIN_H
#define MAIN_H

#define CORR_END 7
#define ERR_EMPTY -1
#define T1_MIN 1
#define T1_MAX 5
#define T2_MIN 0
#define T2_MAX 1
#define T3_MIN 0
#define T3_MAX 4//10
#define T4_MIN 0
#define T4_MAX 1
#define QMAX 100000

typedef struct mas
{
  float qu[QMAX];
  int rear, frnt;
}mas_t;

typedef struct list
{
    float field;
    struct list *ptr;
}list_t;

typedef struct queue
{
    list_t *frnt, *rear;
}queue_t;

float float_rand(float min, float max);
list_t *init(float a);
float remove_elem(queue_t *q);
void insert(queue_t *q, float x);
list_t *addelem(list_t *lst, float number);
int isempty(queue_t *q);
void print(queue_t *q);
int masservice(queue_t *q1, queue_t *q2, int *countq1,
                int *countq2, int param, mas_t *m1, mas_t *m2,
               int *countm1, int *countm2);
void init_m(mas_t *q);
void insert_m(mas_t *q, float x);
int isempty_m(mas_t *q);
float remove_m(mas_t *q);
void print_m(mas_t *q);
void print_intermed(int q1proc, int q2proc, int midlength1, int midlength2,
                     int wtime1, int wtime2, float timeproc1, float timeproc2,
                    int countq1, int countq2, int param);

#endif // MAIN_H
