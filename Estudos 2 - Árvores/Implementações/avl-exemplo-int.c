#include <stdio.h>
#include <string.h>
#include "avl.h"

int comparInt(const void *a, const void *b) {
    int *n1 = (int*)a;
    int *n2 = (int*)b;
    return *n1 - *n2;
}

void printTreeInt(avl_node_t *tree) {
    int *n;

    if (tree != NULL) {
        n = (int*) tree->item;

        printTreeInt(tree->left);
        printf("%d ", *n);
        printTreeInt(tree->right);
    }
}

/**
 * gcc avl.c avl-exemplo-int.c -c && gcc avl.o avl-exemplo-int.o && ./a.out
 * */
int main() {
    int num[] = {0,1,2,3,4,5,6,7,8,9,10,11,12};

    avl_t *treeInt = avl_alloc( comparInt );

    avl_insert(treeInt, &num[4]);
    avl_insert(treeInt, &num[12]);
    avl_insert(treeInt, &num[2]);
    avl_insert(treeInt, &num[4]);
    avl_insert(treeInt, &num[9]);
    avl_insert(treeInt, &num[3]);
    avl_insert(treeInt, &num[11]);

    printTreeInt(treeInt->root);
    printf("\n");

    int n = 11;
    avl_delete(treeInt, &n);
    
    printTreeInt(treeInt->root);
    printf("\n");

    avl_delete_min(treeInt);
    printTreeInt(treeInt->root);
    printf("\n");

    return 0;
}