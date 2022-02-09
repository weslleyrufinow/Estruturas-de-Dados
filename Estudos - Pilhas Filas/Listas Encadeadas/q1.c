#include <stdio.h>
#include <stdlib.h>
#include "List.h"

void print( void *element){
    printf("%d ",*((int *)element));
}

int compar(void *a,void *b){
    int aux = 2;
    if(*((int *)a) == *((int *)b))
        aux = 0;
    if(*((int *)a) > *((int *)b))
        aux = 1;
    if(*((int *)a) < *((int *)b))
        aux = -1;
return aux;}

int main(){
 int i,a[] = {1,2,3,4,5,6,7,8,9,10};
 List *l = List_create();

 for(i = 0; i<10; i++){
     List_insertEnd(l,&a[i]);
     //List_insertBegin(l,&a[i]);
 }

 List_destroy(l);
return 0;}