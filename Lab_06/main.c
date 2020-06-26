#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "hash.h"
#include "tree.h"
#include <time.h>
#include "avl.h"

void print_interface(void)
{
    puts("******************************");
    puts("Select menu item");
    puts("1: Print Binary tree");
    puts("2: Print AVL");
    puts("3: Seek word in Tree");
    puts("4: Seek word in AVL");
    puts("5: Create HashTable");
    puts("6: Print HashTable");
    puts("7: Seek word in HashTable");
    puts("8: Efficiency");
    puts("0: EXIT");
    printf("Your choice: ");
}

void file_to_word(FILE *f, char word[][100], int *count)
{
    rewind(f);
    int i = 0;
    char s[100];
    while (!feof(f))
    {
        fscanf(f, "%c", &s[i]);
        if (s[i] >= 'A' && s[i] <= 'Z')
            s[i] += 'z' - 'Z';
        if (s[i] == ' ' || s[i] == '\n' || s[i] == ',' || s[i] == '.' ||
                s[i] == ':' || s[i] == '?' || s[i]=='!' || s[i]==';' || feof(f))
        {
            s[i] = '\0';
            if (i != 0)
            {
                int flag=0;
                for (int i = 0; i<*count; i++)
                    if (!strcmp(s,word[i]))
                    {
                        flag=1;
                        break;
                    }
                if (!flag)
                {
                    strcpy(word[*count],s);
                    (*count)++;
                }

                i = 0;
            }
        }
        else
        {
            i++;
        }
    }
}

void time_for_tree(char word[][100], int count_word, tnode_t *root)
{
   for (int i=0; i<count_word; i++)
       search_in_tree(root, word[i]);
}

void time_for_avl(char word[][100], int count_word)
{
   avl_t *root = NULL;
   for (int i=0; i<count_word; i++)
       root=avltree_add(root, word[i]);
}

void time_for_hash(char word[][100], int count_word)
{
    hashtab_t **hashtab=NULL;
    int hashtab_size=61;
    hashtab=create_table_word(word,count_word,hashtab_size);
    hashtab[0]=NULL;
}

void time_for_file(char word[][100],int count_word)
{
    FILE *f1=fopen("writing.txt","w");
    for (int i=0; i<count_word;i++)
        fprintf(f1,"%s ",word[i]);
    fclose(f1);
}
void time_for_hash_with_restruct(char word[][100], int count_word)
{
    hashtab_t **hashtab=NULL;
    int hashtab_size=11;
    float count_com=2,test_count_com;
    while(1)
    {
        if (hashtab_size%2==0)
            hashtab_size++;
        hashtab=create_table_word(word,count_word,hashtab_size);
        test_count_com=count_compare(count_word, word, hashtab, hashtab_size);
        if (test_count_com < count_com || fabs(test_count_com-count_com)<0.000001)
            break;
        hashtab_size++;
    }
}

int search_in_file(FILE *f, char *word, int *amount)
{
    rewind(f);
    int i = 0;
    char *s = calloc(100, sizeof(char));
    while (!feof(f))
    {
        fscanf(f, "%c", &s[i]);
        if (s[i] == ' ' || s[i] == '\n' || s[i] == ',' || s[i] == '.' || feof(f))
        {
            s[i] = '\0';
            if (strcmp(s, " ") != 0 && strcmp(s, "\n") != 0 && i != 0)
            {
                *amount = *amount + 1;
                if (strcmp(word, s) == 0)
                {
                    return 1;
                }
            }
            i = 0;

        }
        else
        {
            i++;
        }
    }
    free(s);
    return -1;
}

