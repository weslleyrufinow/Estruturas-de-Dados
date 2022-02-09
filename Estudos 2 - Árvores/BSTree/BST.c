#include <stdio.h>
#include <stdlib.h>

struct BST{
    void *value;
    BST *left;
    BST *right;
    int (*compar)(void *, void *);
};

typedef struct BST BST;

BST  *BST_create(int (*compar)(void*, void*)){
    BST *bst = NULL;

    if(compar){
        bst = (BST *) malloc(sizeof (BST));
        bst->value = NULL;
        bst->left = NULL;
        bst->right = NULL;
        bst->compar = compar;
    }


return bst;}

void  BST_destroy(BST *bst){
    if(bst != NULL){
        BST_destroy(bst->left);
        BST_destroy(bst->right);
        free(bst);
    }
}

void  BST_insert(BST *bst, void *value){
    if(bst && value)
        if(bst->value == NULL)
            bst->value = value;
        else
            if(bst->compar(bst->value,value) < 0){
                if(bst->right == NULL)
                    bst->right = BST_create(bst->compar);

                BST_insert(bst->right,value);
            }
            else
            if(bst->compar(bst->value,value) > 0){
                if(bst->left == NULL)
                    bst->left = BST_create(bst->compar);

                BST_insert(bst->left,value);
            }
}

void *BST_search(BST *bst, void *value){
    if(bst && value)
        if(bst->value)
            if(bst->compar(bst->value,value) == 0)
                return bst->value;
            else
                if(bst->compar(bst->value,value) < 0)
                    return BST_search(bst->right,value);
                else
                    return BST_search(bst->right,value);
return NULL;}

void *BST_remove(BST *bst, void *value);

void  BST_print(BST *bst, void (*print)(void*));
