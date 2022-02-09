#include <stdlib.h>
#include <stdio.h>
#include "StackInt.h"

struct StackInt {
    int length;
    int top;
    int *elements;
};

StackInt *StackInt_create(int length) {
    StackInt *stack = (StackInt*) malloc(sizeof(StackInt));
    if (stack != NULL) {
		stack->length = length;
		stack->top = -1;
		stack->elements = calloc(length, sizeof(int));
    }
    return stack;
}

void StackInt_destroy(StackInt *stack) {
    if (stack != NULL) {
        free(stack->elements);
        free(stack);
    }
}

int StackInt_isEmpty(StackInt *stack) {
    if (stack != NULL)
        return stack->top == -1;
    return 1;
}

int StackInt_isFull(StackInt *stack) {
    if (stack != NULL)
        return stack->top == (stack->length - 1);
    return 0;
}

void StackInt_push(StackInt *stack, int element) {
    if (stack != NULL) {
        if (!StackInt_isFull(stack)) {
            stack->top++;
            stack->elements[stack->top] = element;
        }
    }
}

int StackInt_pop(StackInt *stack) {
    int topElement = 0;
    if (stack != NULL) {
        if (!StackInt_isEmpty(stack)) {
            topElement = stack->elements[stack->top];
            stack->top--;
        }
    }
    return topElement;
}

int StackInt_top(StackInt *stack) {
    int topElement = 0;
    if (stack != NULL) {
        if (!StackInt_isEmpty(stack))
            topElement = stack->elements[stack->top];
    }
    return topElement;
}

void StackInt_print(StackInt *stack) {
    int i;
    if (stack != NULL) {
        for (i = stack->top; i >= 0; i--)
            printf("%d ", stack->elements[i]);
        printf("\n");
    }
}
