#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

void print(void *a){
    printf("%d\n",*((int *)a));
}

int main() {
    int i,*m,n[] = {2,4,6,8,10};
    Stack *stack = stack_create(5);

for(i=0; i<5 ; i++){
    stack_push(stack,&n[i]);
}

stack_print(stack,print);

printf("Desempilhando: \n");
for(i=0; i<5 ; i++){
    m = (int *) stack_pop(stack);
    printf("%d\n",*m);
}

return 0;}