#include <stdlib.h>
#include <stdio.h>
#include "Stack.h"

struct Stack {
    int size;
    int top;
    void **elements;
};

Stack *stack_create(int size) {
    Stack *stack = (Stack*) malloc(sizeof(Stack));
    if (stack != NULL) {
        stack->size = size;
        stack->top = -1;
        stack->elements = calloc(size, sizeof(void *));
    }
    return stack;
}

void stack_destroy(Stack *stack) {
    if (stack != NULL) {
        free(stack->elements);
        stack->elements = NULL;
        free(stack);
        stack = NULL;
    }
}

int stack_isEmpty(Stack *stack) {
    if (stack != NULL)
        return stack->top == -1;
    return 1;
}

int stack_isFull(Stack *stack) {
    if (stack != NULL)
        return stack->top == (stack->size - 1);
    return 0;
}

int stack_getSize(Stack *stack) {
    if (stack != NULL)
        return stack->size;
    return 0;
}

void stack_push(Stack *stack, void *element) {
    if (stack != NULL && element != NULL) {
        if (!stack_isFull(stack)) {
            stack->top++;
            stack->elements[stack->top] = element;
        }
    }
}

void  *stack_pop(Stack *stack) {
    void *topElement = NULL;
    if (stack != NULL) {
        if (!stack_isEmpty(stack)) {
            topElement = stack->elements[stack->top];
            stack->top--;
        }
    }
    return topElement;
}

void *stack_top(Stack *stack) {
    void *topElement = NULL;
    if (stack != NULL) {
        if (!stack_isEmpty(stack))
            topElement = stack->elements[stack->top];
    }
    return topElement;
}

void stack_print(Stack *stack, void (*print)(void *)) {
    int i;
    if (stack != NULL && print != NULL) {
        for (i = stack->top; i >= 0; i--)
            print(stack->elements[i]);
        printf("\n");
    }
}
