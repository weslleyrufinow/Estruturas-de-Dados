/*
Questão 2:
Uma aplicação de lista ordenada é a manipulação de polinômios.
Um polinômio P(x) é uma expressão da forma 𝙖ₙ𝙭ⁿ + ... + 𝙖₂𝙭² + 𝙖₁𝙭 + 𝙖₀. 
Um polinômio pode ser representado por uma lista de pares da forma (c,e), 
cada um deles representando um termo de coeficiente c e expoente e. 
Como um polinômio sempre pode ser escrito na forma reduzida, 
na qual não há expoentes repetidos, os pares nessa lista podem ser ordenados em função do expoente, 
de modo estritamente decrescente. 
(a) Crie um programa que recebe uma sequência de pares (coeficiente, expoente) 
    e os guarda em uma lista ordenada pelo expoente de forma decrescente. 
(b) Crie uma função de impressão para a lista que exiba o polinômio na forma de uma expressão.
por exemplo: P(x) = 3x^5 - 6x^2 + 1.
*/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

typedef struct Node Node;
struct Node {
    Node *next;
    void *value;
};

struct termo{
    int num;
    int exp;
};
typedef struct termo termo;

void print( void *element){
    termo *aux;
    aux = ((termo *)element);
    printf("Numero: %d |EXP: %d *|*",aux->num,aux->exp);
}

int compar(void *a,void *b){
    int r;
    termo *aux1 = (termo *)a;
    termo *aux2 = (termo *)b;
    if(aux1->exp > aux2->exp)
        r = 1;

    if(aux1->exp < aux2->exp)
        r = -1;

    if(aux1->exp == aux2->exp)
        r = 0;

return r;}

void imprime(List *new, int n){
    Node *aux2;
    termo *aux;
    int i,a,b;
    if(new && n >0){
        printf("P(X) = ");
        for(i = 0 ; i < n; i++){
            aux2 = List_removeBegin(new);
            aux = aux2->value;

            if(aux->num > 0){
                printf(" + ");}
            if(aux->num < 0){
                printf(" - ");}

                printf("%d",aux->num);

            if(aux->exp > 0){
                printf("x^");
                printf("%d ",aux->exp);
            }
        }
        printf("\n");
    }else{
        printf("Lenghth = 0");
    }
}

int main(){
 int i,n,a,b;
 List *new,*l = List_create();
 termo *aux;
 printf("Quantos termos tem o seu polinomio?\n");
 scanf("%d",&n);

 for(i = 0; i < n; i++){
     aux = malloc(sizeof(termo *));
     printf("Numero e Expoente do termo %d: ",i+1);
     scanf("%d",&a);
     scanf("%d",&b);
     aux->num = a;
     aux->exp = b;

     List_insertEnd(l,aux);
     List_print(l,print);
 }

    system("clear");
    new = List_sort(l, compar);

    //List_print(new,print);

    imprime(new,n);

    List_destroy(l);
return 0;}