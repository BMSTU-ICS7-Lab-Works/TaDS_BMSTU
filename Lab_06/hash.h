#ifndef HASH_H
#define HASH_H

#define HASH_MUL 31
typedef struct hashtab
{
    char *word;
    struct hashtab *next;
}hashtab_t;


hashtab_t* add_end(hashtab_t *head, hashtab_t *elem);
hashtab_t **add_hashtab(hashtab_t **table, hashtab_t *node, char *word, int *hashtable_size);
hashtab_t* create_hash_node(char *word);
hashtab_t **create_table(FILE *f, int hashtable_size);
unsigned int hash(char *, int);
void hashtab_init(hashtab_t *hashtab, int hashtab_size);
void print_table(hashtab_t **table, int len_table);
float count_compare (int count_word, char word[][100], hashtab_t **hashtab,int hashtab_size);
hashtab_t *hashtab_search(hashtab_t **hashtab, char *key, int *amount, int hashtab_size);
hashtab_t **create_table_word(char word[][100], int count_word, int hashtable_size);
#endif // HASH_H
