/*
Questão 2 - 2 pontos
Escreva um programa que construa uma árvore de busca binária
com todas as palavras incluídas em um arquivo de texto 
e imprima em ordem alfabética todas as palavras do arquivo. Link para o arquivo: Names.txt
gcc avl.c AP2Q2.c -c ; gcc -o AP2Q2.out avl.o AP2Q2.o ; ./AP2Q2.out
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "avl.h"

void printTree(avl_node_t *tree) {
    char *s;

    if (tree != NULL) {
        s = (char*) tree->item;

        printTree(tree->left);
        printf("%s ", s);
        printTree(tree->right);
    }
}

int compar(const void *a, const void *b){
    char *c1 = (char*)a;
    char *c2 = (char*)b;
    return strcmp(c1, c2);
}

int main(){
    avl_t *t = avl_alloc(compar);
    FILE *arq;
    char linha[100];
    char *nome;

    arq = fopen("names.txt","r");
    if(arq == NULL){
        printf("Erro na abertura\n");
    }else{
        while (!feof(arq)){
            nome = calloc(100,1);
            fscanf(arq,"%[^\n]%*c", nome);
            avl_insert(t,nome);
        }
        
    }
printTree(t->root);
printf("\n");

avl_free(t);
fclose(arq);
return 0;}