/*
Questão 4
Escreva uma função chamada 𝗺𝗮𝗽 que receba como parâmetro um vetor de números reais 𝗔 contendo 𝗡 elementos, 
um número real 𝗞 e um ponteiro para função ( 𝚏𝚕𝚘𝚊𝚝 (*𝚘𝚙𝚎𝚛𝚊𝚝𝚒𝚘𝚗) (𝚏𝚕𝚘𝚊𝚝 𝚊, 𝚏𝚕𝚘𝚊𝚝 𝚋) ). 

A função deve retornar o ponteiro para um novo vetor 𝗕 de 𝗡 elementos alocados dinamicamente, 
em que 𝙱[ 𝚒 ] = 𝚘𝚙𝚎𝚛𝚊𝚝𝚒𝚘𝚗( 𝙰[ 𝚒 ], 𝚔 ).

*/
#include <stdio.h>
#include <stdlib.h>

float opera(float a, float b){
return a+b;}

float *map(float A[],int N,float K,float (*opera)(float a, float b)){
    int i;
    float *B;
    B = malloc(sizeof(float) * N);

    for(i=0 ; i<N ; i++){
        B[i] = opera(A[i],K);
        printf("%.2f(A[i]) + %.2f(K) = %.2f(B[i])\n",A[i],K,B[i]);
    }

return B;}

int main(){
    int i;
    float A[3] = {1,2,3}, *vetor;
    
    vetor = map(A,3,1,opera);

    printf("\nVetor resultante: ");
    for(i=0 ; i<3 ; i++){
        printf("%.2f ",vetor[i]);
    }
    printf("\n");

return 0;}