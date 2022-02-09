#include <stdio.h>
#include <stdlib.h>
#include "StackInt.h"

int main() {
    int n = 0;
    StackInt *stack = StackInt_create(20);

    printf("Decimal number: ");
    scanf("%d",&n);
    do{
        StackInt_push(stack,n%2);
        n /= 2 ;
    }while( n != 0);

    printf("Binary number: ");

    while( !StackInt_isEmpty(stack) ){
        printf("%d",StackInt_pop(stack));
    }

    printf("\n");
    StackInt_destroy(stack);

return 0;}