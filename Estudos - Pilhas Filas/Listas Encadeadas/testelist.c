#include <stdio.h>
#include <stdlib.h>
#include "List.h"

void print( void *element){
    printf("%d ",*((int *)element));
}

int compar(void *a,void *b){
    int aux = -1;
    /*
    int x = *((int *)a);
    int y = *((int *)b);
    if(x == y)
        aux = 0;*/
    if(*((int *)a) == *((int *)b))
        aux = 0;
        
return aux;}

int main(){
 int i,a[] = {1,2,3,4,5,6,7,8,9,10};
 List *l = List_create();
 void *paux;

 for(i = 0; i<10; i++){
     List_insertEnd(l,&a[i]);
     //List_insertBegin(l,&a[i]);
 }

 List_print(l,print);

 i = 5;
 paux = &i;
 paux = List_findAndRemove(l,paux,compar);
 if(paux)
    printf("%d\n", *((int *)paux) );

 List_print(l,print);

 List_destroy(l);
return 0;}