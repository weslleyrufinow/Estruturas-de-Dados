#include <stdio.h>
#include <string.h>
#include "rbtree.h"

int comparInt(const void *a, const void *b) {
    int *n1 = (int*)a;
    int *n2 = (int*)b;
    return *n1 - *n2;
}

void printTreeInt(rbtree_node_t *tree) {
    int *n;

    if (tree != NULL) {
        n = (int*) tree->item;

        printTreeInt(tree->left);
        printf("%d ", *n);
        printTreeInt(tree->right);
    }
}

/**
 * gcc rbtree.c rbtree-exemplo-int.c -c && gcc rbtree.o rbtree-exemplo-int.o && ./a.out
 * */
int main() {
    int num[] = {0,1,2,3,4,5,6,7,8,9,10,11,12};

    rbtree_t *treeInt = rbtree_alloc( comparInt );

    rbtree_insert(treeInt, &num[4]);
    rbtree_insert(treeInt, &num[12]);
    rbtree_insert(treeInt, &num[2]);
    rbtree_insert(treeInt, &num[4]);
    rbtree_insert(treeInt, &num[9]);
    rbtree_insert(treeInt, &num[3]);
    rbtree_insert(treeInt, &num[11]);

    printTreeInt(treeInt->root);
    printf("\n");

    int n = 11;
    rbtree_delete(treeInt, &n);
    
    printTreeInt(treeInt->root);
    printf("\n");

    rbtree_delete_min(treeInt);
    printTreeInt(treeInt->root);
    printf("\n");

    return 0;
}