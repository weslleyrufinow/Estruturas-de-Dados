#include <stdio.h>
#include <stdlib.h>
#include "Tree.h"
//gcc Tree.c Tree_main.c -c ; gcc -o Tree_main.out Tree.c Tree_main.c ; ./Tree_main.out
int compar(void *a, void *b) {
    return *((char*) a) - *((char*) b);
}

void print(void *a) {
    printf("%c", *((char*) a));
}

int main() {
    char *str = "abcdef", c = 'e';
    Tree *n = NULL, *t = NULL;

    t = Tree_create(&str[0], 
            Tree_create(&str[1], 
                Tree_create(&str[2], NULL, NULL),
                Tree_create(&str[3], NULL, NULL)
            ),
            Tree_create(&str[4], 
                NULL,
                Tree_create(&str[5], NULL, NULL)
            )
        );
    
    Tree_print(t, print);
    printf("\n");

    n = Tree_find(t, &c, compar); //buscando 'e'
    
    printf("item encontrado = %c\n", *((char*) n->value));

    Tree_destroy(t);
    return 0;
}
