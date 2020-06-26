#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define CORR_END 0;
#define ERR_INP -1;
#define MAXMATR 10000
#define SPARCE 0;
#define ORDINARY 1;
typedef int matrix[MAXMATR][MAXMATR];

int freematr(int **matr, int rows)
{
    for (int i = 0; i < rows; i++)
        if (matr[i])
            free(matr[i]);
    free(matr);
    return CORR_END;
}

int **create(int m, int n)
{
    int **data = (int**)calloc(m, sizeof(int*));
    if (data)
    {
        for (int i = 0; i < m; i++)
        {
            data[i] = (int*)calloc(n, sizeof(int));
            if (!data[i])
            {
                printf("ERR no memory was given");
                freematr(data, m);
                return NULL;
            }
        }
        return data;
    }
    else
    {
        free(data);
        printf("ERR no memory was given");
        return NULL;
    }
}

int make_n_sum_sparce(int m, int n, int nums, int numsb, int a[][n], int b[][n])
{ 
    //func part
    int an[nums], bn[numsb];
    int ai[nums], bi[numsb];
    int aj[n + 1], bj[n + 1];
    int anlen = 0, bnlen = 0;
    int ailen = 0, bilen = 0;
    int ajlen = 0, bjlen = 0;
    int count = 0;
    aj[ajlen] = 0;
    ajlen++;
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < m; i++)
        {
            if (a[i][j] != 0)
            {
                an[anlen] = a[i][j];
                anlen++;
                ai[ailen] = i;
                ailen++;
                count++;
            }
        }
        aj[ajlen] = aj[ajlen - 1] + count;
        ajlen++;
        count = 0;
    }
    //matra
    if (m < 20 && n < 20)
    {
        printf("\nSparced first matrix: \nAN: ");
        for (int i = 0; i < nums; i++)
        {
            printf("%d ", an[i]);
        }
        puts("\nIA: ");
        for (int i = 0; i < nums; i++)
        {
            printf("%d ", ai[i]);
        }
        puts("\nJA: ");
        for (int i = 0; i < n + 1; i++)
        {
            printf("%d ", aj[i]);
        }
        puts("");
    }
    count = 0;
    bj[bjlen] = 0;
    bjlen++;
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < m; i++)
        {
            if (b[i][j] != 0)
            {
                bn[bnlen] = b[i][j];
                bnlen++;
                bi[bilen] = i;
                bilen++;
                count++;
            }
        }
        bj[bjlen] = bj[bjlen - 1] + count;
        bjlen++;
        count = 0;
    }
    //matrb
    if (m < 20 && n < 20)
    {
        printf("\nSparced second matrix: \nAN: ");
        for (int i = 0; i < numsb; i++)
        {
            printf("%d ", bn[i]);
        }
        puts("\nIA: ");
        for (int i = 0; i < numsb; i++)
        {
            printf("%d ", bi[i]);
        }
        puts("\nJA: ");
        for (int i = 0; i < n + 1; i++)
        {
            printf("%d ", bj[i]);
        }
        puts("");
    }
    int resn[nums + numsb];
    int resi[nums + numsb];
    int resj[n + 1];
    int resjlen = 0;
    int curposa = 0, rescurpos = 0, curposb = 0;
    int prevposa = 0, resprevpos = 0, prevposb = 0;
    count = 0;
    int flag = 0;
    resj[resjlen] = 0;
    resjlen++;
    for (int i = 0; i < ajlen - 1; i++)
    {
        curposa = aj[i + 1] - aj[i];
        for (int j = prevposa; j < prevposa + curposa; j++)
        {
            resn[rescurpos] = an[j];
            resi[rescurpos] = ai[j];
            count++;
            rescurpos++;
        }
        prevposa += curposa;
        curposb = bj[i + 1] - bj[i];
        flag = 0;
        for (int k = prevposb; k < prevposb + curposb; k++)
        {
            for (int n = resprevpos; n < rescurpos; n++)
            {
                if (bi[k] == resi[n])
                {
                    resn[n] += bn[k];
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
            {
                resn[rescurpos] = bn[k];
                resi[rescurpos] = bi[k];
                count++;
                rescurpos++;
            }
            flag = 0;
        }
        prevposb += curposb;
        resj[resjlen] = count + resj[resjlen - 1];
        count = 0;
        resjlen++;
        resprevpos = rescurpos;
    }
    //matrres
    printf("\nResult sparce matrix: \nAN: ");
    for (int i = 0; i < rescurpos; i++)
    {
        printf("%d ", resn[i]);
    }
    puts("\nIA: ");
    for (int i = 0; i < rescurpos; i++)
    {
        printf("%d ", resi[i]);
    }
    puts("\nJA: ");
    for (int i = 0; i < resjlen; i++)
    {
        printf("%d ", resj[i]);
    }
    puts("");
    return CORR_END;
}

void make_sparce_check(int m, int n, int **a, int **b, int **an, int **bn, int **ai, int **bi,
                       int **aj, int **bj, int anlen, int bnlen, int ailen, int bilen, int *ajlen, int bjlen)
{
    int count = 0;
    *(*aj + *ajlen) = 0;
    (*ajlen)++;
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < m; i++)
        {
            //printf("\n aij %d\n ", a[i][j]);
            if (a[i][j] != 0)
            {   
                *(*an + anlen) = a[i][j];
                //printf("\n%d an anlen\n", *(*an + anlen) );
                anlen++;
                *(*ai + ailen) = i;
                ailen++;
                count++;
            }
        }
        *(*aj + *ajlen) = *(*aj + *ajlen - 1) + count;
        //printf("\n%d aj ajlen\n", *(*aj + *ajlen));
        (*ajlen)++;
        count = 0;
    }
    count = 0;
    *(*bj + bjlen) = 0;
    bjlen++;
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < m; i++)
        {
            if (b[i][j] != 0)
            {
                *(*bn + bnlen) = b[i][j];
                bnlen++;
                *(*bi + bilen) = i;
                bilen++;
                count++;
            }
        }
        *(*bj + bjlen) = *(*bj + bjlen - 1) + count;
        //printf("\n%d bj bjlen\n", *(*bj + bjlen));
        bjlen++;
        count = 0;
    }
}

