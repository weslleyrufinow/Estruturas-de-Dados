#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

void print(void *a){
    printf("%d ",*((int *)a));
}

int main() {
    int i,*m,n[] = {2,4,6,8,10};
    Queue *queue = Queue_create(5);
/*
printf("Antes do push\n");
printf("cheia? %d ", Queue_isFull(queue)); printf("vazia? %d \n", Queue_isEmpty(queue));*/

for(i=0; i<5 ; i++){
    Queue_push(queue,&n[i]);
}
/*
printf("Apos o push\n");
printf("cheia? %d ", Queue_isFull(queue)); printf("vazia? %d \n", Queue_isEmpty(queue));*/

Queue_print(queue,print);

printf("Main - Printando fila: \n");
for(i=0; i<5 ; i++){
    m = (int *) Queue_pop(queue);
    printf("%d ",*m);
}
printf("\n");
/*
printf("Apos o pop\n");
printf("cheia? %d ", Queue_isFull(queue)); printf("vazia? %d \n", Queue_isEmpty(queue));

printf("Apos o destroy\n");
printf("cheia? %d ", Queue_isFull(queue)); printf("vazia? %d \n", Queue_isEmpty(queue));*/

return 0;}