#ifndef TREE_H
#define TREE_H
typedef struct tnode
{
  char *word;
  int count;
  struct tnode *left;
  struct tnode *right;
}tnode_t;

tnode_t *file_to_tree(FILE *f, tnode_t *root);
tnode_t *addtree(tnode_t *p, char *w);
tnode_t *freemem(tnode_t *tree);
tnode_t *search_in_tree(tnode_t *root, char *key);
float count_compare_tree(int count_word, char word[][100], tnode_t *root);
void showLine(char* c, int p, int s);
void showTree(tnode_t *root, int p, int s);
#endif // TREE_H
