#include <stdio.h>
#include <stdlib.h>
//exemplo de uso de ponteiro para void
int main(){
    int n = 5;
    void *p;
    p = &n;
        printf( "%d\n",*((int *)p) );
return 0;}