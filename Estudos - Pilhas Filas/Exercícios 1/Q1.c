/*
Questão 1
Escreva uma função que percorre uma lista ligada de inteiros e remove (liberando adequadamente a memória)
todos os nós que contêm o(s) elemento(s) de maior valor como mostra a figura. 
O elemento de maior valor deve ser retornado pela função.
*/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

void print( void *element){
    printf("%d ",*((int *)element));
}

int compar(void *a,void *b){
    int aux = 2;
    if(*((int *)a) == *((int *)b))
        aux = 0;
    if(*((int *)a) > *((int *)b))
        aux = 1;
    if(*((int *)a) < *((int *)b))
        aux = -1;
return aux;}

int main(){
 int i,a[] = {3,6,9,3,5,9,7,9,4};
 List *l = List_create();
 void *aux ,*aux2;

 for(i = 0; i<9; i++)
     List_insertEnd(l,&a[i]);

 List_print(l,print);

 aux = List_removeMaior(l,compar);
 if(aux)
    printf("Maior numero retornado: %d\n", *((int *)aux) );
 
 List_print(l,print);

 List_destroy(l);
return 0;}