#include <stdio.h>
#include <stdlib.h>

typedef struct Tree Tree;

Tree *Tree_create (void *value, Tree *left, Tree *right);
void Tree_destroy(Tree *tree);

void *Tree_getValue(Tree *tree);
void *Tree_getLeft(Tree *tree);
void *Tree_getRight(Tree *tree);

void *Tree_setValue(Tree *tree, void *value);
void *Tree_setLeft (Tree *tree, void *value);
void *Tree_setRight(Tree *tree, void *value);

void Tree_print(Tree *tree, void (*print)(void *));