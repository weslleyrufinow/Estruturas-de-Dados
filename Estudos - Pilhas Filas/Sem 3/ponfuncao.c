#include <stdio.h>
#include <stdlib.h>
//Exemplo de um ponteiro para função

int f(int x){

return x*x;}

int main(){
    int (*g)(int);
    g=f;
    printf("%d\n",g(5));    
return 0;}