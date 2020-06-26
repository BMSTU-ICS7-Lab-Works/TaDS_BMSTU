#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "main.h"

float float_rand(float min, float max)
{
    float scale = rand() / (float) RAND_MAX; /* [0, 1.0] */
    //printf("scale %f \n", scale);
    return min + scale * ( max - min );      /* [min, max] */
}

void print_intermed(int q1proc, int q2proc, int midlength1, int midlength2, int wtime1, int wtime2,
                    float timeproc1, float timeproc2, int countq1, int countq2, int param)
{
    if (param == 0)
    {
        printf("--------------------------------------------------\n");
        printf("Proceeded queue 1: %d\n\n", q1proc);
        printf("Proceeded queue 2: %d\n\n", q2proc);
        printf("Median queue 1 length: %f\n", (float) midlength1 / q1proc);
        printf("Median queue 2 length: %f\n", (float) midlength2 / q2proc);
        printf("Median waiting time for queue 1: %f\n", (float) wtime1 / q1proc);
        printf("Median waiting time for queue 2: %f\n", (float) wtime2 / q2proc);
        printf("--------------------------------------------------\n\n");
    }
    else
    {
        printf("--------------------------------------------------\n");
        printf("Time proceeding queue 1: %f\n\n", timeproc1);
        printf("Time proceeding queue 2: %f\n\n", timeproc2);
        //printf("Time proceeding queue 1 && queue 2: %f\n\n", timeproc1 + timeproc2);
        printf("Queue 1 requests entered: %d\n", countq1 + q1proc);
        printf("Queue 2 requests entered: %d\n", countq2 + q2proc);
        printf("Queue 1 requests out: %d\n", q1proc);
        printf("Queue 2 requests out: %d\n", q2proc);
        printf("--------------------------------------------------\n\n");
    }
}

