#include <stdio.h>
#include <stdlib.h>
#include "Tree.h"
//gcc Tree.c Tree_main_2.c -c ; gcc -o Tree_main_2.out Tree.c Tree_main_2.c ; ./Tree_main_2.out
int compar(void *a, void *b) {
    return *((char*) a) - *((char*) b);
}

void print(void *a) {
    printf("%c", *((char*) a));
}

/**
 * 3*2 + 5
 *    +
 *   / \
 *  *   5
 * / \ 
 * 3 2 
 * 
 */

int Tree_eval(Tree *t) {
    char c;
    
    if (t) {
        c = *( (char*)t->value );
        
        if (c == '+') {
            return Tree_eval(t->left) + Tree_eval(t->right);
        }
        else if (c == '*') {
            return Tree_eval(t->left) * Tree_eval(t->right);
        }
        else 
            return c - 48;
    }
    else
        return 0;
}

int main() {
    char *str = "+*532";
    Tree *n = NULL, *t = NULL;

    t = Tree_create(&str[0], 
            Tree_create(&str[1], 
                Tree_create(&str[3], NULL, NULL),
                Tree_create(&str[4], NULL, NULL)
            ),
            Tree_create(&str[2], NULL,NULL)
        );
    
    Tree_print(t, print);
    printf("\n");

    printf("= %d\n", Tree_eval(t));    

    Tree_destroy(t);
    return 0;
}
