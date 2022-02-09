/*
Questão 2
Escrever uma função que calcule a altura de uma árvore binária dada. 
A altura de uma árvore é igual ao máximo nível de seus nós.
gcc TADTree.c L4Q2.c Queue.c -c ; gcc -o L4Q2.out TADTree.o L4Q2.o Queue.o ; ./L4Q2.out
*/

#include <stdio.h>
#include <stdlib.h>
#include "TADTree.h"
/*
void print(void *letra){
    printf("%c ", *((char *)letra) );
}
*/

int main(){
    char l[] = "6-3*4+1+5";
    Tree *t = NULL;
    int h = 0;
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


tree_print_setas(t,print);
printf("Pos-ordem\n");

Tree_destroy(t);
//t = NULL;
h = tree_height(t);
printf("altura: %d\n",h);

tree_print_setas(t,print);
printf("Pos-ordem\n");

//Tree_destroy(t);
return 0;}