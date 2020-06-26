#ifndef AVL_H
#define AVL_H

typedef struct avltree
{
    char *word;
    int count;
    int height;
    struct avltree *left;
    struct avltree *right;
}avl_t;

avl_t *file_to_avl(FILE *f, avl_t *root);
avl_t *avltree_add(avl_t *tree, char *w);
void showLine(char* c, int p, int s);
void avlTree(avl_t *root, int p, int s);
avl_t *search_in_tree_avl(avl_t *root, char *key);
float count_compare_avl(int count_word, char word[][100], avl_t *root);

#endif // AVL_H
