#include <stdio.h>
#include <string.h>
#include "avl.h"

int comparStr(const void *a, const void *b) {
    char *s1 = (char*)a;
    char *s2 = (char*)b;
    return strcmp(s1, s2);
}

void printTreeStr(avl_node_t *tree) {
    char *s;

    if (tree != NULL) {
        s = (char*) tree->item;

        printTreeStr(tree->left);
        printf("%s ", s);
        printTreeStr(tree->right);
    }
}

/**
 * gcc avl.c avl-exemplo-str.c -c && gcc avl.o avl-exemplo-str.o && ./a.out
 * */
int main() {
    char *str[] = {"Jan","Fev","Mar","Abr","Mai","Jun","Jul"};

    avl_t *treeStr = avl_alloc( comparStr );

    avl_insert(treeStr, str[2]);
    avl_insert(treeStr, str[0]);
    avl_insert(treeStr, str[5]);
    avl_insert(treeStr, str[1]);
    avl_insert(treeStr, str[6]);
    avl_insert(treeStr, str[3]);
    avl_insert(treeStr, str[4]);

    printTreeStr(treeStr->root);
    printf("\n");

    char *s = "Jul";
    avl_delete(treeStr, s);

    printTreeStr(treeStr->root);
    printf("\n");

    avl_delete_min(treeStr);
    
    printTreeStr(treeStr->root);
    printf("\n");

    return 0;
}