#include <stdio.h>
#include <stdlib.h>
#include "TADTree.h"

void print(void *letra){
    printf("%c ", *((char *)letra) );
}

int main(){
    // a0 b1 c2 d3 e4 f5
    char l[] = "abcdef";
    Tree *t = NULL;

    t = Tree_create(&l[0], //a
                        Tree_create(&l[1], //b
                                        NULL,
                                        Tree_create(&l[3], NULL , NULL) //d
                    ),
                        Tree_create(&l[2], //c
                                        Tree_create(&l[4], NULL , NULL), //e
                                        Tree_create(&l[5], NULL , NULL)  //f
                    )

    );
Tree_print(t,print);
printf("\n");
Tree_destroy(t);
return 0;}

//gcc -c TADTree.c TADTeste.c ; gcc TADTree.o TADTeste.o ; ./a.out