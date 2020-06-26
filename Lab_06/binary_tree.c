#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tree.h"

tnode_t *file_to_tree(FILE *f, tnode_t *root)
{
    rewind(f);
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
                root=addtree(root,s);
            i = 0;
        }
        else
        {
            i++;
        }
    }
    free(s);
    return root;
}

tnode_t *addtree(tnode_t *p, char *w)
{
    int cond;
    if (p == NULL)
    {
        p = (tnode_t*)malloc(sizeof(tnode_t));
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    }
    else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;
    else if (cond < 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);
    return p;
}

tnode_t *freemem(tnode_t *tree)
{
    if (tree!=NULL)
    {
        freemem(tree->left);
        freemem(tree->right);
        free(tree);
    }
    return NULL;
}

tnode_t *search_in_tree(tnode_t *root, char *key)
{
    if ((root == NULL) || (strcmp(root -> word,key)==0))
        return root;
    if (strcmp(key, root -> word)<0)
        return search_in_tree(root -> left, key);
    else return search_in_tree(root -> right, key);
}

void showLine(char* c, int p, int s)
{
    int t=s;
    for(int i = 0; i < p; i++)
    {
        printf(t&1 ? "|  " : "   ");
        t/=2;
    }
    printf(c);
}

void showTree(tnode_t *root, int p, int s)
{
    if (root == NULL)
        return;
    printf("%s", root->word);
    printf("\n");
    if (root->left != NULL)
    {
        showLine("|\n", p, s);
        showLine("L: ", p, s);
        showTree(root->left, p+1, s + ((root->right == NULL ? 0 : 1)<<p));
    }
    if (root->right != NULL)
    {
        showLine("|\n", p, s);
        showLine("R: ", p, s);
        showTree(root->right, p+1, s);
    }
}

tnode_t *search(tnode_t *root, char *key, int *amount)
{
    if ((root == NULL) || (strcmp(root -> word,key)==0))
    {
        (*amount)++;
        return root;
    }
    (*amount)++;
    if (strcmp(key, root -> word)<0)
        return search(root -> left, key, amount);
    else return search(root -> right, key, amount);
}

float count_compare_tree(int count_word, char word[][100], tnode_t *root)
{
    int amount=0;
    for (int i=0; i<count_word;i++)
    {
        search(root, word[i], &amount);
    }
    return (1.0*amount/count_word);
}
