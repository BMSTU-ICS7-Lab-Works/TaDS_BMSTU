#include <stdlib.h>
#include <stdio.h>
#include "main.h"


list_t *init(float a)
{
  list_t *lst;
  lst = (list_t*)malloc(sizeof(list_t));
  lst->field = a;
  lst->ptr = NULL;
  return(lst);
}

int isempty(queue_t *q)
{
  if(q->frnt == 0)
    return 1;
  else
    return 0;
}

list_t *addelem(list_t *lst, float number)
{
  list_t *temp, *p;
  temp = (list_t*)malloc(sizeof(list_t));
  p = lst->ptr;
  lst->ptr = temp;
  temp->field = number;
  temp->ptr = p;
  return temp;
}

void insert(queue_t *q, float x)
{
  if ((q->rear == 0) && (q->frnt == 0))
  {
    q->rear = init(x);
    q->frnt = q->rear;
  }
  else
    q->rear = addelem(q->rear, x);
}

float remove_elem(queue_t *q)
{
  list_t *temp;
  float x;
  if(isempty(q) == 1)
  {
    printf("Queue is empty!\n");
    return ERR_EMPTY;
  }
  x = q->frnt->field;
  temp = q->frnt;
  q->frnt = q->frnt->ptr;
  free(temp);
  return x;
}

void print(queue_t *q)
{
  list_t *h;
  if(isempty(q) == 1)
  {
    printf("Queue is empty!\n");
    return;
  }
  for(h = q->frnt; h!= NULL; h = h->ptr)
    printf("%f ", h->field);
}
