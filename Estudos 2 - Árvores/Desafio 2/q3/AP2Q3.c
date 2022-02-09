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
gcc avl.c AP2Q3.c -c ; gcc -o AP2Q3.out avl.o AP2Q3.o ; ./AP2Q3.out
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