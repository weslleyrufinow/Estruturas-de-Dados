#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Queue.h"
#include "Stack.h"
#define SIZE 32

int main() {
    int i;
    char strA[SIZE], strB[SIZE], strC[SIZE];
    Queue *q = Queue_create(SIZE);
    Stack *s = stack_create(SIZE);

    printf("Cadeia: ");
        scanf("%[^\n]s",strA);
    
    for (i = 0; strA[i]; i++)
        if (strA[i] != ' ') {
            strA[i] = toupper(strA[i]);
            Queue_push(q, &strA[i]);
            stack_push(s, &strA[i]);
        }

    memset(strB, '\0', SIZE);
    memset(strC, '\0', SIZE);

    for (i = 0; !stack_isEmpty(s); i++) {
        strB[i] = *((char*) Queue_pop(q));
        strC[i] = *((char*) stack_pop(s));
    }
    
    if (strcmp(strB, strC) == 0)
        printf("Is a palindrome chain (%s == %s)\n", strB, strC);
    else
        printf("Isn't a palindrome chain (%s != %s)\n", strB, strC);
    
    Queue_destroy(q);
    stack_destroy(s);
    
    return 0;
}