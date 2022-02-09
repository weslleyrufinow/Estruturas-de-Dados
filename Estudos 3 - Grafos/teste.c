#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"
//gcc teste.c ; ./a.out

void var(int *n){
    *n+=1;
}
int main(){
    int n = 0, *a;
    printf("%d\n",n);
    var(&n);
    printf("%d\n",n);

    *a = 1;
    *a += 1;

    printf("%d\n",*a);

return 0;}