/*
Questão 3
Escrever o algoritmo de visita em Pré Ordem utilizando sem utilizar procedimentos recursivos.
gcc TADTree.c L4Q3.c Queue.c -c ; gcc -o L4Q3.out TADTree.o L4Q3.o Queue.o ; ./L4Q3.out
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "TADTree.h"
#include "Queue.h"

typedef struct Tree Tree;
int main(){
    // a0 b1 c2 d3 e4 f5
    char l[] = "123456789";
            //'0'6 '1'- '2'3 '3'* '4'4 '5'+ '6'1 '7'+ '8'5
    Tree *t = NULL;

    t = Tree_create(&l[5], //+
                        Tree_create(&l[3], //*
                                        Tree_create(&l[1], //-
                                                    Tree_create(&l[0], NULL , NULL),//6 
                                                    Tree_create(&l[2], NULL , NULL)),//3
                                        Tree_create(&l[7], //+
                                                    Tree_create(&l[4], NULL , NULL),//4 
                                                    Tree_create(&l[6], NULL , NULL)) //1
                    ),
                        Tree_create(&l[8], 
                                    NULL, 
                                    NULL)
                    );


Tree_preOrder(t,print);
printf("Pre-ordem\n");

//res(t,q);

//Queue_print(q,print);
//printf("Fila\n");

Tree_destroy(t);
return 0;}