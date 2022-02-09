/*
Questão 2:
Crie uma estrutura 𝗖𝗮𝗿 com os membros: 𝗯𝗿𝗮𝗻𝗱, 𝗺𝗼𝗱𝗲𝗹, 𝘃𝗮𝗹𝘂𝗲, 𝗸𝗺_𝗹 e 𝗸𝗺_𝗵. 

Crie uma função que retorne o ponteiro para um vetor de 𝗡 elementos tipo 𝘀𝘁𝗿𝘂𝗰𝘁𝗖𝗮𝗿 alocado dinamicamente. 

Caso 𝗡 seja negativo ou igual a zero, um ponteiro nulo deverá ser retornado. 
Use a função para criar um vetor de tamanho 5, preencha suas informações e imprima o vetor.

*/
#include <stdio.h>
#include <stdlib.h>

typedef struct{
   char brand[100];
   char model[100];
   float value;
   float km_l;
   float km_h;
}car;

car *vet(int n){
    car *cada=NULL;
    int i;

    if(n>0){
        cada = malloc(sizeof(car)*n);
        printf("Lendo os valores: \n");
        for(i = 0; i<n; i++){
            printf("Indice %d\n",i);

            printf("Digite a marca: \n"); 
            scanf("%s",cada[i].brand);

            printf("Digite o modelo: \n"); 
            scanf("%s",cada[i].model);

            printf("Digite o valor: \n"); 
            scanf("%f",&(cada[i]).value);

            printf("Digite a Quilometragem por litro: \n"); 
            scanf("%f",&(cada[i]).km_l);

            printf("Digite a maxima de km/h: \n"); 
            scanf("%f",&(cada[i]).km_h);

            system("clear");//linux
            //system("cls");//windows
        }
        printf("Imprimindo o/os vetores: \n");

        for(i = 0; i<n; i++){
            printf("Marca: %s\n",cada[i].brand);
            printf("Modelo: %s\n",cada[i].model);
            printf("Valor: %.2f\n",cada[i].value);
            printf("Km/L: %.2f\n",cada[i].km_l);
            printf("Velocidade maxima: %.2f\n",cada[i].km_h);
            printf("\n***************************************\n");
        }

    }
return cada;}

int main(){
    int n=2;
    car *cad=0;

    cad = vet(n);

    if(cad==NULL){
        printf("NULL\n");
    }

    free(cad);
    cad = NULL;
    return 0;
}