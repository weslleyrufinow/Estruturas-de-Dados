/*
Questão 4
Fazer função para retornar o pai de um dado nó de uma árvore: 
(a) dado um item, procura se item existe na árvore (usando algum algoritmo de travessia) 
(b) caso positivo retorna o conteúdo do pai do nó.
gcc TADTree.c teste.c Queue.c -c ; gcc -o teste.out TADTree.o L4Q4.o Queue.o ; ./teste.out
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "TADTree.h"
#include "Queue.h"


struct Tree{
    void *value;
    Tree *left;
    Tree *right;
};

typedef struct Tree Tree;

Tree *Tree_create (void *value, Tree *left, Tree *right){
    Tree *tree = NULL;
    if(value){
        tree = (Tree *) malloc(sizeof(Tree));
        tree->value = value;
        tree->left  = (Tree *)left;
        tree->right = (Tree *)right;
        
    }
return tree;}

void Tree_destroy(Tree *tree){
    if(tree){
        Tree_destroy(tree->left);
        tree->left = NULL;

        Tree_destroy(tree->right);
        tree->right = NULL;
        
        free(tree);
        tree = NULL;
    }
}

void *Tree_getValue(Tree *tree){
    if(tree){
        return tree->value;
    }else{
        return NULL;
    }
}

void *Tree_getLeft(Tree *tree){
    if(tree){
        return tree->left;
    }else{
        return NULL;
    }
}

void *Tree_getRight(Tree *tree){
    if(tree){
        return tree->right;
    }else{
        return NULL;
    }
}

void *Tree_setValue(Tree *tree, void *value){
    if(tree && value){
        tree->value = value;
    }
}

void *Tree_setLeft(Tree *tree, void *value){
    if(tree && value){
        tree->left = Tree_create(value, NULL, NULL);
    }
}

void *Tree_setRight(Tree *tree, void *value){
    if(tree && value){
        tree->right = Tree_create(value, NULL, NULL);
    }
}


void Tree_inOrder(Tree *tree, void (*process)(void *)){
    if(tree){
        if(tree->value){
            Tree_inOrder(tree->left, process);
            process(tree->value);
            Tree_inOrder(tree->right, process);
        }
    }
}

void Tree_preOrder(Tree *tree, void (*process)(void *)){
    if(tree){
        if(tree->value){
            process(tree->value);
            Tree_preOrder(tree->left, process);
            Tree_preOrder(tree->right, process);
        }
    }
}

void Tree_postOrder(Tree *tree, void (*process)(void *)){
    if(tree){
        if(tree->value){
            Tree_postOrder(tree->left, process);
            Tree_postOrder(tree->right, process);
            process(tree->value);
        }
    }
}
/*
void res_stack(Tree *tree, Stack *s){
    if(tree){
        if(tree->value){
            res_stack(tree->left,s);
            res_stack(tree->right,s);
            stack_push(s,tree->value);
        }
    }
}
*/
void res_queue(Tree *tree, Queue *q){
    if(tree){
        if(tree->value){
            res_queue(tree->left,q);
            res_queue(tree->right,q);
            Queue_push(q,tree->value);
        }
    }
}



void res(Tree *tree, Queue *q){
    if(tree){
        if(tree->value){
            res(tree->left,q);
            res(tree->right,q);
            proccess(tree->value,q);
        }
    }
}

void *op(void *opr, Queue *q){
    char op = *( (char *) opr);
    char *ch = malloc(sizeof(char *));
    int x,y,r, *res = malloc(sizeof(int *));
    void *n = malloc(sizeof(void *));
    x=y=r=0; 
    n = NULL; res = NULL;

        x =  atoi((char *) Queue_pop(q)) ;
        y =  atoi((char *) Queue_pop(q)) ;
        printf("x: %d",x);
        printf(" %c",op);
        printf(" %d :y \n",y);

        switch(op){
            case '+':   r = x+y; res = &r;
                        break;

            case '-':   r = x-y; res = &r;
                        break;

            case '*':   r = x*y; res = &r;
                        break;

            case '/':   r = x/y; res = &r;
                        break;
        }
        *ch = *res+'0';
        n = ch;
        printf("res: %d",*res);
        printf(" ch: %c",*ch);
        printf(" n: %c\n",*((char *)n));
return n;}

void proccess(void *value, Queue *q){
        if(value){
            if(isdigit( *((char *)value)) ){
                Queue_push(q,value);
                Queue_print(q,print);
                printf("\n");
            }else{
                Queue_push(q,op(value,q));
            }
            
        }
}
/*
 3 + 6 * 4 - 1 + 5
        +
      /   \
     *     5
   /   \
  +     -
 / \   / \
3   6 4   1

Pre-ordem:
 + * + 3 6 - 4 1 5

In-ordem:
3 + 6 * 4 - 1 + 5

Pos-ordem:
3 6 + 4 1 - * 5 +
*/

void print(void *letra){
    printf("%c ", *((char *)letra) );
}

void tree_print_main(Tree *bst, void (*print)(void *)) {
    int level = 0;
    if (print) {
        tree_print_level(bst, print, level, '.');
    }
}

void tree_print_level(Tree *bst, void (*print)(void *), int level, char c){
    int i;

    for (i=0; i<level; i++)
        printf("\t");

    printf("%c/", c);
    if (bst) {
        print(bst->value);
        printf("\n");


        tree_print_level(bst->right, print, level + 1, 'r');
        tree_print_level(bst->left,  print, level + 1, 'l');
    }
    else
        printf("~\n");
}

void tree_print_setas(Tree *tree, void (*print)(void *)){
    if(tree){
        if(tree->value){
            printf("<");
            tree_print_setas(tree->left, print);
            print(tree->value);
            tree_print_setas(tree->right, print);
            printf("> ");
        }
    }else{
        printf("<> ");
    }
}

int tree_height(Tree *tree){
    int l, r;
    if (tree == NULL) {
        return 0;
    }
    else {
        l = 1 + tree_height(tree->left);
        r = 1 + tree_height(tree->right);

        if(l > r)
            return l;
        else
            return r;
    }
}

int compar(void *v,char *k){
    int i;
    char a = *((char *)k);
    char b = *((char *)v);
    i = strcmp(k,v);
return i;}

int tree_find(Tree *t,char *key, int (compar)(void *, char *)){
    if(t == NULL){
        return 0;
    }else{
        if(compar(t->value,key) == 0){
            return 1;
        }else{
            if(compar(t->value,key) < 0){
                return (tree_find( t->left,key,compar) );
            }else{
                return (tree_find( t->right,key,compar) );
            }
        }
                
    }
}

/*
void print(void *letra){
    printf("%c ", *((char *)letra) );
}
*/

int main(){
    char l[] = "6-3*4+1+5";
    Tree *t = NULL;
    int h = 0;
    char *pc,c = '3';
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
pc = &c;
p2 = tree_find(t,pc, compar);

printf("p2: %c \n", *((char*)p2));

tree_print_setas(t,print);
printf("Pos-ordem\n");

Tree_destroy(t);
return 0;}