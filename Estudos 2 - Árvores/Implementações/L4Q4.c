/*
Questão 4
Fazer função para retornar o pai de um dado nó de uma árvore: 
(a) dado um item, procura se item existe na árvore (usando algum algoritmo de travessia) 
(b) caso positivo retorna o conteúdo do pai do nó.
gcc TADTree.c L4Q4.c Queue.c -c ; gcc -o L4Q4.out TADTree.o L4Q4.o Queue.o ; ./L4Q4.out
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
    char *pc,c = '-';
    void *p,*p2;
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
//pc = &c;
pc = &l[6];
printf("pc: %c\n", *((char*)pc));

p2 = tree_find(t,pc, compar);

if(p2 != NULL)
    printf("certo? %c\n", *((char*)p2));

tree_print_setas(t,print);
printf("Pos-ordem\n");

Tree_destroy(t);
return 0;}