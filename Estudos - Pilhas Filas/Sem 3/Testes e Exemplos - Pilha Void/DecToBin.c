#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

int main() {
    int a,n = 0;
    Stack *stack = StackVoid_create(20);

    printf("Decimal number: ");
    scanf("%d",&n);
    do{
        a = n%2;
        Stack_push(stack,&a);
        n /= 2 ;
    }while( n != 0);

    printf("Binary number: ");

    while( !Stack_isEmpty(stack) ){
        a = *((int*)Stack_pop(stack));
        printf("%d", a);
    }
    
    printf("\n");
    Stack_destroy(stack);
return 0;}