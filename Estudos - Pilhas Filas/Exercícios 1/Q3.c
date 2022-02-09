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
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Queue.h"
#define TAM 3
struct aviao{
    int id;
    char nome[20];
};
typedef struct aviao aviao;

void menu(){
    printf("\n");
    printf("1.Numero de avioes aguardando decolagem\n");
    printf("2.Autorizar a decolagem do primeiro da fila\n");
    printf("3.Adicionar um aviao a fila\n");
    printf("4.Listar avioes na fila\n");
    printf("5.Listar caracteristicas do 1 aviao\n");
    printf("6.Sair\n");
    printf("\n");
}

void print( void *element){
    aviao *aux;
    aux = ((aviao *)element);
    printf("Nome: %s |ID: %d\n",aux->nome,aux->id);
}

int aguardando (Queue *pista){
    int a = Queue_cont(pista);
    return (a);}

void autorizar (Queue *pista){
    void *aux;
    int b = Queue_cont(pista);
    if(b == 0){
        printf("Pista vazia\n");
    }else{
        aux = Queue_pop(pista);
    }

}

void listar_avioes (Queue *pista){
    int b = Queue_cont(pista);
    if(b == 0){
        printf("Pista vazia\n");
    }else{
        Queue_print(pista,print);
    }
}

void listar_aviao (Queue *pista){
    void *a = Queue_begin(pista);
    int b = Queue_cont(pista);
    if(b == 0){
        printf("Pista vazia\n");
    }else{
        print(a);
    }
}

void add_aviao(Queue *pista){
    struct aviao *aux;
    aux = (struct aviao *)malloc(sizeof(struct aviao));
    char nomeaux[20];
    int c=0,i,a = aguardando(pista);
    if(a == TAM){
        printf("Pista de decolagem cheia\n");
    }else{
        for(i=0 ; i<20;i++)
            nomeaux[i] = '\0';

        printf("ID do novo aviao:\n");
        scanf("%d",&i);
        printf("Nome do novo aviao:\n");
        setbuf(stdin,NULL);
        scanf("%[^\n]s",nomeaux);
        aux->id=i;
        strcpy(aux->nome,nomeaux);
        system("clear");
        setbuf(stdin,NULL);
        Queue_push(pista,aux);
        menu();

    }
}

int main(){
    int i = 0;
    Queue *pista = Queue_create(TAM);
    int but = 0;

    menu();

do{
    printf("Agurdando escolha: ");
    scanf("%d",&but);
    system("clear");
    switch (but){
    case 1:
        menu();
        printf("%d aguardando decolagem\n",aguardando(pista));
        printf("\n");
        break;
    case 2:
        menu();
        autorizar(pista);
        printf("\n");
        break;
    case 3:
        menu();
        add_aviao(pista);
        printf("\n");
        break;
    case 4:
        menu();
        listar_avioes(pista);
        printf("\n");
        break;
    case 5:
        menu();
        listar_aviao(pista);
        printf("\n");
        break;
    case 6: printf("Saindo\n");
        break;
    default:
        menu();
        printf("opcao invalida\n");
        break;
    }
}while(but != 6);

return 0;}