int masservice(queue_t *q1, queue_t *q2, int *countq1, int *countq2,
               int param, mas_t *m1, mas_t *m2, int *countm1, int *countm2)
{
    float t1 = float_rand(T1_MIN, T1_MAX);
    float t2 = float_rand(T2_MIN, T2_MAX);
    float t3, t4;
    float rem1 = t1, rem2 = t2;
    int flagproc = -1;
    int q1proc = 0;
    int q2proc = 0;
    int prevq1proc = 0;
    int m1proc = 0;
    int m2proc = 0;
    int prevm1proc = 0;
    float wtime1 = 0, wtime2 = 0;
    float overtime1 = 0, overtime2 = 0;
    int midlength1 = 0, midlength2 = 0;
    int modflag1 = 0;
    int modflag2 = 0;
    float timeproc1 = 0;
    float timeproc2 = 0;
    if (T1_MIN + T1_MAX < T3_MAX + T3_MIN)
        modflag1 = 1;
    if (T2_MIN + T2_MAX < T4_MAX + T4_MIN)
        modflag2 = 1;
    modflag2 = 1;
    //printf("modlfags %d %d\n", modflag1, modflag2);
    while (q1proc <= 1000 && m1proc <= 1000)
    {
        if (param == 0)
        {
            //printf("%f time proces %f\n", t1, t2);
            if (q1proc % 100 == 0 && q1proc != prevq1proc)
            {

                if (q1proc == 1000)
                    print_intermed(q1proc, q2proc, midlength1, midlength2, wtime1, wtime2, timeproc1, timeproc2, *countq1, *countq2, 1);
                else
                    print_intermed(q1proc, q2proc, midlength1, midlength2, wtime1, wtime2, timeproc1, timeproc2, *countq1, *countq2, 0);
                prevq1proc = q1proc;
            }
            //printf("\ncount q1 q2 %d %d\n\n", (*countq1), (*countq2));
            /*
            printf("\nflagproc %d\n", flagproc);
            if (flagproc > -1)
            {
                print(q1);
                printf("\n\n");
                print(q2);
            }
            */
            if ((*countq1) == 0 && (*countq2) == 0)
            {
                q1->rear = init(t1);
                q1->frnt = q1->rear;
                (*countq1)++;
                q2->rear = init(t2);
                q2->frnt = q2->rear;
                (*countq2)++;
                if (rem1 < rem2)
                {
                    rem1 = float_rand(T1_MIN, T1_MAX);
                    overtime1 = rem1;
                    rem2 = t2 - t1;
                    overtime2 = rem2;
                    flagproc = 0;
                    t3 = float_rand(T3_MIN, T3_MAX);
                    if (modflag1 == 0)
                        timeproc1 += q1->frnt->field;
                    if (modflag1 == 1)
                        timeproc1 += t3;
                    remove_elem(q1);
                    q1proc++;
                    (*countq1)--;
                    while (overtime1 <= t3)
                    {
                        if ((*countq1) == 0)
                        {
                            q1->rear = init(t1);
                            q1->frnt = q1->rear;
                        }
                        else
                            insert(q1, t1);
                        overtime1 += t1;
                        (*countq1)++;
                        t1 = float_rand(T1_MIN, T1_MAX);
                    }
                    while (overtime2 <= t3)
                    {
                        insert(q2, t2);
                        (*countq2)++;
                        overtime2 += t2;
                        t2 = float_rand(T2_MIN, T2_MAX);
                    }
                    rem1 = overtime1 - t3;
                    rem2 = overtime2 - t3;
                }
                else
                {
                    rem1 = t1 - t2;
                    overtime1 = rem1;
                    rem2 = float_rand(T2_MIN, T2_MAX);
                    overtime2 = rem2;
                    flagproc = 1;
                    t4 = float_rand(T4_MIN, T4_MAX);
                    if (modflag2 == 0)
                        timeproc2 += q2->frnt->field;

                    if (modflag2 == 1)
                        timeproc2 += t4;
                    remove_elem(q2);
                    q2proc++;
                    (*countq2)--;
                    while (overtime1 <= t4)
                    {

                        insert(q1, t1);
                        (*countq1)++;
                        overtime1 += t1;
                        t1 = float_rand(T1_MIN, T1_MAX);
                    }
                    while (overtime2 <= t4)
                    {
                        if ((*countq2) == 0)
                        {
                            q2->rear = init(t2);
                            q2->frnt = q2->rear;
                        }
                        else
                            insert(q2, t2);
                        (*countq2)++;
                        overtime2 += t2;
                        t2 = float_rand(T2_MIN, T2_MAX);
                    }
                    rem1 = overtime1 - t4;
                    rem2 = overtime2 - t4;
                }
                overtime1 = rem1;
                overtime2 = rem2;
            }
            else if ((flagproc == 0 && (*countq1) != 0) ||
                     (flagproc == 1 && (*countq2) != 0))
            {
                if (flagproc == 0)
                {
                    t3 = float_rand(T3_MIN, T3_MAX);
                    if (modflag1 == 0)
                        timeproc1 += q1->frnt->field;
                    if (modflag1 == 1)
                        timeproc1 += t3;
                    //print(q1);
                    // print(q2);
                    remove_elem(q1);
                    q1proc++;
                    (*countq1)--;
                    while (overtime1 <= t3)
                    {
                        if ((*countq1) == 0)
                        {
                            q1->rear = init(t1);
                            q1->frnt = q1->rear;
                        }
                        else
                            insert(q1, t1);
                        (*countq1)++;
                        t1 = float_rand(T1_MIN, T1_MAX);
                        overtime1 += t1;
                    }
                    while (overtime2 <= t3)
                    {
                        if ((*countq2) == 0)
                        {
                            q2->rear = init(t2);
                            q2->frnt = q2->rear;
                        }
                        else
                            insert(q2, t2);
                        (*countq2)++;
                        t2 = float_rand(T2_MIN, T2_MAX);
                        overtime2 += t2;
                    }
                    rem1 = overtime1 - t3;
                    rem2 = overtime2 - t3;
                }
                if (flagproc == 1)
                {
                    t4 = float_rand(T4_MIN, T4_MAX);
                    if (modflag2 == 0)
                        timeproc2 += q2->frnt->field;
                    if (modflag2 == 1)
                        timeproc2 += t4;
                    remove_elem(q2);
                    q2proc++;
                    (*countq2)--;
                    while (overtime1 <= t4)
                    {
                        if ((*countq1) == 0)
                        {
                            q1->rear = init(t1);
                            q1->frnt = q1->rear;
                        }
                        else
                            insert(q1, t1);
                        (*countq1)++;
                        t1 = float_rand(T1_MIN, T1_MAX);
                        overtime1 += t1;
                    }
                    while (overtime2 <= t4)
                    {
                        if ((*countq2) == 0)
                        {
                            q2->rear = init(t2);
                            q2->frnt = q2->rear;
                        }
                        else
                            insert(q2, t2);
                        (*countq2)++;
                        t2 = float_rand(T2_MIN, T2_MAX);
                        overtime2 += t2;
                    }
                    rem1 = overtime1 - t4;
                    rem2 = overtime2 - t4;
                }
                wtime1 += overtime1;
                wtime2 += overtime2;
                overtime1 = rem1;
                overtime2 = rem2;
            }
            else if ((*countq1) != 0 && (*countq2) == 0)
            {
                flagproc = 0;
                t3 = float_rand(T3_MIN, T3_MAX);
                if (modflag1 == 0)
                    timeproc1 += q1->frnt->field;
                if (modflag1 == 1)
                    timeproc1 += t3;
                remove_elem(q1);
                q1proc++;
                (*countq1)--;
                while (overtime1 <= t3)
                {
                    if ((*countq1) == 0)
                    {
                        q1->rear = init(t1);
                        q1->frnt = q1->rear;
                    }
                    else
                        insert(q1, t1);
                    (*countq1)++;
                    t1 = float_rand(T1_MIN, T1_MAX);
                    overtime1 += t1;
                }
                while (overtime2 <= t3)
                {
                    if ((*countq2) == 0)
                    {
                        q2->rear = init(t2);
                        q2->frnt = q2->rear;
                    }
                    else
                        insert(q2, t2);
                    (*countq2)++;
                    t2 = float_rand(T2_MIN, T2_MAX);
                    overtime2 += t2;
                }
                wtime1 += overtime1;
                wtime2 += overtime2;
                rem1 = overtime1 - t3;
                rem2 = overtime2 - t3;
                overtime1 = rem1;
                overtime2 = rem2;
            }
            else if ((*countq1) == 0 && (*countq2) != 0)
            {
                flagproc = 1;
                t4 = float_rand(T4_MIN, T4_MAX);
                if (modflag2 == 0)
                    timeproc2 += q2->frnt->field;
                if (modflag2 == 1)
                    timeproc2 += t4;
                remove_elem(q2);
                q2proc++;
                (*countq2)--;
                while (overtime1 <= t4)
                {
                    if ((*countq1) == 0)
                    {
                        q1->rear = init(t1);
                        q1->frnt = q1->rear;
                    }
                    else
                        insert(q1, t1);
                    (*countq1)++;
                    t1 = float_rand(T1_MIN, T1_MAX);
                    overtime1 += t1;
                }
                while (overtime2 <= t4)
                {
                    if ((*countq2) == 0)
                    {
                        q2->rear = init(t2);
                        q2->frnt = q2->rear;
                    }
                    else
                        insert(q2, t2);
                    (*countq2)++;
                    t2 = float_rand(T2_MIN, T2_MAX);
                    overtime2 += t2;
                }
                wtime1 += overtime1;
                wtime2 += overtime2;
                rem1 = overtime1 - t4;
                rem2 = overtime2 - t4;
                overtime1 = rem1;
                overtime2 = rem2;
            }
            midlength1 += *countq1;
            midlength2 += *countq2;
        }
        else
        {
            /*
            print_m(m1);
            printf("\n\n");
            print_m(m2);
            */
            if (m1proc % 100 == 0 && m1proc != prevm1proc)
            {
                if (m1proc == 1000)
                    print_intermed(m1proc, m2proc, midlength1, midlength2, wtime1, wtime2, timeproc1, timeproc2, *countm1, *countm2, 1);
                else
                    print_intermed(m1proc, m2proc, midlength1, midlength2, wtime1, wtime2,  timeproc1, timeproc2, *countm1, *countm2, 0);
                prevm1proc = m1proc;
            }
            if ((*countm1) == 0 && (*countm2) == 0)
            {
                (*countm1)++;
                (*countm2)++;
                insert_m(m1, t1);
                insert_m(m2, t2);
                if (rem1 < rem2)
                {
                    rem1 = float_rand(T1_MIN, T1_MAX);
                    overtime1 = rem1;
                    rem2 = t2 - t1;
                    overtime2 = rem2;
                    flagproc = 0;
                    t3 = float_rand(T3_MIN, T3_MAX);
                    if (modflag1 == 0)
                        timeproc1 += m1->qu[m1->frnt];
                    if (modflag1 == 1)
                        timeproc1 += t3;
                    remove_m(m1);
                    m1proc++;
                    (*countm1)--;
                    while (overtime1 <= t3)
                    {
                        insert_m(m1, t1);
                        overtime1 += t1;
                        (*countm1)++;
                        t1 = float_rand(T1_MIN, T1_MAX);
                    }
                    while (overtime2 <= t3)
                    {
                        insert_m(m2, t2);
                        (*countm2)++;
                        overtime2 += t2;
                        t2 = float_rand(T2_MIN, T2_MAX);
                    }
                    wtime1 += overtime1;
                    wtime2 += overtime2;
                    rem1 = overtime1 - t3;
                    rem2 = overtime2 - t3;
                }
                else
                {
                    rem1 = t1 - t2;
                    overtime1 = rem1;
                    rem2 = float_rand(T2_MIN, T2_MAX);
                    overtime2 = rem2;
                    flagproc = 1;
                    t4 = float_rand(T4_MIN, T4_MAX);
                    if (modflag2 == 0)
                        timeproc2 += m2->qu[m2->frnt];
                    if (modflag2 == 1)
                        timeproc2 += t4;
                    remove_m(m2);
                    m2proc++;
                    (*countm2)--;
                    while (overtime1 <= t4)
                    {
                        insert_m(m1, t1);
                        (*countm1)++;
                        overtime1 += t1;
                        t1 = float_rand(T1_MIN, T1_MAX);
                    }
                    while (overtime2 <= t4)
                    {
                        insert_m(m2, t2);
                        (*countm2)++;
                        overtime2 += t2;
                        t2 = float_rand(T2_MIN, T2_MAX);
                    }
                    wtime1 += overtime1;
                    wtime2 += overtime2;
                    rem1 = overtime1 - t4;
                    rem2 = overtime2 - t4;
                }
                overtime1 = rem1;
                overtime2 = rem2;
            }
            else if ((flagproc == 0 && (*countm1) != 0) ||
                     (flagproc == 1 && (*countm2) != 0))
            {
                if (flagproc == 0)
                {
                    t3 = float_rand(T3_MIN, T3_MAX);
                    if (modflag1 == 0)
                        timeproc1 += m1->qu[m1->frnt];
                    if (modflag1 == 1)
                        timeproc1 += t3;
                    remove_m(m1);
                    m1proc++;
                    (*countm1)--;
                    while (overtime1 <= t3)
                    {
                        insert_m(m1, t1);
                        (*countm1)++;
                        t1 = float_rand(T1_MIN, T1_MAX);
                        overtime1 += t1;
                    }
                    while (overtime2 <= t3)
                    {
                        insert_m(m2, t2);
                        (*countm2)++;
                        t2 = float_rand(T2_MIN, T2_MAX);
                        overtime2 += t2;
                    }
                    wtime1 += overtime1;
                    wtime2 += overtime2;
                    rem1 = overtime1 - t3;
                    rem2 = overtime2 - t3;
                }
                if (flagproc == 1)
                {
                    t4 = float_rand(T4_MIN, T4_MAX);
                    if (modflag2 == 0)
                        timeproc2 += m2->qu[m2->frnt];
                    if (modflag2 == 1)
                        timeproc2 += t4;
                    remove_m(m2);
                    m2proc++;
                    (*countm2)--;
                    while (overtime1 <= t4)
                    {
                        insert_m(m1, t1);
                        (*countm1)++;
                        t1 = float_rand(T1_MIN, T1_MAX);
                        overtime1 += t1;
                    }
                    while (overtime2 <= t4)
                    {
                        insert_m(m2, t2);
                        (*countm2)++;
                        t2 = float_rand(T2_MIN, T2_MAX);
                        overtime2 += t2;
                    }
                    wtime1 += overtime1;
                    wtime2 += overtime2;
                    rem1 = overtime1 - t4;
                    rem2 = overtime2 - t4;
                }
                overtime1 = rem1;
                overtime2 = rem2;
            }
            else if ((*countm1) != 0 && (*countm2) == 0)
            {
                flagproc = 0;
                t3 = float_rand(T3_MIN, T3_MAX);
                if (modflag1 == 0)
                    timeproc1 += m1->qu[m1->frnt];
                if (modflag1 == 1)
                    timeproc1 += t3;
                remove_m(m1);
                m1proc++;
                (*countm1)--;
                while (overtime1 <= t3)
                {
                    insert_m(m1, t1);
                    (*countm1)++;
                    t1 = float_rand(T1_MIN, T1_MAX);
                    overtime1 += t1;
                }
                while (overtime2 <= t3)
                {
                    insert_m(m2, t2);
                    (*countm2)++;
                    t2 = float_rand(T2_MIN, T2_MAX);
                    overtime2 += t2;
                }
                wtime1 += overtime1;
                wtime2 += overtime2;
                rem1 = overtime1 - t3;
                rem2 = overtime2 - t3;
                overtime1 = rem1;
                overtime2 = rem2;
            }
            else if ((*countm1) == 0 && (*countm2) != 0)
            {
                flagproc = 1;
                t4 = float_rand(T4_MIN, T4_MAX);
                if (modflag2 == 0)
                    timeproc2 += m2->qu[m2->frnt];
                if (modflag2 == 1)
                    timeproc2 += t4;
                remove_m(m2);
                m2proc++;
                (*countm2)--;
                while (overtime1 <= t4)
                {
                    insert_m(m1, t1);
                    (*countm1)++;
                    t1 = float_rand(T1_MIN, T1_MAX);
                    overtime1 += t1;
                }
                while (overtime2 <= t4)
                {
                    insert_m(m2, t2);
                    (*countm2)++;
                    t2 = float_rand(T2_MIN, T2_MAX);
                    overtime2 += t2;
                }
                wtime1 += overtime1;
                wtime2 += overtime2;
                rem1 = overtime1 - t4;
                rem2 = overtime2 - t4;
                overtime1 = rem1;
                overtime2 = rem2;
            }
            midlength1 += *countm1;
            midlength2 += *countm2;
        }

    }
    return CORR_END;
}
