#include <stdio.h>
#include <stdlib.h>
#include "BST.h"

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

void *BST_remove(BST *bst, void *value){
    if(bst == NULL){
        return NULL;
    }
    else{
        if(bst->compar(bst->value,value) > 0){
            bst->left = BST_remove(bst->left,value);
        }
        else if (bst->compar(bst->value,value) < 0){
            bst->right = BST_remove (bst->right,value);
        }
        else{
            if((bst->left == NULL) && (bst->right == NULL)){
                free(bst);
                bst=NULL;
            }
            else if(bst->right == NULL){
                BST *tmp = bst;
                bst = bst->left;
                free (tmp);
            }
            else if(bst->left == NULL){
                BST *tmp = bst;
                bst = bst->right;
                free (tmp);
            }
            else{
                BST *tmp = bst->left;
                while(tmp->right != NULL){
                    tmp=tmp->right;
                }
                bst->value = tmp->value;
                tmp->value = value;
                bst->left = BST_remove(bst->left,value);
            }
        }
    }
    return bst;
}

void  BST_print(BST *bst, void (*print)(void*)){
    if(bst){
        if(bst->value){
            printf("<");
            BST_print(bst->left, print);
            print(bst->value);
            BST_print(bst->right, print);
            printf("> ");
        }
    }else{
        printf("<> ");
    }
}

/*
void pre_ordem (BST *t) {
    if (BST){
       BST_print(t,print);
       pre_ordem (arv->left);
       pre_ordem (arv->right);

    }
}

void in_ordem (BST *arv) {
   if (BST) {
      in_ordem (arv->left);
      printf ("%d, ", arv->value);
      in_ordem (arv->right);
   }
}

void pos_ordem (BST *arv){
    if (BST){
        pos_ordem (arv->left);
        pos_ordem (arv->right);
        printf("%d, ", arv->value);
    }
}
*/
