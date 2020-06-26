#include "app.h"

int BellmanFord(int **graph, int V, int E, int src, int end)
{
    // Инцилизация расстояний всех вершин как INF.
    int dis[V];
    for(int i = 0; i < V; i++)
        dis[i] = INF;

    // Инцилизация расстояния источника как 0
    dis[src] = 0;

    // Релаксация всех ребер |V| - 1 раз
    for (int i = 0; i < V - 1; i++)
    {
        for(int j = 0; j < E; j++)
        {
            if (dis[graph[j][0]] + graph[j][2] < dis[graph[j][1]])
                dis[graph[j][1]] =  dis[graph[j][0]] + graph[j][2];
        }
    }

    // Проверка на негативный цикл.
    for(int i = 0; i < E; i++)
    {
        int x = graph[i][0];
        int y = graph[i][1];
        int weight = graph[i][2];
        if (dis[x] != INF && dis[x] + weight < dis[y])
        {
            puts("Graph contains negative weight cycle");
            return -2;
        }
    }
    if (dis[end] < INF)
    {
        //puts("Path were found");
        return 0;
    }
    else
    {
        //puts("No such path");
        return -1;
    }
}

// для времени работы алгоритма
void BellmanFord_time(int **graph, int V, int E, int src, int end)
{
    int dis[V];
    for(int i = 0; i < V; i++)
        dis[i] = INF;
    dis[src] = 0;
    for (int i = 0; i < V - 1; i++)
    {
        for(int j = 0; j < E; j++)
        {
            if (dis[graph[j][0]] + graph[j][2] < dis[graph[j][1]])
                dis[graph[j][1]] =  dis[graph[j][0]] + graph[j][2];
        }
    }
    for(int i = 0; i < E; i++)
    {
        int x = graph[i][0];
        int y = graph[i][1];
        int weight = graph[i][2];
        if (dis[x] != INF && dis[x] + weight < dis[y])
        {
            puts("Graph contains negative weight cycle");
            return;
        }
    }
}
