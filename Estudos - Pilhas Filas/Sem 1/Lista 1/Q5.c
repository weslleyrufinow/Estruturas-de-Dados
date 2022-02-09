/*
Questão 5
Considere a seguinte declaração: 𝚒𝚗𝚝 𝚊, *𝚋, **𝚌, ***𝚍; 
escreva um programa que leia a variável a e calcule e exiba:
    o dobro, o triplo e o quádruplo desse valor utilizando apenas os ponteiros 𝗯, 𝗰 e 𝗱.

O ponteiro 𝗯 deve ser usado para calcular o dobro, 𝗰, o triplo, e 𝗱, o quádruplo.
*/
#include <stdio.h>
#include <stdlib.h>

int main(){
    int a=1, *b=&a, **c=&b, ***d=&c;

    //scanf("%d",a);

    printf("       a = %d\n",   a*1);
    printf("  *b * 2 = %d\n",  *b*2);
    printf(" **c * 3 = %d\n", **c*3);
    printf("***d * 4 = %d\n",***d*4);

return 0;}