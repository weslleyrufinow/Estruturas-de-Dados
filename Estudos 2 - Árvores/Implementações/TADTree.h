#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
#include "Queue.h"

typedef struct Tree Tree;

Tree *tree_create (void *value, Tree *left, Tree *right);
void tree_destroy(Tree *tree);

void tree_preOrder(Tree *tree,void (*process)(void *));
void tree_postOrder(Tree *tree,void (*process)(void *));
void tree_inOrder(Tree *tree,void (*process)(void *));
void tree_queue(Tree *tree, Queue *queue);


void print(void *letra);
void res(Tree *tree, Queue *q);
void *op(void *opr, Queue *q);
void proccess(void *value, Queue *q);

void tree_print_main(Tree *bst, void (*print)(void *));
void tree_print_level(Tree *bst, void (*print)(void *), int level, char c);

void tree_print_setas(Tree *tree, void (*print)(void *));
int  tree_height(Tree *t);

int compar(void *v,void *k);
void *tree_find(Tree *t,void *key, int (compar)(void *, void *));

