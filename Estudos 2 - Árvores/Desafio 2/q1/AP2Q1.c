/*
Questão 1 - 3 pontos
Crie uma função que aceite uma expressão aritmética simples formada pelos operadores básicos (+, -, *, /) 
e números de 0 a 9, a função deve validar a expressão retornando 1 caso a expressão seja válida e 0 caso contrário. 
Para validar a expressão use as seguintes regras: 
*um nó com um operador deve possuir os filhos esquerdo e direito não nulos, enquanto um nó que possui um operando deve possuir ambos os filhos nulos indicando que é uma folha. 

Crie um programa para testar sua implementação com as seguintes expressões:
gcc Tree.c queue.c AP2Q1.c -c ; gcc -o AP2Q1.out Tree.o queue.o AP2Q1.o ; ./AP2Q1.out
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Tree.h"

int inttree_postOrder(Tree *tree, int valida(Tree *t)){
    if(tree){
        if(tree->value){
            int n;
            inttree_postOrder(tree->left, valida);
            inttree_postOrder(tree->right, valida);
            n = valida(tree);
        }
    }
}

int valida(Tree *t){
    int n = 0;
    char c = *((char *)t->value);

  if(strchr("0123456789",c)){
      if(t->left == NULL && t->right == NULL){
          n = 1;
      }else{
          n = 0;
      }
      //printf("n: %d\n",n);
  }

  if(strchr("+-*/",c)){
      if( (t->left == NULL) && (t->right == NULL) ){
          n = 0;
      }else if((t->left != NULL) && (t->right != NULL)){
          if ( (strchr("+-*/",*((char *)t->left->value)))  && (strchr("+-*/",*((char *)t->right->value))) ){
              n = 0;
          }else{
              n = 1;
          }
      }
      //printf("opr: %d\n",n);
  }

return n;}

void valida_main(Tree *t){
    int n = inttree_postOrder(t,valida);
    if(n == 1){
        printf("Valida\n");
    }else{
        printf("Invalida\n");
    }
}


int main(){

    char l1[] = "+*225";//valida
    char l2[] = "4*72+";//invalida
    char l3[] = "-*23+3";//invalida
    Tree *t1 = NULL, *t2 = NULL, *t3 = NULL;

    t1 = tree_create(&l1[0], //+
                        tree_create(&l1[1], //*
                                            tree_create(&l1[2],NULL, NULL),//2
                                            tree_create(&l1[3],NULL, NULL) //2
                        ),tree_create(&l1[4],NULL,NULL)//5
                    );

    t2 = tree_create(&l2[0], //4
                        tree_create(&l2[1], //*
                                            tree_create(&l2[2],NULL, NULL),//7
                                            tree_create(&l2[3],NULL, NULL) //2
                        ),tree_create(&l2[4],NULL,NULL)//+
                    );
    t3 = tree_create(&l3[0], //-
                        tree_create(&l3[1], //*
                                            tree_create(&l3[2],NULL, NULL),//2
                                            tree_create(&l3[3],NULL, NULL) //3
                        ),tree_create(&l2[4],NULL,//+
                                                    tree_create(&l3[5],NULL,NULL))//3
                    );

    tree_print_main(t1,print_char);
    tree_print_main(t2,print_char);
    tree_print_main(t3,print_char);

    valida_main(t1);
    valida_main(t2);
    valida_main(t3);



    tree_destroy(t1);
    tree_destroy(t2);
    tree_destroy(t3);
return 0;}