double sum_sparce_check(int m, int n, int **a, int **b, int **an, int **bn, int **ai, int **bi,
                        int **aj, int **bj, int anlen, int bnlen, int ailen, int bilen, int ajlen, int bjlen)
{
    int* resn= (int*) malloc(1000000*sizeof(int));
    int* resi = (int*) malloc(1000000*sizeof(int));
    int* resj = (int*) malloc(1001*sizeof(int));
    int resjlen = 0;
    int curposa = 0, rescurpos = 0, curposb = 0;
    int prevposa = 0, resprevpos = 0, prevposb = 0;
    int count = 0;
    int flag = 0;
    time_t start, end;
    double time_res;
    start = clock();
    resj[resjlen] = 0;
    resjlen++;
    //printf("ajlen %d", ajlen);
    //printf("\nresj %d\n", resj[resjlen]);
    for (int i = 0; i < ajlen - 1; i++)
    {
        curposa = *(*aj + i + 1) - *(*aj + i);
        //printf("\ncurposaa %d\n", *(*aj + i + 1) - *(*aj + i));
        //printf("\naj[i] %d", aj[i]);
        for (int j = prevposa; j < prevposa + curposa; j++)
        {
            //printf("j = %d an[j] = %d ai[j] = %d\n", j, an[j], ai[j]);
            resn[rescurpos] = *(*an + j);
            resi[rescurpos] = *(*ai + j);
            //printf("\ncurposa %d\n", resi[rescurpos]);
            count++;
            rescurpos++;
        }
        prevposa += curposa;
        curposb = *(*bj + i + 1) - *(*bj + i);
        //printf("\ncurposba %d\n", *(*bj + i + 1) - *(*bj + i));
        flag = 0;
        for (int k = prevposb; k < prevposb + curposb; k++)
        {
            for (int n = resprevpos; n < rescurpos; n++)
            {
                //puts("iter");
                if (*(*bi + k) == resi[n])
                {
                    resn[n] += *(*bn + k);
                    flag = 1;
                    break;
                }
            }
            if (flag == 0)
            {
                resn[rescurpos] = *(*bn + k);
                resi[rescurpos] = *(*bi + k);
                count++;
                rescurpos++;
            }
            flag = 0;
        }
        prevposb += curposb;
        resj[resjlen] = count + resj[resjlen - 1];
        count = 0;
        resjlen++;
        resprevpos = rescurpos;
    }
    //puts("PUKPUK");
    end = clock();
    time_res = ((double)(end - start) / CLOCKS_PER_SEC);
    free(resn);
    free(resi);
    free(resj);
    return time_res;
}

void shufflematr(int m, int n, int matr[][n])
{
    int tmp;
    int randi, randj;
    for (int k = 0; k < 100; k++)
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
            {
                randi = rand() % m;
                randj = rand() % n;
                tmp = matr[i][j];
                matr[i][j] = matr[randi][randj];
                matr[randi][randj] = tmp;
            }
}

void shufflematr_check(int m, int n, int ***matr)
{
    int tmp;
    int randi, randj;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        {
            randi = rand() % m;
            randj = rand() % n;
            tmp = *(*(*matr + i) + j);
            *(*(*matr + i) + j) = *(*(*matr + randi) + randj);
            *(*(*matr + randi) + randj) = tmp;
        }
}

int def_sum(int m, int n, int a[][n], int b[][n])
{
    int res[m][n];
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            res[i][j] = 0;
            res[i][j] = a[i][j] + b[i][j];
            if (res[i][j] != 0)
                printf("index i: %d\nindex j: %d\nres[i][j]: %d\n\n", i, j, res[i][j]);
        }
    }
    return CORR_END;
}

void def_sum_check(int m, int n, int **a, int **b)
{
    //probably dynamic sophuld be here too
    int **res = create(m, n);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            res[i][j] = 0;
            res[i][j] = a[i][j] + b[i][j];
        }
    }
    //int trash = res[0][0];
    //trash++;
    freematr(res, m);
}

void autofill_check(int m, int n, int *nums, int *numsb, int ***a, int ***b)
{
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        {
            *(*(*a + i) + j) = 0;
            *(*(*b + i) + j) = 0;
        }
    int allelems = m * n;
    int zeronums = floor(allelems * (100 - *nums) / 100);
    int notzeroa = m * n - zeronums;
    int zeroi = m - floor((zeronums / n));
    int zeroj = zeronums % n;
    for (int i = 0; i < zeroi; i++)
    {
        if (i == zeroi - 1)
           for (int j = 0; j < n - zeroj; j++)
                *(*(*a + i) + j) = rand() % 10 + 1;
        else
            for (int j = 0; j < n; j++)
                *(*(*a + i) + j) = rand() % 10 + 1;
    }
    shufflematr_check(m, n, a);
    zeronums =floor(allelems * (100 - *numsb) / 100);
    int notzerob = m * n - zeronums;
    zeroi = m - floor((zeronums / n));
    zeroj = zeronums % n;
    for (int i = 0; i < zeroi; i++)
    {
        if (i == zeroi - 1)
           for (int j = 0; j < n - zeroj; j++)
                *(*(*b + i) + j) = rand() % 10 + 1;
        else
            for (int j = 0; j < n; j++)
                *(*(*b + i) + j) = rand() % 10 + 1;
    }
    shufflematr_check(m, n, b);
    *nums = notzeroa;
    *numsb = notzerob;
}

