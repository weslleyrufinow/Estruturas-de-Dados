#include <stdlib.h>
#include <stdio.h>
#include "List.h"
#include "Stack.h"

typedef struct Node Node;
typedef struct Stack Stack;

struct Node {
    Node *next;
    void *value;
};

struct List {
    Node *first;
    int length;
};

struct Stack {
    void *top;
    List *elements;
};

int compar(void *a,void *b){
    int aux = 2;
    if(*((int *)a) == *((int *)b))
        aux = 0;
    if(*((int *)a) > *((int *)b))
        aux = 1;
    if(*((int *)a) < *((int *)b))
        aux = -1;
return aux;}

Stack *stack_create() {
    Stack *s = malloc(sizeof(Stack));
    s->elements = List_create();
return s;}

void stack_destroy(Stack *s) {
    if (s != NULL) {
        List_destroy(s->elements);
        free(s);
        s = NULL;
    }
}

int stack_isEmpty(Stack *s){
    if(s->elements->first == NULL){
        return 1;
    }else{
        return 0;
    }
}

int stack_getSize(Stack *s) {
    if (s != NULL)
        return s->elements->length;
return 0;}

void stack_push(Stack *s, void *element) {
    if (s != NULL && element != NULL) {
        List_insertBegin(s->elements, element);
        s->top = element;
    }
}

void *stack_top(Stack *s) {
    void *topElement = NULL;
    if (s != NULL) {
            topElement = s->elements->first->value;
    }
    return topElement;
}

void  *stack_pop(Stack *s) {
    void *topElement = NULL;
    if (s != NULL) {
        if (stack_isEmpty(s) != 1) {
            topElement = List_removeBegin(s->elements);
            s->top = s->elements->first->value;
        }
    }
return topElement;}

void stack_print(Stack *s, void (*print)(void *)) {
    int i;
    if (s != NULL && print != NULL) {
        List_print(s->elements,print);
        printf("\n");
    }
}
