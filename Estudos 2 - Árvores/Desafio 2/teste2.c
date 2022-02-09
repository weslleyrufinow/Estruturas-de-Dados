/*
Questão 3
Escreva um programa que simule o controle de uma pista de decolagem de aviões em um aeroporto. 
Neste programa, o usuário deve ser capaz de realizar as seguintes tarefas: 
(a) Listar o número de aviões aguardando na pista de decolagem; 
(b) Autorizar a decolagem do primeiro avião da fila; 
(c) Adicionar um avião à fila de espera; 
(d) Listar todos os aviões na fila de espera; 
(e) Listar as características do primeiro avião da fila.
    Considere que os aviões possuem um nome e um número inteiro como identificador. 
    Adicione outras características conforme achar necessário.
gcc avl.c teste2.c -c ; gcc -o teste2.out avl.o teste2.o ; ./teste2.out
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "avl.h"

void menu(){
    printf("\n");
    printf("1.Listar produtos\n");
    printf("2.Adicionar produtos\n");
    printf("3.Remover produtos\n");
    printf("4.Sair\n");
    printf("\n");
}

typedef struct produto{
    char nome[100];
    char versao[100];
    double preco;
} produto;

void printstruct(void *tree) {
    produto c = *( (produto*) tree); 
    printf("(%s, %s, %.2f)\n", c.nome, c.versao, c.preco);
}

void printprodTree(avl_node_t *tree) {
    void *n;
    if (tree != NULL) {
        n = (void *) tree->item;

        printprodTree(tree->left);
        printstruct(n);
        printprodTree(tree->right);
    }
}

void remover_produtos(avl_t *t, FILE *arq){

    //avl_delete(t);
    //se retornar null, nao foi encontrado
    fclose(arq);
}

void adicionar_produtos(avl_t *t, FILE *arq){
    arq = fopen("software","ab");
    produto *tmp = malloc(sizeof(produto));
    if(arq == NULL){
        printf("Erro na abertura\n");
    }else{
        setbuf(stdin,NULL);
        printf("Nome do produto:\n");
        scanf("%[^'\n']s",tmp->nome);

        setbuf(stdin,NULL);
        printf("Versao do produto:\n");
        scanf("%[^'\n']s",tmp->versao);
        setbuf(stdin,NULL);

        printf("Preco do produto:\n");
        scanf("%lf",&tmp->preco);
        setbuf(stdin,NULL);
        fwrite(avl_insert(t,tmp), sizeof(t), 1, arq);
        //fwrite(tmp, sizeof(produto),1, arq);

    }
fclose(arq);
menu();
}

void listar_produtos(avl_t *t,FILE *arq){
    arq = fopen("software","rb");
    produto *tmp;
    if(arq == NULL){
        printf("Erro na abertura\n");
        menu();
    }else{
        printf("     NOME      VERSAO  PRECO\n");
        while (!feof(arq)){
            fread(tmp,sizeof(produto),1,arq);
            printf("%s ",tmp->nome);
            printf("%s ",tmp->versao);
            printf("%.2f\n",tmp->preco);
        }
        printf("\n");
    }
fclose(arq);
}

int compar(const void *a, const void *b) {
    int n;
    produto *c1 = (produto*)a;
    produto *c2 = (produto*)b;
    n = strcmp(c1->nome, c2->nome);
    if(n == 0){
        n = strcmp(c1->versao, c2->versao);   
    }
return n;}

int main(){
    avl_t *t = avl_alloc(compar);
    FILE *arq;
    int but = 0;

    menu();
do{
    printf("Agurdando escolha: ");
    scanf("%d",&but);
    system("clear");
    switch (but){
    case 1:
        menu();
        printf("Listando Produtos\n");
        listar_produtos(t,arq);
        printf("\n");
        break;
    case 2:
        menu();
        printf("Qual produto a ser adicionado?\n");
        adicionar_produtos(t,arq);
        printf("\n");
        break;
    case 3:
        menu();
        printf("Qual produto a ser removido?\n");
        remover_produtos(t,arq);
        printf("\n");
        break;
    case 4:
        menu();
        printf("Saindo...\n");
        break;
    default:
        menu();
        printf("opcao invalida\n");
        but = 4;
        break;
    }
}while(but != 4);


avl_free(t);
fclose(arq);
return 0;}