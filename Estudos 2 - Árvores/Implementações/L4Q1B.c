/*
Questão 1
Implemente um TAD árvore binária de expressões aritméticas. 
Por exemplo, a expressão (6-3)*(4+1)+5 é representada pela árvore binária ilustrada na figura abaixo. 
As folhas da árvore armazenam operandos e os nós internos operadores. 
Teste sua implementação com a expressão desta árvore que resulta no valor 20.
gcc TADTree.c L4Q1B.c Queue.c -c ; gcc -o L4Q1B.out TADTree.o L4Q1B.o Queue.o ; ./L4Q1B.out
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "TADTree.h"
#include "Queue.h"
/*
void print(void *letra){
    printf("%c ", *((char *)letra) );
}
*/

int main(){
    // a0 b1 c2 d3 e4 f5
    char l[] = "6-3*4+1+5";
            //'0'6 '1'- '2'3 '3'* '4'4 '5'+ '6'1 '7'+ '8'5
    Tree *t = NULL;
    Queue *q = NULL;
    q = Queue_create(1000);

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


Tree_postOrder(t,print);
printf("Pos-ordem\n");

res(t,q);

Queue_print(q,print);
printf("Fila\n");

Tree_destroy(t);
return 0;}