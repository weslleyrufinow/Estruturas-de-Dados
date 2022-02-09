#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
#include "List.h"
#define TAM 5

void print( void *element){
    printf("%d ",*((int *)element));
}

int main() {
    void *aux;
    int i,a[TAM] = {1,2,3,4,5};
    Stack *s = stack_create();

 for(i = 0; i<TAM; i++){
     stack_push(s,&a[i]);
 }

 stack_print(s,print);
 
 for(i = 1; i<5; i++){
     aux = stack_pop(s);
     stack_print(s,print);
 }
 
 
return 0;}