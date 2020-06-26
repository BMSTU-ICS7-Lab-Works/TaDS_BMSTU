#include "app.h"

void show_matr_gv(int **a, int E)
{
    FILE *f = fopen("output.gv", "w");
    fprintf(f, "digraph My_graph {\n");
    for (int i = 0; i < E; i++)
    {
        if (a[i][2] < INF && a[i][2] != 0)
            fprintf(f, "%d -> %d;\n", a[i][0], a[i][1]);
    }
    fprintf(f, "}\n");
    fclose(f);
}