int autofill(int m, int n, int param)
{
    int a[m][n];
    int b[m][n];
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        {
            a[i][j] = 0;
            b[i][j] = 0;
        }
    int nums, numsb;
    float nums1, numsb1;
    int allelems = m * n;
    printf("Enter percentage of non-zero elements of first matrix\n");
    if (!scanf("%f", &nums1))
    {
        printf("Input error\n");
        return ERR_INP;
    }
    nums = nums1;
    if (nums != nums1)
    {
        printf("Input error\n");
        return ERR_INP;
    }

    int zeronums =floor(allelems * (100 - nums) / 100);
    int notzeroa = m * n - zeronums;
    int zeroi = m - floor((zeronums / n));
    int zeroj = zeronums % n;
    for (int i = 0; i < zeroi; i++)
    {
        if (i == zeroi - 1)
           for (int j = 0; j < n - zeroj; j++)
                a[i][j] = rand() % 10 + 1;
        else
            for (int j = 0; j < n; j++)
                a[i][j] = rand() % 10 + 1;
    }
    printf("\nEnter percentage of non-zero elements of second matrix\n");
    if (!scanf("%f", &numsb1))
    {
        printf("Input error\n");
        return ERR_INP;
    }
    numsb = numsb1;
    if (numsb != numsb1)
    {
        printf("Input error\n");
        return ERR_INP;
    }
    shufflematr(m, n, a);
    zeronums =floor(allelems * (100 - numsb) / 100);
    int notzerob = m * n - zeronums;
    zeroi = m - floor((zeronums / n));
    zeroj = zeronums % n;
    for (int i = 0; i < zeroi; i++)
    {
        if (i == zeroi - 1)
           for (int j = 0; j < n - zeroj; j++)
                b[i][j] = rand() % 10 + 1;
        else
            for (int j = 0; j < n; j++)
                b[i][j] = rand() % 10 + 1;
    }
    shufflematr(m, n, b);
    if (m < 20 && n < 20)
    {
        puts("First matrix: \n");
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
                printf("%d ", a[i][j]);
            puts("");
        }
        puts("\nSecond matrix: \n");
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
                printf("%d ", b[i][j]);
            puts("");
        }
        puts("");
    }
    if (param == 0)
        make_n_sum_sparce(m, n, notzeroa, notzerob, a, b);
    else
        def_sum(m, n, a, b);
    return CORR_END;
}

int inp_matr(int m, int n, int param)
{
    int nums, numsb;
    float nums1, numsb1;
    printf("Enter number of non-zero elements of first matrix\n");
    if (!scanf("%f", &nums1))
    {
        printf("Input error\n");
        return ERR_INP;
    }
    nums = nums1;
    if (nums != nums1)
    {
        printf("Input error\n");
        return ERR_INP;
    }
    int a[m][n];
    int b[m][n];
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        {
            a[i][j] = 0;
            b[i][j] = 0;
        }
    int insi, insj, inselem;
    float insi1, insj1, inselem1;
    puts("Choose the row and column to insert non-zero element:\n");
    for (int i = 0; i < nums; i++)
    {
        printf("Enter row of insertion ");
        if (!scanf("%f", &insi1))
        {
            printf("Input error\n");
            return ERR_INP;
        }
        insi = insi1;
        if (insi != insi1 || insi > m || insi < 1)
        {
            printf("Input error\n");
            return ERR_INP;
        }
        printf("Enter column of insertion ");
        if (!scanf("%f", &insj1))
        {
            printf("Input error\n");
            return ERR_INP;
        }
        insj = insj1;
        if (insj != insj1 || insj > n || insj < 1)
        {
            printf("Input error\n");
            return ERR_INP;
        }
        printf("Enter non-zero element ");
        if (!scanf("%f", &inselem1))
        {
            printf("Input error\n");
            return ERR_INP;
        }
        inselem = inselem1;
        if (inselem != inselem1 || inselem == 0)
        {
            printf("Input error\n");
            return ERR_INP;
        }
        a[insi - 1][insj - 1] = inselem;
    }
    printf("\nEnter number of non-zero elements of second matrix\n");
    if (!scanf("%f", &numsb1))
    {
        printf("Input error\n");
        return ERR_INP;
    }
    numsb = numsb1;
    if (numsb != numsb1)
    {
        printf("Input error\n");
        return ERR_INP;
    }
    puts("Choose the row and column to insert non-zero element:\n");
    for (int i = 0; i < numsb; i++)
    {
        printf("Enter row of insertion ");
        if (!scanf("%f", &insi1))
        {
            printf("Input error\n");
            return ERR_INP;
        }
        insi = insi1;
        if (insi != insi1 || insi > m || insi < 1)
        {
            printf("Input error\n");
            return ERR_INP;
        }
        printf("Enter column of insertion ");
        if (!scanf("%f", &insj1))
        {
            printf("Input error\n");
            return ERR_INP;
        }
        insj = insj1;
        if (insj != insj1 || insj > n || insj < 1)
        {
            printf("Input error\n");
            return ERR_INP;
        }
        printf("Enter non-zero element ");
        if (!scanf("%f", &inselem1))
        {
            printf("Input error\n");
            return ERR_INP;
        }
        inselem = inselem1;
        if (inselem != inselem1 || inselem == 0)
        {
            printf("Input error\n");
            return ERR_INP;
        }
        b[insi - 1][insj - 1] = inselem;
    }
    if (m < 20 && n < 20)
    {
        puts("First matrix: \n");
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
                printf("%d ", a[i][j]);
            puts("");
        }
        puts("\nSecond matrix: \n");
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
                printf("%d ", b[i][j]);
            puts("");
        }
        puts("\n");
    }
    if (param == 1)
        def_sum(m, n, a, b);
    else
        make_n_sum_sparce(m, n, nums, numsb, a, b);
    return CORR_END;
}

void print_check(int m, int n, int perc, double time_res1, double time_res2, int not_zero,int num_of_iters)
{
    int iter = pow(10, num_of_iters);
    printf("%-5d x %5d|%8d|     %9.5lfE-%d    |      %9.5lfE-%d     |%22I64d|%24I64d|%20d|\n", m, n, perc, time_res1, num_of_iters,
              time_res2, num_of_iters, sizeof(int) * (not_zero * 2 + n + 1),  sizeof(int) * (2 * (n * m)), iter);
}

