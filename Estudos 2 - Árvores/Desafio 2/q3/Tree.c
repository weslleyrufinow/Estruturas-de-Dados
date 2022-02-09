#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "Tree.h"
#include "avl.h"
#include "rbtree.h"
#include "queue.h"


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
        tree_destroy(tree->left);
        tree_destroy(tree->right);
        free(tree);
    }
}

void print_char(void *a){
    printf("%c", *((char*) a));
}

int compar_char(void *a, void *b) {
    return *((char*) a) - *((char*) b);
}

Tree *tree_find_main(Tree *tree, void *value, int (*compar)(void*,void*), void (*print_char)(void*)){
    Tree *p = NULL;
    p = tree_find(tree,value,compar);
    if(p == NULL){
        printf("Tree_find retornou NULL\n");
    }else{
        printf("Valor encontrado: ");
        print_char(p->value); printf("\n");
    }
}

Tree *tree_find(Tree *tree, void *value, int (*compar)(void*,void*)){
    Tree *node = NULL;

    if (tree && value && compar) {
        if (compar(value, tree->value) == 0)
            node = tree;
        else {
            node = tree_find(tree->left, value, compar);
            if (node == NULL)
                node = tree_find(tree->right, value, compar);
        }
    }

    return node;
}

void tree_print_main(Tree *tree, void (*print)(void *)){
    tree_print(tree,print);
    printf("\n");
}

void tree_print(Tree *tree, void (*print)(void *)) {
    if (tree && print) {
        printf("(");
        print(tree->value);
        printf(" ");
        tree_print(tree->left, print);
        tree_print(tree->right, print);
        printf(")");
    }
    else
        printf("<> ");
}

void tree_inOrder(Tree *tree, void (*process)(void *)){
    if(tree){
        if(tree->value){
            tree_inOrder(tree->left, process);
            process(tree);
            tree_inOrder(tree->right, process);
        }
    }
}

void tree_preOrder(Tree *tree, void (*process)(void *)){
    if(tree){
        if(tree->value){
            process(tree);
            tree_preOrder(tree->left, process);
            tree_preOrder(tree->right, process);
        }
    }
}

void tree_postOrder(Tree *tree, void (*process)(void *)){
    if(tree){
        if(tree->value){
            tree_postOrder(tree->left, process);
            tree_postOrder(tree->right, process);
            process(tree);
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

void tree_queue(Tree *tree, Queue *q){
    if(tree){
        if(tree->value){
            tree_queue(tree->left,q);
            tree_queue(tree->right,q);
            Queue_push(q,tree->value);
        }
    }
}

void tree_print_level_main(Tree *bst, void (*print)(void *)){
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



void tree_height_main(Tree *tree){
    int n;
    n = tree_height(tree);
    printf("Altura da arvore: %d\n", n);
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

void tree_eval_main(Tree *t){
    int n;
    n = tree_eval(t);
    printf("Resultado da expressao: %d\n",n);
}

int tree_eval(Tree *t) {
    char c;
    
    if (t) {
        c = *( (char*)t->value );
        
        if (c == '+') {
            return tree_eval(t->left) + tree_eval(t->right);
        }
        else if (c == '*') {
            return tree_eval(t->left) * tree_eval(t->right);
        }
        else if (c == '-') {
            return tree_eval(t->left) - tree_eval(t->right);
        }
        else if (c == '/') {
            return tree_eval(t->left) / tree_eval(t->right);
        }
        else 
            return c - 48;
    }
    else
        return 0;
}