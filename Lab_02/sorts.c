#include "main.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void sortkey(key *table_keys, int param, int amount)
{
    key tmp;
    if (param == 1)
    {
        //there will be bubble
        for (int i = 0 ; i < amount - 1; i++)
        {
           // сравниваем два соседних элемента.
           for (int j = 0 ; j < amount - 1; j++)
           {
               if(table_keys[j].price > table_keys[j+1].price)
               {

                  // если они идут в неправильном порядке, то
                  //  меняем их местами.
                  tmp = table_keys[j];
                  table_keys[j] = table_keys[j+1];
                  table_keys[j+1] = tmp;
               }
            }
        }
    }
    else
    {
        //there will be shelll
        int step, i, j;
        key tmp;
        // Выбор шага
        for (step = amount / 2; step > 0; step /= 2)
            // Перечисление элементов, которые сортируются на определённом шаге
            for (i = step; i < amount; i++)
                // Перестановка элементов внутри подсписка, пока i-тый не будет отсортирован
                for (j = i - step; j >= 0 && table_keys[j].price > table_keys[j + step].price; j -= step)
                {
                    tmp = table_keys[j];
                    table_keys[j] = table_keys[j + step];
                    table_keys[j + step] = tmp;
                }

    }
}

void sortcars(cars *table_cars, int param, int amount)
{
    cars tmp;
    if (param == 1)
    {
        //there will be bubble
        for (int i = 0 ; i < amount - 1; i++)
        {
           // сравниваем два соседних элемента.
           for(int j = 0 ; j < amount - 1; j++)
           {
               if (table_cars[j].price > table_cars[j+1].price)
               {
                  // если они идут в неправильном порядке, то
                  //  меняем их местами.
                  tmp = table_cars[j];
                  table_cars[j] = table_cars[j+1];
                  table_cars[j+1] = tmp;
               }
            }
        }
    }
    else
    {
        //there will be shell
        int step, i, j;
        cars tmp;
        // Выбор шага
        for (step = amount / 2; step > 0; step /= 2)
            // Перечисление элементов, которые сортируются на определённом шаге
            for (i = step; i < amount; i++)
                // Перестановка элементов внутри подсписка, пока i-тый не будет отсортирован
                for (j = i - step; j >= 0 && table_cars[j].price > table_cars[j + step].price; j -= step)
                {
                    tmp = table_cars[j];
                    table_cars[j] = table_cars[j + step];
                    table_cars[j + step] = tmp;
                }
    }
}

void shuffle(cars *table_cars, key *table_keys, int param, int amount)
{
    cars tmp;
    key tmp1;
    if (param == 1)
    {
        for (int i = amount - 1; i >= 1; i--)
        {
            int ind = rand() % amount;
            tmp = table_cars[ind];
            table_cars[ind] = table_cars[i];
            table_cars[i] = tmp;
        }
    }
    else
    {
        for (int i = amount - 1; i >= 1; i--)
        {
            int ind = rand() % amount;
            tmp1 = table_keys[ind];
            table_keys[ind] = table_keys[ind];
            table_keys[ind] = tmp1;
        }

    }
}
