/*
Questão 4 - 2 pontos
Gere uma sequência de 1000 números inteiros aleatórios de 0 a 999. 
Insira a mesma sequência de números em uma árvore AVL e em uma árvore vermelho e preto. 
Em seguida calcule e exiba a altura das duas árvores. 
Repita a execução do seu programa 10 vezes e calcule e apresente as médias das alturas para os dois tipos de árvores.
gcc Tree.c avl.c rbtree.c AP2Q4.c -c ; gcc -o AP2Q4.out Tree.o avl.o rbtree.o AP2Q4.o ; ./AP2Q4.out
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "avl.h"
#include "rbtree.h"
#include "Tree.h"
//#include "queue.h"
#define TAM 999

int avltree_h(avl_node_t *t){
    int l, r;
    if (t == NULL) {
        return 0;
    }
    else {
        l = 1 + avltree_h(t->left);
        r = 1 + avltree_h(t->right);

        if(l > r)
            return l;
        else
            return r;
    }
}

int avltree_hm(avl_node_t *t){
    int n;
    n = avltree_h(t);
    printf("Altura AVL Tree: %d\n", n);
return n;}

int rbtree_h(rbtree_node_t *t){
    int l, r;
    if (t == NULL) {
        return 0;
    }
    else {
        l = 1 + rbtree_h(t->left);
        r = 1 + rbtree_h(t->right);

        if(l > r)
            return l;
        else
            return r;
    }
}

int rbtree_hm(rbtree_node_t *t){
    int n;
    n = rbtree_h(t);
    printf("Altura RB Tree: %d\n", n);
return n;}

int compar(const void *a, const void *b) {
    int *n1 = (int*)a;
    int *n2 = (int*)b;
    return *n1 - *n2;
}

void printint(void *a){
    int n = *((int *)a);
    printf("%d ",n);
}

void rbprintTree(rbtree_node_t *tree) {
    int *n;

    if (tree != NULL) {
        n = (int*) tree->item;

        rbprintTree(tree->left);
        printf("%d ", *n);
        rbprintTree(tree->right);
    }
}

void avlprintTree(avl_node_t *tree) {
    int *n;

    if (tree != NULL) {
        n = (int*) tree->item;

        avlprintTree(tree->left);
        printf("%d ", *n);
        avlprintTree(tree->right);
    }
}

int main(){
    srand(time(NULL));
    int i,n,v[TAM+1];
    int avl,rb;
    rbtree_t *rbtree = rbtree_alloc(compar);
    avl_t *avltree = avl_alloc(compar);
    avl = rb = 0;
for(n = 0; n<10; n++){
    printf("Execução %d:\n",n+1);
        avltree = avl_alloc(compar);
        rbtree = rbtree_alloc(compar);
        for(i = 0; i<=TAM; i++){
            //printf("%d ", rand() % 999);
            v[i] = rand() % 999;
            avl_insert(avltree, &v[i]);
            rbtree_insert(rbtree, &v[i]);
            //printf("v[%d]:%d\n",i,v[i]);
        }
        //printf("i: %d\n", i);

        /*
        avlprintTree(avltree->root);
        printf("AVL Tree\n");
        rbprintTree(rbtree->root);
        printf("RB Tree\n");

        avltree_print_level_main(avltree->root,printint);printf("AVL Tree\n");
        rbtree_print_level_main(rbtree->root,printint);printf("RB Tree\n");
        */
        avl+= avltree_hm(avltree->root);
        rb += rbtree_hm(rbtree->root);
}

printf("Media altura AVL: %d\n",avl/10);
printf("Media altura RBTree: %d\n",rb/10);


avl_free(avltree);
rbtree_free(rbtree);
return 0;}