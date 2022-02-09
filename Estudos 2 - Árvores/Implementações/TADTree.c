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

Tree *tree_create (void *value, Tree *left, Tree *right){
    Tree *tree = NULL;
    if(value){
        tree = (Tree *) malloc(sizeof(Tree));
        tree->value = value;
        tree->left  = (Tree *)left;
        tree->right = (Tree *)right;
        
    }
return tree;}

void tree_destroy(Tree *tree) {
    if (tree) {
        Tree_destroy(tree->left);
        Tree_destroy(tree->right);
        free(tree);
    }
}

void tree_inOrder(Tree *tree, void (*process)(void *)){
    if(tree){
        if(tree->value){
            Tree_inOrder(tree->left, process);
            process(tree->value);
            Tree_inOrder(tree->right, process);
        }
    }
}

void tree_preOrder(Tree *tree, void (*process)(void *)){
    if(tree){
        if(tree->value){
            process(tree->value);
            Tree_preOrder(tree->left, process);
            Tree_preOrder(tree->right, process);
        }
    }
}

void tree_postOrder(Tree *tree, void (*process)(void *)){
    if(tree){
        if(tree->value){
            Tree_postOrder(tree->left, process);
            Tree_postOrder(tree->right, process);
            process(tree->value);
        }
    }
}

void tree_queue(Tree *tree, Queue *q){
    if(tree){
        if(tree->value){
            res_queue(tree->left,q);
            res_queue(tree->right,q);
            Queue_push(q,tree->value);
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

int compar(void *v,void *k){
    int i;
    char *a = ((char *)v);
    char *b = ((char *)k);

    i = strcmp(a,b);
    //printf("i: %d\n", i);
    printf("v: %c\n", *a);
return i;}

Tree *tree_find(Tree *tree, void *value, int (*compar)(void*,void*)) {
    Tree *node = NULL;

    if (tree && value && compar) {
        if (compar(value, tree->value) == 0)
            node = tree;
        else {
            node = Tree_find(tree->left, value, compar);
            if (node == NULL)
                node = Tree_find(tree->right, value, compar);
        }
    }

    return node;
}

/*
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
*/