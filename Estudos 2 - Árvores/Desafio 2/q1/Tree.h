#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "avl.h"
#include "rbtree.h"
#include "avl.h"
#include "queue.h"


typedef struct Tree {
    void *value;
    struct Tree *left;
    struct Tree *right;
} Tree;

Tree *tree_create(void *value, Tree *left, Tree *right);
void  tree_destroy(Tree *tree);

void print_char(void *a);
int compar_char(void *a, void *b);

Tree *tree_find_main(Tree *tree, void *value, int (*compar)(void*,void*), void (*print_char)(void*));
Tree *tree_find(Tree *tree, void *value, int (*compar)(void*,void*));

void tree_print_main(Tree *tree, void (*print)(void *));
void tree_print(Tree *tree, void (*print)(void *));

void tree_inOrder(Tree *tree, void (*process)(void *));
void tree_preOrder(Tree *tree, void (*process)(void *));
void tree_postOrder(Tree *tree, void (*process)(void *));

//void tree_queue(Tree *tree, Queue *q);

void tree_print_level_main(Tree *bst, void (*print)(void *));
void tree_print_level(Tree *bst, void (*print)(void *), int level, char c);

void tree_height_main(Tree *tree);
int tree_height(Tree *tree);

void tree_eval_main(Tree *t);
int tree_eval(Tree *t);

