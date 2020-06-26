#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"

hashtab_t* add_end(hashtab_t *head, hashtab_t *elem)
{
    hashtab_t *cur = head;
    if (!head)
    {
        return elem;
    }
    for (; cur->next; cur = cur->next)
    {
        if (!strcmp(cur->word, elem->word))
        {
            return head;
        }
    }
    if (!strcmp(cur->word, elem->word))
    {
        return head;
    }
    cur->next = elem;
    return head;
}

hashtab_t** add_hashtab(hashtab_t **table, hashtab_t *node, char *word, int *hashtable_size)
{
    int index = hash(word,*hashtable_size);
    table[index] = add_end(table[index], node);
    return table;
}

hashtab_t* create_hash_node(char *word)
{
    hashtab_t *node = malloc(sizeof(hashtab_t));
    if (node && word)
    {
        node->word = strdup(word);
        node->next = NULL;
    }
    return node;
}
void print_table(hashtab_t **table, int len_table)
{
    for (int i = 0; i < len_table; i++)
    {
        printf("%d ", i);
        hashtab_t *cur= table[i];
        for ( ; cur; cur = cur->next)
        {
            printf (" -> %s", cur->word);
        }
        printf(" -> NULL\n");
    }
    printf("\n");
}

hashtab_t *hashtab_search(hashtab_t **hashtab, char *key, int *amount, int hashtab_size)
{
    int index;
    hashtab_t *node;
    index = hash(key,hashtab_size);
    for (node = hashtab[index]; node != NULL; node = node->next)
    {
        (*amount)++;
        if (strcmp(node->word, key) == 0)
            return node;
    }
    return NULL;
}

float count_compare (int count_word, char word[][100], hashtab_t **hashtab,int hashtab_size)
{
    int amount=0;
    for (int i=0; i<count_word;i++)
    {
        hashtab_search(hashtab,word[i],&amount,hashtab_size);
    }
    return (1.0*amount/count_word);
}
hashtab_t **create_table(FILE *f, int hashtable_size)
{
    rewind(f);
    hashtab_t **table = NULL;
    hashtab_t *node;
    table = calloc(hashtable_size, sizeof(hashtab_t*));
    int i = 0;
    char *s = calloc(100, sizeof(char));
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
                node = create_hash_node(s);
                table = add_hashtab(table, node, s, &hashtable_size);
            }
            i = 0;

        }
        else
        {
            i++;
        }
    }
    free(s);

    return table;
}

hashtab_t **create_table_word(char word[][100], int count_word, int hashtable_size)
{
    hashtab_t **table = NULL;
    hashtab_t *node;
    table = calloc(hashtable_size, sizeof(hashtab_t*));
    for (int i=0; i<count_word; i++)
    {
        node = create_hash_node(word[i]);
        table = add_hashtab(table, node, word[i], &hashtable_size);
    }
    return table;
}

unsigned int hash(char *s, int hashtab_size)
{
    unsigned int h = 0;
    char *p;
    for (p = s; *p != '\0'; p++)
        h = h * HASH_MUL + (unsigned int)*p;
    return h % hashtab_size;
}
