#include "app.h"

void print_interface(void)
{
    puts("******************************");
    puts("Select menu item");
    puts("1: Print GRAPH");
    puts("2: Perform task");
    puts("0: EXIT");
    printf("Your choice: ");
}

int main()
{
    int V;
    int E;
    srand(time(NULL));
    FILE *f = fopen("graph.txt", "r");
    //FILE *f = fopen("graph_negative.txt", "r");
    if (!f)
    {
         printf("File Error");
         return EXIT_FAILURE;
    }
    puts("Task is to define whether it is possible to get from vertice A to vertice B"
         " after deleting any 3 roads\n");
    if (fscanf(f, "%d %d", &V, &E)!=2)
    {
        puts("INCORRECT DATA");
        return EXIT_FAILURE;
    }
    int **wmtr = create_matrix(E);
    E -= 3;
    int **mtr=create_matrix(E);
    int u,v;
    for (int i=0; i<E + 3; i++)
    {
        if (fscanf(f,"%d %d",&u,&v)!=2 || (u>V) || (u<0) || (v>V) || (v<0))
        {

            puts("INCORRECT DATA");
            free_matrix(wmtr,E + 3);
            return EXIT_FAILURE;
        }
        wmtr[i][0] = u;
        wmtr[i][1] = v;
        wmtr[i][2] = 1;
    }
    int choice;
    while (1)
    {
        print_interface();
        scanf("%d", &choice);
        printf("\n");
        switch (choice)
        {
            case 0:
            {
                fclose(f);
                return EXIT_SUCCESS;
            }
            case 1:
            {
                show_matr_gv(wmtr, E + 3);
                break;
            }
            case 2:
            {
                if (E + 3 <= 3)
                {
                    puts("There is less than 4 roads so it is impossible to get anywhere after deleting"
                         " three of them");
                    break;
                }
                int src, end;
                printf("Input vertice A: ");
                if (scanf("%d",&src)!=1 || (src > V) || (src < 0))
                {
                    puts("incorrect vertice\n");
                    fclose(f);
                    break;
                }
                printf("Input vertice B: ");
                if (scanf("%d",&end)!=1 || (end > V) || (end < 0))
                {
                    puts("incorrect vertice\n");
                    fclose(f);
                    break;
                }
                if (src == end)
                {
                    printf("Vertice A and B should be different\n");
                    fclose(f);
                    break;
                }
                int del1, del2, del3;
                int randnum;
                int k;
                int flag = 0;
                for (int i = 0; i < 100000; i++)
                {

                    del1 = -1;
                    del2 = -1;
                    del3 = -1;
                    randnum = rand() % (E + 3);
                    del1 = randnum;
                    while (randnum == del1)
                        randnum = rand() % (E + 3);
                    del2 = randnum;
                    while (randnum == del1 || randnum == del2)
                        randnum = rand() % (E + 3);
                    del3 = randnum;
                    k = 0;
                    for (int j = 0; j < E + 3; j++)
                    {
                        if (j != del1 && j != del2 && j != del3)
                        {
                            mtr[k][0] = wmtr[j][0];
                            mtr[k][1] = wmtr[j][1];
                            mtr[k][2] = 1;
                            k++;
                        }
                    }
                    if (BellmanFord(mtr, V, E, src, end) != 0)
                    {
                        flag = 1;
                        printf("\nIt is impossible to get from A to B after deleting this three roads:\n");
                        printf("Road1: %d -> %d\n",wmtr[del1][0], wmtr[del1][1]);
                        printf("Road2: %d -> %d\n",wmtr[del2][0], wmtr[del2][1]);
                        printf("Road3: %d -> %d\n",wmtr[del3][0], wmtr[del3][1]);
                        break;
                    }
                }
                if (flag == 0)
                    printf("\nIt is possible to get from A to B after deleting three roads\n");
                break;
                /*
                time_t start,end;
                start=clock();
                for (int i=0; i<1000000; i++)
                    BellmanFord_time(mtr, V, E, src, end);
                end=clock();
                double time_res= ((double)(end - start) / CLOCKS_PER_SEC);
                printf("Use memory: %I64d bytes\n", E*3*sizeof(int));
                printf("Time work: %.6lfE-6\n", time_res);
                */
            }
        }
    }
}
