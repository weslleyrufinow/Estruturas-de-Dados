#include <stdio.h>
#include <stdlib.h>
#include "TADTree.h"

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
        tree->left = NULL;

        free(tree);
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

void Tree_print(Tree *tree, void (*print)(void *)){
    if(tree){
        if(tree->value){
            printf("<");
            Tree_print(tree->left, print);
            print(tree->value);
            Tree_print(tree->right, print);
            printf("> ");
        }
    }else{
        printf("<> ");
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
//Funcao de processamento é generica, como printar, ou realizar uma operação
/*
void Tree_preOrder(Tree *tree){
    process(tree);
    Tree_preOrder(tree->left);
    Tree_preOrder(tree->right);
}
void Tree_inOrder(Tree *tree){
    Tree_preOrder(tree->left);
    process(tree);
    Tree_preOrder(tree->right);
}
void Tree_postOrder(Tree *tree){
    Tree_preOrder(tree->left);
    Tree_preOrder(tree->right);
    process(tree);
}
*/