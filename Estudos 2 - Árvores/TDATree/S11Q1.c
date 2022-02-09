#include <stdio.h>
#include <stdlib.h>
#include "TADTree.h"

void print(void *letra){
    printf("%c ", *((char *)letra) );
}

int main(){
    // a0 b1 c2 d3 e4 f5
    char l[] = "6-3*4+1+5";
            //'0'6 '1'- '2'3 '3'* '4'4 '5'+ '6'1 '7'+ '8'5
    Tree *t = NULL;

    t = Tree_create(&l[5], //+
                        Tree_create(&l[3], //*
                                        Tree_create(&l[7], //+
                                                    Tree_create(&l[2], NULL , NULL),//3 
                                                    Tree_create(&l[0], NULL , NULL)),//6
                                        Tree_create(&l[1], //-
                                                    Tree_create(&l[4], NULL , NULL),//4 
                                                    Tree_create(&l[6], NULL , NULL)) //1
                    ),
                        Tree_create(&l[8], 
                                    NULL, 
                                    NULL)
                    );


Tree_print(t,print);
printf("\n");
Tree_destroy(t);
return 0;}

//gcc -c TADTree.c S11Q1.c ; gcc TADTree.o S11Q1.o ; ./a.out