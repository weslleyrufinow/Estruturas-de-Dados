#include <stdio.h>
#include <stdlib.h>
#include "TADTree.h"

void print(void *letra){
    printf("%i ", *((int *)letra) );
}

int main(){
    // 01 12 23 34 45 56 67
    int l[] = {1,2,3,4,5,6,7};
    Tree *t = NULL;

    t = Tree_create(&l[0], //1
                        Tree_create(&l[1], //2
                                        NULL,
                                        Tree_create(&l[3], NULL , NULL) //4
                    ),
                        Tree_create(&l[2], //3
                                        Tree_create(&l[4], NULL , NULL), //5
                                        Tree_create(&l[5], NULL , NULL)  //6
                    )

    );
Tree_print(t,print);
printf("\n");

Tree_setLeft(Tree_getLeft(t),&l[6]);  //7 Coloca o valor no ultimo no esquerdo
Tree_print(t,print);
printf("\n");
Tree_setLeft(Tree_getLeft(Tree_getLeft(t)),&l[5]);  //6 Substitui o valor no ultimo no esquerdo
Tree_print(t,print);
printf("\n");

Tree_destroy(t);
return 0;}

//gcc -c TADTree.c TADTeste2.c ; gcc TADTree.o TADTeste2.o ; ./a.out