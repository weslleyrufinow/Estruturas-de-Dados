/*
Questão 3 - 3 pontos
Implemente um programa baseado em menu para gerenciar uma loja de software. 
Todas as informações sobre o software disponível são armazenadas em um arquivo chamado "software". 
Essas informações incluem NOME, VERSÃO, e PREÇO de cada pacote. 
Quando chamado, o programa cria automaticamente uma árvore de pesquisa binária 
com um nó correspondente a um pacote de software e inclui como sua chave o NOME do pacote E sua VERSÃO. 
O único acesso às informações armazenadas no software deve ser por meio desta árvore. 
O programa deve permitir que o arquivo e a árvore sejam atualizados 
quando novos pacotes de software chegarem à loja e quando alguns pacotes forem vendidos. 
A árvore é atualizada da maneira usual. 
Os pacotes podem ser listados e devem ser exibidos em ordem alfabética e da menor versão para a maior. 
A imagem apresenta um exemplo de listagem.
gcc avl.c rbtree.c AP2Q3.c -c ; gcc -o AP2Q3.out avl.o rbtree.o AP2Q3.o ; ./AP2Q3.out
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include "avl.h"
typedef struct produto{
    char *nome;
    char *versao;
    float preco;
} produto;

int compar(const void *a, const void *b) {
    int n;
    produto *c1 = (produto*)a;
    produto *c2 = (produto*)b;
    n = strcmp(c1->nome, c2->nome);
    if(n == 0){
        n = strcmp(c1->versao, c2->versao);   
    }
return n;}

void printstruct(void *tree) {
    produto c = *( (produto*) tree); 
    printf("(%s, %s, %.2f)\n", c.nome, c.versao, c.preco);
}

void printprodTree(avl_node_t *tree) {
    produto *c; 
    if (tree != NULL) {
        c = (produto*)tree->item;
        
        printprodTree(tree->left);
        printf("(%s, %s, %.2f)\n", c->nome, c->versao, c->preco);
        printprodTree(tree->right);
    }
}
int main(){
    int i;
    avl_t *t = avl_alloc(compar);
    FILE *arq;

    arq = fopen("software.txt","r");

    if(arq == NULL){
        printf("Erro na abertura\n");
    }else{
        while (!feof(arq)){
            nome = calloc(100,1);
            fscanf(arq,"%[^\n]%*c", nome);
            avl_insert(t,nome);
        }
        
    }

//printprodTree(t->root);
//printf("\n");

avl_free(t);
fclose(arq);
return 0;}