int compare()
{
    time_t start, end;
    double time_res1 = 0, time_res2 = 0;
    int* an = (int*) malloc(100*sizeof(int));
    int* bn = (int*) malloc(100*sizeof(int));
    int* ai = (int*) malloc(100*sizeof(int));
    int* bi = (int*) malloc(100*sizeof(int));
    int* aj = (int*) malloc(11*sizeof(int));
    int* bj = (int*) malloc(11*sizeof(int));
    int anlen = 0, bnlen = 0;
    int ailen = 0, bilen = 0;
    int ajlen = 0, bjlen = 0;
    int nums = 0, numsb = 0;
    printf (" Matrix size | Perc %% |Time sparce sum, sec |"
            "Time ordinary sum, sec | Memory sparce, bytes | Memory ordinary, bytes |Number of iterations|\n");
    printf("---------------------------------------------------------------------------"
           "---------------------------------------------------------------\n");
    //one block
    int zeronums =floor(10 * 10 * (100 - 0) / 100);
    int not_zero = 10 * 10 - zeronums;
    int **a = create(10, 10);
    int **b = create(10, 10);
    autofill_check(10, 10, &nums, &numsb, &a, &b);
    /*
    def_sum_check(int m, int n, int a[][n], int b[][n], double *time_res)
    make_sparce_check(int m, int n, int nums, int numsb, int a[][n], int b[][n], int an[], int bn[], int ai[], int bi[],
                           int aj[], int bj[], int anlen, int bnlen, int ailen, int bilen, int *ajlen, int bjlen, double *time_res);

    isum_sparce_check(int m, int n, int nums, int numsb, int a[][n], int b[][n], int an[], int bn[], int ai[], int bi[],
                         int aj[], int bj[], int anlen, int bnlen, int ailen, int bilen, int ajlen, int bjlen, double *time_res)
                         signatures*/
    make_sparce_check(10, 10, a, b, &an, &bn, &ai, &bi,
                           &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 10000; i++)
        time_res1 += sum_sparce_check(10, 10, a, b,  &an, &bn, &ai, &bi,
                                      &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 10000; i++)
        def_sum_check(10, 10, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    ajlen = 0;
    print_check(10, 10, 0, time_res1, time_res2, not_zero, 4);
    //
    time_res1 = 0;
    nums = 5, numsb = 5;
    autofill_check(10, 10, &nums, &numsb, &a, &b);
    make_sparce_check(10, 10, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 10000; i++)
        time_res1 += sum_sparce_check(10, 10, a, b, &an, &bn, &ai, &bi,
                                      &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 10000; i++)
        def_sum_check(10, 10, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(10 * 10 * (100 - 5) / 100);
    not_zero = 10 * 10 - zeronums;
    print_check(10, 10, 5, time_res1, time_res2, not_zero, 4);
    ajlen = 0;
    //
    time_res1 = 0;
    nums = 10, numsb = 10;
    autofill_check(10, 10, &nums, &numsb, &a, &b);
    make_sparce_check(10, 10, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 10000; i++)
        time_res1 += sum_sparce_check(10, 10, a, b, &an, &bn, &ai, &bi,
                                      &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 10000; i++)
        def_sum_check(10, 10, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(10 * 10 * (100 - 10) / 100);
    not_zero = 10 * 10 - zeronums;
    ajlen = 0;
    print_check(10, 10, 10, time_res1, time_res2, not_zero, 4);
    //
    time_res1 = 0;
    nums = 20, numsb = 20;
    autofill_check(10, 10, &nums, &numsb, &a, &b);
    make_sparce_check(10, 10, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 10000; i++)
        time_res1 += sum_sparce_check(10, 10, a, b, &an, &bn, &ai, &bi,
                                      &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 10000; i++)
        def_sum_check(10, 10, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(10 * 10 * (100 - 20) / 100);
    not_zero = 10 * 10 - zeronums;
    ajlen = 0;
    print_check(10, 10, 20, time_res1, time_res2, not_zero, 4);
    //
    time_res1 = 0;
    nums = 30, numsb = 30;
    autofill_check(10, 10, &nums, &numsb, &a, &b);
    make_sparce_check(10, 10, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 10000; i++)
        time_res1 += sum_sparce_check(10, 10, a, b, &an, &bn, &ai, &bi,
                                      &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 10000; i++)
        def_sum_check(10, 10, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(10 * 10 * (100 - 30) / 100);
    not_zero = 10 * 10 - zeronums;
    ajlen = 0;
    print_check(10, 10, 30, time_res1, time_res2, not_zero, 4);
    //
    time_res1 = 0;
    nums = 50, numsb = 50;
    autofill_check(10, 10, &nums, &numsb, &a, &b);
    make_sparce_check(10, 10, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 10000; i++)
        time_res1 += sum_sparce_check(10, 10, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 10000; i++)
        def_sum_check(10, 10, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(10 * 10 * (100 - 50) / 100);
    not_zero = 10 * 10 - zeronums;
    ajlen = 0;
    print_check(10, 10, 50, time_res1, time_res2, not_zero, 4);
    //
    time_res1 = 0;
    nums = 60, numsb = 60;
    autofill_check(10, 10, &nums, &numsb, &a, &b);
    make_sparce_check(10, 10, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 10000; i++)
        time_res1 += sum_sparce_check(10, 10, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 10000; i++)
        def_sum_check(10, 10, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(10 * 10 * (100 - 60) / 100);
    not_zero = 10 * 10 - zeronums;
    ajlen = 0;
    print_check(10, 10, 60, time_res1, time_res2, not_zero, 4);
    freematr(a, 10);
    freematr(b, 10);
    free(an);
    free(bn);
    free(ai);
    free(bi);
    free(aj);
    free(bj);

    //
    printf("---------------------------------------------------------------------");
    printf("---------------------------------------------------------------------\n");
    a = create(50, 50);
    b = create(50, 50);
    an = (int*) malloc(2500*sizeof(int));
    bn = (int*) malloc(2500*sizeof(int));
    ai = (int*) malloc(2500*sizeof(int));
    bi = (int*) malloc(2500*sizeof(int));
    aj = (int*) malloc(51*sizeof(int));
    bj = (int*) malloc(51*sizeof(int));
    time_res1 = 0;
    nums = 0, numsb = 0;
    autofill_check(50, 50, &nums, &numsb, &a, &b);
    make_sparce_check(50, 50, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 10000; i++)
        time_res1 += sum_sparce_check(50, 50, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 10000; i++)
        def_sum_check(50, 50, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(50 * 50 * (100 - 0) / 100);
    not_zero = 50 * 50 - zeronums;
    ajlen = 0;
    print_check(50, 50, 0, time_res1, time_res2, not_zero, 4);
    //
    time_res1 = 0;
    nums = 5, numsb = 5;
    autofill_check(50, 50, &nums, &numsb, &a, &b);
    make_sparce_check(50, 50, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 10000; i++)
        time_res1 += sum_sparce_check(50, 50, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 10000; i++)
        def_sum_check(50, 50, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(50 * 50 * (100 - 5) / 100);
    not_zero = 50 * 50 - zeronums;
    ajlen = 0;
    print_check(50, 50, 5, time_res1, time_res2, not_zero, 4);
    //
    time_res1 = 0;
    nums = 10, numsb = 10;
    autofill_check(50, 50, &nums, &numsb, &a, &b);
    make_sparce_check(50, 50, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 10000; i++)
        time_res1 += sum_sparce_check(50, 50, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 10000; i++)
        def_sum_check(50, 50, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(50 * 50 * (100 - 10) / 100);
    not_zero = 50 * 50 - zeronums;
    ajlen = 0;
    print_check(50, 50, 10, time_res1, time_res2, not_zero, 4);
    //
    time_res1 = 0;
    nums = 20, numsb = 20;
    autofill_check(50, 50, &nums, &numsb, &a, &b);
    make_sparce_check(50, 50, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 10000; i++)
        time_res1 += sum_sparce_check(50, 50, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 10000; i++)
        def_sum_check(50, 50, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(50 * 50 * (100 - 20) / 100);
    not_zero = 50 * 50 - zeronums;
    ajlen = 0;
    print_check(50, 50, 20, time_res1, time_res2, not_zero, 4);
    //
    time_res1 = 0;
    nums = 30, numsb = 30;
    autofill_check(50, 50, &nums, &numsb, &a, &b);
    make_sparce_check(50, 50, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 10000; i++)
        time_res1 += sum_sparce_check(50, 50, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 10000; i++)
        def_sum_check(50, 50, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(50 * 50 * (100 - 30) / 100);
    not_zero = 50 * 50 - zeronums;
    ajlen = 0;
    print_check(50, 50, 30, time_res1, time_res2, not_zero, 4);
    //
    time_res1 = 0;
    nums = 50, numsb = 50;
    autofill_check(50, 50, &nums, &numsb, &a, &b);
    make_sparce_check(50, 50, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 10000; i++)
        time_res1 += sum_sparce_check(50, 50, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 10000; i++)
        def_sum_check(50, 50, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(50 * 50 * (100 - 50) / 100);
    not_zero = 50 * 50 - zeronums;
    ajlen = 0;
    print_check(50, 50, 50, time_res1, time_res2, not_zero, 4);
    //
    time_res1 = 0;
    nums = 60, numsb = 60;
    autofill_check(50, 50, &nums, &numsb, &a, &b);
    make_sparce_check(50, 50, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 10000; i++)
        time_res1 += sum_sparce_check(50, 50, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 10000; i++)
        def_sum_check(50, 50, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(50 * 50 * (100 - 60) / 100);
    not_zero = 50 * 50 - zeronums;
    ajlen = 0;
    print_check(50, 50, 60, time_res1, time_res2, not_zero, 4);
    freematr(a, 50);
    freematr(b, 50);
    free(an);
    free(bn);
    free(ai);
    free(bi);
    free(aj);
    free(bj);
    //
    printf("---------------------------------------------------------------------");
    printf("---------------------------------------------------------------------\n");
    a = create(100, 100);
    b = create(100, 100);
    an = (int*) malloc(10000*sizeof(int));
    bn = (int*) malloc(10000*sizeof(int));
    ai = (int*) malloc(10000*sizeof(int));
    bi = (int*) malloc(10000*sizeof(int));
    aj = (int*) malloc(101*sizeof(int));
    bj = (int*) malloc(101*sizeof(int));
    time_res1 = 0;
    nums = 0, numsb = 0;
    autofill_check(100, 100, &nums, &numsb, &a, &b);
    make_sparce_check(100, 100, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 1000; i++)
        time_res1 += sum_sparce_check(100, 100, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 1000; i++)
        def_sum_check(100, 100, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(100 * 100 * (100 - 0) / 100);
    not_zero = 100 * 100 - zeronums;
    ajlen = 0;
    print_check(100, 100, 0, time_res1, time_res2, not_zero, 3);
    //
    time_res1 = 0;
    nums = 5, numsb = 5;
    autofill_check(100, 100, &nums, &numsb, &a, &b);
    make_sparce_check(100, 100, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 1000; i++)
        time_res1 += sum_sparce_check(100, 100, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 1000; i++)
        def_sum_check(100, 100, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(100 * 100 * (100 - 5) / 100);
    not_zero = 100 * 100 - zeronums;
    ajlen = 0;
    print_check(100, 100, 5, time_res1, time_res2, not_zero, 3);
    //
    time_res1 = 0;
    nums = 10, numsb = 10;
    autofill_check(100, 100, &nums, &numsb, &a, &b);
    make_sparce_check(100, 100, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 1000; i++)
        time_res1 += sum_sparce_check(100, 100, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 1000; i++)
        def_sum_check(100, 100, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(100 * 100 * (100 - 10) / 100);
    not_zero = 100 * 100 - zeronums;
    ajlen = 0;
    print_check(100, 100, 10, time_res1, time_res2, not_zero, 3);
    //
    time_res1 = 0;
    nums = 20, numsb = 20;
    autofill_check(100, 100, &nums, &numsb, &a, &b);
    make_sparce_check(100, 100, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 1000; i++)
        time_res1 += sum_sparce_check(100, 100, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 1000; i++)
        def_sum_check(100, 100, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(100 * 100 * (100 - 20) / 100);
    not_zero = 100 * 100 - zeronums;
    ajlen = 0;
    print_check(100, 100, 20, time_res1, time_res2, not_zero, 3);
    //
    time_res1 = 0;
    nums = 30, numsb = 30;
    autofill_check(100, 100, &nums, &numsb, &a, &b);
    make_sparce_check(100, 100, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 1000; i++)
        time_res1 += sum_sparce_check(100, 100, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 1000; i++)
        def_sum_check(100, 100, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(100 * 100 * (100 - 30) / 100);
    not_zero = 100 * 100 - zeronums;
    ajlen = 0;
    print_check(100, 100, 30, time_res1, time_res2, not_zero, 3);
    //
    time_res1 = 0;
    nums = 50, numsb = 50;
    autofill_check(100, 100, &nums, &numsb, &a, &b);
    make_sparce_check(100, 100, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 1000; i++)
        time_res1 += sum_sparce_check(100, 100, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 1000; i++)
        def_sum_check(100, 100, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(100 * 100 * (100 - 50) / 100);
    not_zero = 100 * 100 - zeronums;
    ajlen = 0;
    print_check(100, 100, 50, time_res1, time_res2, not_zero, 3);
    //
    time_res1 = 0;
    nums = 60, numsb = 60;
    autofill_check(100, 100, &nums, &numsb, &a, &b);
    make_sparce_check(100, 100, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 1000; i++)
        time_res1 += sum_sparce_check(100, 100, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 1000; i++)
        def_sum_check(100, 100, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(100 * 100 * (100 - 60) / 100);
    not_zero = 100 * 100 - zeronums;
    ajlen = 0;
    print_check(100, 100, 60, time_res1, time_res2, not_zero, 3);
    freematr(a, 100);
    freematr(b, 100);
    free(an);
    free(bn);
    free(ai);
    free(bi);
    free(aj);
    free(bj);
    //
    printf("---------------------------------------------------------------------");
    printf("---------------------------------------------------------------------\n");
    a = create(250, 250);
    b = create(250, 250);
    an = (int*) malloc(62500*sizeof(int));
    bn = (int*) malloc(62500*sizeof(int));
    ai = (int*) malloc(62500*sizeof(int));
    bi = (int*) malloc(62500*sizeof(int));
    aj = (int*) malloc(251*sizeof(int));
    bj = (int*) malloc(251*sizeof(int));
    time_res1 = 0;
    nums = 0, numsb = 0;
    autofill_check(250, 250, &nums, &numsb, &a, &b);
    make_sparce_check(250, 250, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 1000; i++)
        time_res1 += sum_sparce_check(250, 250, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 1000 * 1.8; i++)
        def_sum_check(250, 250, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(100 * 100 * (100 - 0) / 100);
    not_zero = 250 * 250 - zeronums;
    ajlen = 0;
    print_check(250, 250, 0, time_res1, time_res2, not_zero, 3);
    //
    time_res1 = 0;
    nums = 5, numsb = 5;
    autofill_check(250, 250, &nums, &numsb, &a, &b);
    make_sparce_check(250, 250, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 1000; i++)
        time_res1 += sum_sparce_check(250, 250, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 1000 * 1.8; i++)
        def_sum_check(250, 250, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(100 * 100 * (100 - 5) / 100);
    not_zero = 250 * 250 - zeronums;
    ajlen = 0;
    print_check(250, 250, 5, time_res1, time_res2, not_zero, 3);
    //
    time_res1 = 0;
    nums = 10, numsb = 10;
    autofill_check(250, 250, &nums, &numsb, &a, &b);
    make_sparce_check(250, 250, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 1000; i++)
        time_res1 += sum_sparce_check(250, 250, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 1000 * 1.8; i++)
        def_sum_check(250, 250, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(100 * 100 * (100 - 10) / 100);
    not_zero = 250 * 250 - zeronums;
    ajlen = 0;
    print_check(250, 250, 10, time_res1, time_res2, not_zero, 3);
    //
    time_res1 = 0;
    nums = 20, numsb = 20;
    autofill_check(250, 250, &nums, &numsb, &a, &b);
    make_sparce_check(250, 250, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 1000; i++)
        time_res1 += sum_sparce_check(250, 250, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 1000 * 1.8; i++)
        def_sum_check(250, 250, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(100 * 100 * (100 - 20) / 100);
    not_zero = 250 * 250 - zeronums;
    ajlen = 0;
    print_check(250, 250, 20, time_res1, time_res2, not_zero, 3);
    //
    time_res1 = 0;
    nums = 30, numsb = 30;
    autofill_check(250, 250, &nums, &numsb, &a, &b);
    make_sparce_check(250, 250, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 1000; i++)
        time_res1 += sum_sparce_check(250, 250, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 1000 * 1.8; i++)
        def_sum_check(250, 250, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(100 * 100 * (100 - 30) / 100);
    not_zero = 250 * 250 - zeronums;
    ajlen = 0;
    print_check(250, 250, 30, time_res1, time_res2, not_zero, 3);
    //
    time_res1 = 0;
    nums = 50, numsb = 50;
    autofill_check(250, 250, &nums, &numsb, &a, &b);
    make_sparce_check(250, 250, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 1000; i++)
        time_res1 += sum_sparce_check(250, 250, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 1000 * 1.8; i++)
        def_sum_check(250, 250, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(100 * 100 * (100 - 50) / 100);
    not_zero = 250 * 250 - zeronums;
    ajlen = 0;
    print_check(250, 250, 50, time_res1, time_res2, not_zero, 3);
    //
    time_res1 = 0;
    nums = 60, numsb = 60;
    autofill_check(250, 250, &nums, &numsb, &a, &b);
    make_sparce_check(250, 250, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 1000; i++)
        time_res1 += sum_sparce_check(250, 250, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 1000 * 1.8; i++)
        def_sum_check(250, 250, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(100 * 100 * (100 - 60) / 100);
    not_zero = 250 * 250 - zeronums;
    ajlen = 0;
    print_check(250, 250, 60, time_res1, time_res2, not_zero, 3);
    freematr(a, 250);
    freematr(b, 250);
    free(an);
    free(bn);
    free(ai);
    free(bi);
    free(aj);
    free(bj);
    //
    printf("---------------------------------------------------------------------");
    printf("---------------------------------------------------------------------\n");
    a = create(500, 500);
    b = create(500, 500);
    an = (int*) malloc(250000*sizeof(int));
    bn = (int*) malloc(250000*sizeof(int));
    ai = (int*) malloc(250000*sizeof(int));
    bi = (int*) malloc(250000*sizeof(int));
    aj = (int*) malloc(501*sizeof(int));
    bj = (int*) malloc(501*sizeof(int));
    time_res1 = 0;
    nums = 0, numsb = 0;
    autofill_check(500, 500, &nums, &numsb, &a, &b);
    make_sparce_check(500, 500, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 100; i++)
        time_res1 += sum_sparce_check(500, 500, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 100 * 3.5; i++)
        def_sum_check(500, 500, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(100 * 100 * (100 - 0) / 100);
    not_zero = 500 * 500 - zeronums;
    ajlen = 0;
    print_check(500, 500, 0, time_res1, time_res2, not_zero, 2);
    //
    time_res1 = 0;
    nums = 5, numsb = 5;
    autofill_check(500, 500, &nums, &numsb, &a, &b);
    make_sparce_check(500, 500, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 100; i++)
        time_res1 += sum_sparce_check(500, 500, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 100 * 3.5; i++)
        def_sum_check(500, 500, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(100 * 100 * (100 - 5) / 100);
    not_zero = 500 * 500 - zeronums;
    ajlen = 0;
    print_check(500, 500, 5, time_res1, time_res2, not_zero, 2);
    //
    time_res1 = 0;
    nums = 10, numsb = 10;
    autofill_check(500, 500, &nums, &numsb, &a, &b);
    make_sparce_check(500, 500, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 100; i++)
        time_res1 += sum_sparce_check(500, 500, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 100 * 3.5; i++)
        def_sum_check(500, 500, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(100 * 100 * (100 - 10) / 100);
    not_zero = 500 * 500 - zeronums;
    ajlen = 0;
    print_check(500, 500, 10, time_res1, time_res2, not_zero, 2);
    //
    time_res1 = 0;
    nums = 20, numsb = 20;
    autofill_check(500, 500, &nums, &numsb, &a, &b);
    make_sparce_check(500, 500, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 100; i++)
        time_res1 += sum_sparce_check(500, 500, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 100 * 3.5; i++)
        def_sum_check(500, 500, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(100 * 100 * (100 - 20) / 100);
    not_zero = 500 * 500 - zeronums;
    ajlen = 0;
    print_check(500, 500, 20, time_res1, time_res2, not_zero, 2);
    //
    time_res1 = 0;
    nums = 30, numsb = 30;
    autofill_check(500, 500, &nums, &numsb, &a, &b);
    make_sparce_check(500, 500, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 100; i++)
        time_res1 += sum_sparce_check(500, 500, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 100 * 3.5; i++)
        def_sum_check(500, 500, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(100 * 100 * (100 - 30) / 100);
    not_zero = 500 * 500 - zeronums;
    ajlen = 0;
    print_check(500, 500, 30, time_res1, time_res2, not_zero, 2);
    //
    time_res1 = 0;
    nums = 50, numsb = 50;
    autofill_check(500, 500, &nums, &numsb, &a, &b);
    make_sparce_check(500, 500, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 100; i++)
        time_res1 += sum_sparce_check(500, 500, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 100 * 3.5; i++)
        def_sum_check(500, 500, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(100 * 100 * (100 - 50) / 100);
    not_zero = 500 * 500 - zeronums;
    ajlen = 0;
    print_check(500, 500, 50, time_res1, time_res2, not_zero, 2);
    //
    time_res1 = 0;
    nums = 60, numsb = 60;
    autofill_check(500, 500, &nums, &numsb, &a, &b);
    make_sparce_check(500, 500, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 100; i++)
        time_res1 += sum_sparce_check(500, 500, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 100 * 3.5; i++)
        def_sum_check(500, 500, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(100 * 100 * (100 - 60) / 100);
    not_zero = 500 * 500 - zeronums;
    ajlen = 0;
    print_check(500, 500, 60, time_res1, time_res2, not_zero, 2);
    freematr(a, 500);
    freematr(b, 500);
    free(an);
    free(bn);
    free(ai);
    free(bi);
    free(aj);
    free(bj);
    //
    printf("---------------------------------------------------------------------");
    printf("---------------------------------------------------------------------\n");
    a = create(750, 750);
    b = create(750, 750);
    an = (int*) malloc(562500*sizeof(int));
    bn = (int*) malloc(562500*sizeof(int));
    ai = (int*) malloc(562500*sizeof(int));
    bi = (int*) malloc(562500*sizeof(int));
    aj = (int*) malloc(751*sizeof(int));
    bj = (int*) malloc(751*sizeof(int));
    time_res1 = 0;
    nums = 0, numsb = 0;
    autofill_check(750, 750, &nums, &numsb, &a, &b);
    make_sparce_check(750, 750, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 100; i++)
        time_res1 += sum_sparce_check(750, 750, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 100 * 4.3; i++)
        def_sum_check(750, 750, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(100 * 100 * (100 - 0) / 100);
    not_zero = 750 * 750 - zeronums;
    ajlen = 0;
    print_check(750, 750, 0, time_res1, time_res2, not_zero, 2);
    //
    time_res1 = 0;
    nums = 5, numsb = 5;
    autofill_check(750, 750, &nums, &numsb, &a, &b);
    make_sparce_check(750, 750, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 100; i++)
        time_res1 += sum_sparce_check(750, 750, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 100 * 4.3; i++)
        def_sum_check(750, 750, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(100 * 100 * (100 - 5) / 100);
    not_zero = 750 * 750 - zeronums;
    ajlen = 0;
    print_check(750, 750, 5, time_res1, time_res2, not_zero, 2);
    //
    time_res1 = 0;
    nums = 10, numsb = 10;
    autofill_check(750, 750, &nums, &numsb, &a, &b);
    make_sparce_check(750, 750, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 100; i++)
        time_res1 += sum_sparce_check(750, 750, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 100 * 4.3; i++)
        def_sum_check(750, 750, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(100 * 100 * (100 - 10) / 100);
    not_zero = 750 * 750 - zeronums;
    ajlen = 0;
    print_check(750, 750, 10, time_res1, time_res2, not_zero, 2);
    //
    time_res1 = 0;
    nums = 20, numsb = 20;
    autofill_check(750, 750, &nums, &numsb, &a, &b);
    make_sparce_check(750, 750, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 100; i++)
        time_res1 += sum_sparce_check(750, 750, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 100 * 4.3; i++)
        def_sum_check(750, 750, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(100 * 100 * (100 - 20) / 100);
    not_zero = 750 * 750 - zeronums;
    ajlen = 0;
    print_check(750, 750, 20, time_res1, time_res2, not_zero, 2);
    //
    time_res1 = 0;
    nums = 30, numsb = 30;
    autofill_check(750, 750, &nums, &numsb, &a, &b);
    make_sparce_check(750, 750, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 100; i++)
        time_res1 += sum_sparce_check(750, 750, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 100 * 4.3; i++)
        def_sum_check(750, 750, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(100 * 100 * (100 - 30) / 100);
    not_zero = 750 * 750 - zeronums;
    ajlen = 0;
    print_check(750, 750, 30, time_res1, time_res2, not_zero, 2);
    //
    freematr(a, 750);
    freematr(b, 750);
    free(an);
    free(bn);
    free(ai);
    free(bi);
    free(aj);
    free(bj);
    //
    printf("---------------------------------------------------------------------");
    printf("---------------------------------------------------------------------\n");
    a = create(1000, 1000);
    b = create(1000, 1000);
    an = (int*) malloc(1000000*sizeof(int));
    bn = (int*) malloc(1000000*sizeof(int));
    ai = (int*) malloc(1000000*sizeof(int));
    bi = (int*) malloc(1000000*sizeof(int));
    aj = (int*) malloc(1001*sizeof(int));
    bj = (int*) malloc(1001*sizeof(int));
    time_res1 = 0;
    nums = 0, numsb = 0;
    autofill_check(1000, 1000, &nums, &numsb, &a, &b);
    make_sparce_check(1000, 1000, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 100; i++)
        time_res1 += sum_sparce_check(1000, 1000, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 100 * 5; i++)
        def_sum_check(1000, 1000, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(100 * 100 * (100 - 0) / 100);
    not_zero = 1000 * 1000 - zeronums;
    ajlen = 0;
    print_check(1000, 1000, 0, time_res1, time_res2, not_zero, 2);
    //
    time_res1 = 0;
    nums = 5, numsb = 5;
    autofill_check(1000, 1000, &nums, &numsb, &a, &b);
    make_sparce_check(1000, 1000, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 100; i++)
        time_res1 += sum_sparce_check(1000, 1000, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 100 * 5; i++)
        def_sum_check(1000, 1000, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(100 * 100 * (100 - 5) / 100);
    not_zero = 1000 * 1000 - zeronums;
    ajlen = 0;
    print_check(1000, 1000, 5, time_res1, time_res2, not_zero, 2);
    //
    time_res1 = 0;
    nums = 10, numsb = 10;
    autofill_check(1000, 1000, &nums, &numsb, &a, &b);
    make_sparce_check(1000, 1000, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 100; i++)
        time_res1 += sum_sparce_check(1000, 1000, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 100 * 5; i++)
        def_sum_check(1000, 1000, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(100 * 100 * (100 - 10) / 100);
    not_zero = 1000 * 1000 - zeronums;
    ajlen = 0;
    print_check(1000, 1000, 10, time_res1, time_res2, not_zero, 2);
    //
    time_res1 = 0;
    nums = 20, numsb = 20;
    autofill_check(1000, 1000, &nums, &numsb, &a, &b);
    make_sparce_check(1000, 1000, a, b, &an, &bn, &ai, &bi,
                      &aj, &bj, anlen, bnlen, ailen, bilen, &ajlen, bjlen);
    for (int i = 0; i < 100; i++)
        time_res1 += sum_sparce_check(1000, 1000, a, b, &an, &bn, &ai, &bi,
                         &aj, &bj, anlen, bnlen, ailen, bilen, ajlen, bjlen);
    start = clock();
    for (int i = 0; i < 100 * 5; i++)
        def_sum_check(1000, 1000, a, b);
    end = clock();
    time_res2 = ((double)(end - start) / CLOCKS_PER_SEC);
    zeronums = floor(100 * 100 * (100 - 20) / 100);
    not_zero = 1000 * 1000 - zeronums;
    ajlen = 0;
    print_check(1000, 1000, 20, time_res1, time_res2, not_zero, 2);
    //
    freematr(a, 1000);
    freematr(b, 1000);
    free(an);
    free(bn);
    free(ai);
    free(bi);
    free(aj);
    free(bj);
    return CORR_END;
}

int main()
{
    int state = 0;
    printf("Variant:2\n");
    while (state == 0)
    {  
        printf("\nThis program sums 2 matrices.\n"
               "also it compares time and memory efficiency of matrix representation\n"
               "as 2 vectors and a list and in default representation\n");
        printf("MENU:\n1. Sum matrices represented as 2 vectors and a list,\n"
               "get the result in the same representation.\n"
               "2. Sum matrices in default representation and\n"
               "get the result in the same form.\n"
               "3. Compare efficiency of summation in different forms of containig matrix\n"
               "4. Close the program.\n\n");
        int s;
        float s1;
        printf("YOUR CHOICE: ");
        if (!scanf("%f", &s1))
        {
            printf("Input error\n");
            return ERR_INP;
        }
        s = s1;
        if (s != s1)
        {
            printf("Input error\n");
            return ERR_INP;
        }
        switch (s)
        {
        case 1:
        {
            int m, n;
            float m1, n1;
            printf("Enter number of rows: ");
            if (!scanf("%f", &m1))
            {
                printf("Input error\n");
                return ERR_INP;
            }
            m = m1;
            if (m != m1 || m < 1 || m > 300)
            {
                printf("Input error\n");
                return ERR_INP;
            }
            printf("Enter number of columns: ");
            if (!scanf("%f", &n1))
            {
                printf("Input error\n");
                return ERR_INP;
            }
            n = n1;
            if (n != n1 || n < 1 || n > 300)
            {
                printf("Input error\n");
                return ERR_INP;
            }
            int fillch;
            float fillch1;
            printf("How do you want to fill the matrixs?\n1.Manually\n2.Automatically");
            printf("\nMake your choice: ");
            if (!scanf("%f", &fillch1))
            {
                printf("Input error\n");
                return ERR_INP;
            }
            fillch = fillch1;
            if (fillch != fillch1 || (fillch != 1 && fillch != 2))
            {
                printf("Input error\n");
                return ERR_INP;
            }
            if (fillch == 1)
                inp_matr(m, n, 0);
            else
                autofill(m, n, 0);
            break;
        }
        case 2:
        {
            int m, n;
            float m1, n1;
            printf("Enter number of rows: ");
            if (!scanf("%f", &m1))
            {
                printf("Input error\n");
                return ERR_INP;
            }
            m = m1;
            if (m != m1 || m < 1 || m > 300)
            {
                printf("Input error\n");
                return ERR_INP;
            }
            printf("Enter number of columns: ");
            if (!scanf("%f", &n1))
            {
                printf("Input error\n");
                return ERR_INP;
            }
            n = n1;
            if (n != n1 || n < 1 || n > 300)
            {
                printf("Input error\n");
                return ERR_INP;
            }
            int fillch;
            float fillch1;
            printf("How do you want to fill the matrixs?\n1.Manually\n2.Automatically");
            printf("\nMake your choice: ");
            if (!scanf("%f", &fillch1))
            {
                printf("Input error\n");
                return ERR_INP;
            }
            fillch = fillch1;
            if (fillch != fillch1 || (fillch != 1 && fillch != 2))
            {
                printf("Input error\n");
                return ERR_INP;
            }
            if (fillch == 1)
                inp_matr(m, n, 1);
            else
                autofill(m, n, 1);
            break;
        }
        case 3:
            compare();
            break;
        case 4:
            printf("Exit...");
            return CORR_END;
        default:
            printf("ERR input");
            return ERR_INP;
        }
    }
    return CORR_END;
    return 0;
}