float count_compare_file(int count_word, char word[][100], FILE *f)
{
    int amount=0;
    for (int i=0; i<count_word;i++)
    {
        search_in_file(f, word[i], &amount);
    }
    return (1.0*amount/count_word);
}
void effictive()
{
    time_t start, end;
    char word[140][100];
    int count_word=0;
    FILE *f = fopen("efficiency.txt", "r");
    file_to_word(f, word, &count_word);
    printf("Count words: %d\n",count_word);
    puts("\nEFFICIENCY TABLE");
    puts("-----|   TIME SEEKING  |  SIZE  |   COMPARE  |");

    start=clock();
    for (int i=0; i<1000; i++)
        count_compare_file(count_word, word, f);
    end=clock();
    double time_res_file= ((double)(end - start) / CLOCKS_PER_SEC);
    FILE *f1=fopen("writing.txt","w");
    for (int i=0; i<count_word;i++)
        fprintf(f1,"%s ",word[i]);
    fclose(f1);
    f1=fopen("writing.txt","r");
    printf("FILE |   %4.6lfE-3   | %6I64d | %10lf |\n",time_res_file/count_word, (size_t)875,
           count_compare_file(count_word, word, f1));
    tnode_t *root = NULL;
    rewind(f);
    root = file_to_tree(f, root);
    start=clock();
    for (int i=0; i<1000; i++)
        count_compare_tree(count_word, word, root);
    end=clock();
    double time_res_tree = ((double)(end - start) / CLOCKS_PER_SEC);
    printf("TREE |   %4.6lfE-3   | %6I64d | %10lf |\n",time_res_tree/count_word, sizeof(tnode_t)*count_word,
           count_compare_tree(count_word, word, root));
    avl_t *avl = NULL;
    rewind(f);
    avl = file_to_avl(f, avl);
    start=clock();
    for (int i=0; i<1000; i++)
        count_compare_avl(count_word, word, avl);
    end=clock();
    double time_res_avl = ((double)(end - start) / CLOCKS_PER_SEC);
    printf("AVL  |   %4.6lfE-3   | %6I64d | %10lf |\n",time_res_avl/count_word, sizeof(avl_t)*count_word,
           count_compare_avl(count_word, word, avl));

    rewind(f);
    hashtab_t **hashtab=NULL;
    int hashtab_size=61;
    hashtab=create_table_word(word,count_word,hashtab_size);
    start=clock();
    for (int i=0; i<1000; i++)
        count_compare(count_word, word, hashtab, hashtab_size);
    end=clock();
    double time_res_hash = ((double)(end - start) / CLOCKS_PER_SEC);
    int count_null=0;
    for (int i=0; i<hashtab_size;i++)
        if (hashtab[i]==NULL)
            count_null++;
    printf("HASH |   %4.6lfE-3   | %6I64d | %10lf |\n",time_res_hash/count_word, sizeof(hashtab_t)*(count_word+count_null),
           count_compare(count_word, word, hashtab, hashtab_size));
    fclose(f1);
    fclose(f);
}

int main()
{
    puts("This program demonstrates how to work with DDP, AVL and hash-table");
    tnode_t *root = NULL;
    hashtab_t **hashtab=NULL;
    float count_com;
    char word[140][100];
    int count_word=0;
    int hashtab_size;
    avl_t *avl = NULL;
    FILE *f = fopen("test.txt", "r+");
    file_to_word(f, word,&count_word);
    //int count_word_hash=count_word;
    printf("count word in file %d\n",count_word);
    root=file_to_tree(f, root);
    avl=file_to_avl(f, avl);
    int choice;
    while (1)
    {
        print_interface();
        scanf("%d", &choice);
        printf("\n");
        switch (choice)
        {
            case 0:
                return 0;
            case 1:
            {
                if (root)
                    showTree(root,0,0);
                else
                    puts("NULL");
                break;
            }
            case 2:
            {
                if (avl)
                    avlTree(avl,0,0);
                else
                    puts("NULL");
                break;
            }
            case 3:
            {
                char word_dop[100];
                printf("input word: ");
                scanf("%s", word_dop);
                if (search_in_tree(root, word_dop) == NULL)
                {
                    puts("This word is not in the tree");
                }
                else
                    puts("Word was found!");
                break;
            }
            case 4:
            {
                char word_dop[100];
                printf("input word: ");
                scanf("%s", word_dop);
                if (search_in_tree_avl(avl, word_dop) == NULL)
                {
                    puts("This word is not in the AVL");
                }
                else
                    puts("Word was found!");
                break;
            }
            case 5:
            {
                float test_count_com;
                hashtab_size = 11;
                printf("input the average number of comparisons: ");
                scanf("%f",&count_com);
                printf("please wait table creating...\n");
                while(1)
                {
                    if (hashtab_size%2==0)
                        hashtab_size++;
                    hashtab=create_table(f,hashtab_size);
                    test_count_com=count_compare(count_word, word, hashtab, hashtab_size);
                    if (test_count_com < count_com || fabs(test_count_com-count_com)<0.000001)
                        break;
                    hashtab_size++;
                }
                puts("TABLE WAS CREATED");
                printf("average number of comparison %f\n",test_count_com);
                break;
            }
            case 6:
            {
                if (hashtab==NULL)
                {
                    puts("HASH TABLE NOT CREATED");
                    break;
                }
                print_table(hashtab,hashtab_size);
                break;
            }
            case 7:
            {
                if (hashtab==NULL)
                {
                    puts("HASH TABLE NOT CREATED");
                    break;
                }
                char word_dop[100];
                int t=0;
                printf("input word: ");
                scanf("%s", word_dop);
                if (hashtab_search(hashtab, word_dop, &t, hashtab_size)==NULL)
                {
                    puts("This word is not in the hashtable");
                }
                else
                    puts("Word was found!");
                break;
            }
            case 8:
            {
            //int t = 0;
            /*
                float time1 = clock();
                char s[6];
                strcpy(s, "malls");
                hashtab_search(hashtab, s, &t, hashtab_size);
                float time2 = clock();
                printf("%f\n", time2 - time1);
                */
                effictive();
                puts("");
                break;
            }
            case 9:
            {
                avltree_add(avl, "bbe");
            }

            default:
                puts("incorrect choice");
                break;
        }
    }
    return 0;
}
