#include <stdlib.h>
#include <stdio.h>
#include "Queue.h"
//PENSAMENTO ALTERNATIVO: UM CONTADOR QUE DIZ QUANTOS ITENS A FILA TEM (0 A N)
struct Queue {
    int begin;
    int end;
    int size;
    int cont;
    void **elements;
};

int Queue_next(Queue *queue, int index){
    if(queue != NULL && index >= 0)
        return ((index+1) % queue->size);
    else
        return 0;
}

Queue  *Queue_create(int size){
    int i;
    Queue *queue = malloc(sizeof(Queue));
    queue->begin = -1;
    queue->end = -1;
    queue->size = size;
    queue->cont = 0;

    queue->elements = malloc(sizeof(void *) * size);

    for(i=0; i<size; i++)
        queue->elements[i] = NULL;

return queue;}

void Queue_destroy(Queue *queue) {
    int i;
    if (queue != NULL){
        free(queue->elements);
        queue->elements = NULL;
        free(queue);
        queue = NULL;
    }
}


int Queue_isEmpty(Queue *queue){
    if(queue != NULL){
        if(queue->cont == 0){
            return 1;
        }else{
            return 0;
        }
    }
}

int Queue_isFull(Queue *queue){
    if(queue != NULL){
        if(queue->cont == queue->size){
            return 1;
        }else{
            return 0;
        }
    }
}


void Queue_push(Queue *queue, void *element){
    if(queue != NULL && element != NULL){
        //SE A FILA ESTIVER VAZIA, BEGIN E END VÃO APONTAR PRO INÍCIO
        if(Queue_isEmpty(queue)){
            queue->begin = Queue_next(queue, queue->end);
            queue->end = queue->begin;
            queue->elements[queue->end] = element;
            queue->cont++;
        }
        //SE A FILA NAO ESTIVER CHEIA, END RECEBE O PROXIMO INDICE E EM SEGUIDA O VALOR
        else if (!Queue_isFull(queue)){
            queue->end = Queue_next(queue, queue->end);
            queue->elements[queue->end] = element;
            queue->cont++;
        }
    }
}

//REFAZER O POP
void *Queue_pop(Queue *queue){
   void *a = NULL;
    if(queue != NULL){
        if(!Queue_isEmpty(queue)){
            a = queue->elements[queue->begin];
            queue->elements[queue->begin] = NULL;
            queue->begin = Queue_next(queue,queue->begin);
            queue->cont--;
        }
    }

return a;}

void *Queue_begin(Queue *queue){
    if( queue != NULL && !Queue_isEmpty(queue) )
        return queue->elements[queue->begin];
}

void *Queue_end(Queue *queue){
    if( queue != NULL)
        return queue->elements[queue->end];
}

void Queue_print(Queue *queue, void (*print)(void *)){
    int i, j;
    void *a,*aux;
    i =  queue->begin;
    for(j = 0; j < queue->cont; j++){
        //printf("Begin : %d | End : %d | Next: %d ", queue->begin, queue->end ,i);
        print(queue->elements[i]);
        i = Queue_next(queue,i);
    }
    //printf("\n");
}