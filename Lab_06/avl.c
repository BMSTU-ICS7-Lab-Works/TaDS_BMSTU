#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "avl.h"

void avltree_free(avl_t *tree)
{
    if (tree == NULL)
        return;
    avltree_free(tree->left);
    avltree_free(tree->right);
    free(tree);
}
avl_t *search_in_tree_avl(avl_t *root, char *key)
{
    if ((root == NULL) || (strcmp(root ->word,key)==0))
        return root;
    if (strcmp(key, root -> word)<0)
        return search_in_tree_avl(root -> left, key);
    else return search_in_tree_avl(root -> right, key);
}

void avlTree(avl_t *root, int p, int s)
{
    if (root == NULL)
        return;
    printf("%s", root->word);
    printf("\n");
    if (root->left != NULL)
    {
        showLine("|\n", p, s);
        showLine("L: ", p, s);
        avlTree(root->left, p+1, s + ((root->right == NULL ? 0 : 1)<<p));
    }
    if (root->right != NULL)
    {
        showLine("|\n", p, s);
        showLine("R: ", p, s);
        avlTree(root->right, p+1, s);
    }
}

avl_t *file_to_avl(FILE *f, avl_t *root)
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
                root=avltree_add(root,s);
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

int avltree_height(avl_t *tree)
{
    return (tree != NULL) ? tree->height : -1;
}

int avltree_balance(avl_t *tree)
{
    return avltree_height(tree->left)-avltree_height(tree->right);
}

int max_t(int a, int b)
{
    if (a>=b)
        return a;
    else
        return b;
}

avl_t *avltree_right_rotate(avl_t *tree)
{
    avl_t *left;
    left = tree->left;
    tree->left = left->right;
    left->right = tree;
    tree->height = max_t(avltree_height(tree->left),avltree_height(tree->right)) + 1;
    left->height = max_t(avltree_height(left->left), tree->height) + 1;
    return left;
}

avl_t *avltree_left_rotate(avl_t *tree)
{
    avl_t *right;
    right = tree->right;
    tree->right = right->left;
    right->left = tree;
    tree->height = max_t( avltree_height(tree->left), avltree_height(tree->right)) + 1;
    right->height = max_t( avltree_height(right->right), tree->height) + 1;
    return right;
}

avl_t *avltree_leftright_rotate(avl_t *tree)
{
    tree->left = avltree_left_rotate(tree->left);
    return avltree_right_rotate(tree);
}

avl_t *avltree_rightleft_rotate(avl_t *tree)
{
    tree->right = avltree_right_rotate(tree->right);
    return avltree_left_rotate(tree);
}

avl_t *avltree_add(avl_t *tree, char *w)
{
    int cond;
    if (tree == NULL)
    {
        tree = (avl_t*)malloc(sizeof(avl_t));
        tree->word = strdup(w);
        tree->count = 1;
        tree->height = 0;
        tree->left = tree->right = NULL;
    }
    cond = strcmp(w, tree->word);
    if (cond < 0)
    { /* Insert into left subtree*/
        tree->left = avltree_add(tree->left, w);
        if (avltree_height(tree->left) - avltree_height(tree->right) == 2)
        { /* Subtreeis unbalanced */
            if (strcmp(w,tree->left->word)<0)
            { /* Left leftcase */
                tree = avltree_right_rotate(tree);
            }
            else
            { /* Left right case */
                tree = avltree_leftright_rotate(tree);
            }
        }
    }
    else if (cond>0)
    { /* Insert into right subtree*/
        tree->right = avltree_add(tree->right, w);
        if (avltree_height(tree->right) - avltree_height(tree->left) == 2)
        { /* Subtreeis unbalanced */
            if (strcmp(w,tree->right->word)>0)
            { /* Right rightcase */
                tree = avltree_left_rotate(tree);
            }
            else
            { /* Right left case */
                tree = avltree_rightleft_rotate(tree);
            }
        }
    }
    tree->height = max_t(avltree_height(tree->left),avltree_height(tree->right) ) + 1;
    return tree;
}

avl_t *search_avl(avl_t *root, char *key, int *amount)
{
    if ((root == NULL) || (strcmp(root -> word,key)==0))
    {
        (*amount)++;
        return root;
    }
    (*amount)++;
    if (strcmp(key, root -> word)<0)
        return search_avl(root -> left, key, amount);
    else return search_avl(root -> right, key, amount);
}

float count_compare_avl(int count_word, char word[][100], avl_t *root)
{
    int amount=0;
    for (int i=0; i<count_word;i++)
    {
        search_avl(root, word[i], &amount);
    }
    return (1.0*amount/count_word);
}
