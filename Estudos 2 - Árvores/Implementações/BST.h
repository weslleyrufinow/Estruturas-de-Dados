#include <stdio.h>
#include <stdlib.h>

typedef struct BST BST;

BST  *BST_create(int (*compar)(void*, void*));
void  BST_destroy(BST *bst);
void  BST_insert(BST *bstree, void *value);
void *BST_search(BST *bst, void *value);
void *BST_remove(BST *bst, void *value);
void  BST_print(BST *bst, void (*print)(void*));
