#include <stdlib.h>
#include <stdio.h>
#include "main.h"

void init_m(mas_t *q)
{
  q->frnt = 1;
  q->rear = 0;
}

void insert_m(mas_t *q, float x)
{
  if (q->rear < QMAX-1)
  {
    q->rear++;
    q->qu[q->rear] = x;
  }
  else
    printf("Queue is full!\n");
}

int isempty_m(mas_t *q)
{
  if (q->rear < q->frnt)
      return 1;
  else
      return 0;
}

float remove_m(mas_t *q)
{
  float x;
  int h;
  if (isempty_m(q) == 1)
  {
    printf("Queue is empty!\n");
    return 0;
  }
  x = q->qu[q->frnt];
  for (h = q->frnt; h < q->rear; h++)
    q->qu[h] = q->qu[h+1];
  q->rear--;
  return x;
}

void print_m(mas_t *q)
{
  int h;
  if (isempty_m(q) == 1)
  {
    printf("Queue is empty!\n");
    return;
  }
  for (h = q->frnt; h <= q->rear; h++)
    printf("%f ", q->qu[h]);
  puts("end");
  return;
}
