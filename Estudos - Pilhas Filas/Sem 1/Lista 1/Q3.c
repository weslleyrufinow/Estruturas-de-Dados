/*
Questão 3
Escreva uma função que receba por parâmetro os valores inteiros e positivos 𝗠 e 𝗡 
e retorne um ponteiro para uma matriz 𝗠 × 𝗡 alocada dinamicamente. 

Essa matriz deverá ter todas as posições inicializadas com zero.
 */
#include <stdio.h>
#include <stdlib.h>
#define TAM 3

int **fun(int m,int n){
    int i,j,**mat;
    
    mat = malloc(sizeof(int*) * m);
    for(i=0; i<m; i++){
        mat[i] = malloc(sizeof(int) * n);
    }

    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++){
            mat[i][j] = 0;
        }
    }

    return mat;
}

int main(){
    int i,j,m=TAM,n=TAM;
    int **matriz=NULL;

    matriz = fun(m,n);

    for (i = 0; i < m; i++){
        printf("\n");
        for (j = 0; j < n; j++){
            printf("%d ",matriz[i][j]);
        }
    }
    printf("\n");
    
    return 0;
}