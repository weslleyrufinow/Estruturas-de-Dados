#include <stdio.h>
#include <string.h>
#include "rbtree.h"

int comparStr(const void *a, const void *b) {
    char *s1 = (char*)a;
    char *s2 = (char*)b;
    return strcmp(s1, s2);
}

void printTreeStr(rbtree_node_t *tree) {
    char *s;

    if (tree != NULL) {
        s = (char*) tree->item;

        printTreeStr(tree->left);
        printf("%s ", s);
        printTreeStr(tree->right);
    }
}

/**
 * gcc rbtree.c rbtree-exemplo-str.c -c && gcc rbtree.o rbtree-exemplo-str.o && ./a.out
 * */
int main() {
    char *str[] = {"Jan","Fev","Mar","Abr","Mai","Jun","Jul"};

    rbtree_t *treeStr = rbtree_alloc( comparStr );

    rbtree_insert(treeStr, str[2]);
    rbtree_insert(treeStr, str[0]);
    rbtree_insert(treeStr, str[5]);
    rbtree_insert(treeStr, str[1]);
    rbtree_insert(treeStr, str[6]);
    rbtree_insert(treeStr, str[3]);
    rbtree_insert(treeStr, str[4]);

    printTreeStr(treeStr->root);
    printf("\n");

    char *s = "Jul";
    rbtree_delete(treeStr, s);

    printTreeStr(treeStr->root);
    printf("\n");

    rbtree_delete_min(treeStr);
    
    printTreeStr(treeStr->root);
    printf("\n");

    return 0;
}