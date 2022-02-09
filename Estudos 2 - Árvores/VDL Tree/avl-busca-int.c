#include <stdio.h>
#include <string.h>
#include <time.h>
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
    int n = 1000;
    avl_t *treeInt = avl_alloc( comparInt );

    srand(time(NULL));


    
    
    printTreeInt(treeInt->root);
    printf("\n");

    return 0;
}