#ifndef APP_H
#define APP_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INF 100000
void free_matrix(int **mtr, int E); // освобождение матрицы
int **create_matrix(int E); // создание матрицы
int BellmanFord(int **graph, int V, int E, int src, int end); // алгоритм Белмана-Форда
void show_matr_gv(int **a, int E); // визуализация графа
void BellmanFord_time(int **graph, int V, int E, int src, int end); // посмотреть время работы алгоритма
#endif // APP_H
