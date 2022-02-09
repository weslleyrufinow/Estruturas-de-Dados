/*
Questão 3
Usando coloração limitada por borda, crie uma versão da função 𝚌𝚘𝚕𝚘𝚛𝚒𝚗𝚐𝙰𝚛𝚎𝚊() no arquivo 𝗰𝗼𝗹𝗼𝗿𝗶𝗻𝗴.𝗰 
e faça um programa para testá-la.

*/

#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
#define DIM 9

void show(int [DIM][DIM]);
void color(int);
void coloringArea(int [DIM][DIM], int, int, int);
void coloringArea2(int [DIM][DIM], int, int, int);

int main() {
    int i, j, n;
    int img[DIM][DIM] = {{0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 1, 0, 0, 0, 0},
                         {0, 0, 0, 1, 1, 1, 0, 0, 0},
                         {0, 0, 1, 1, 1, 1, 1, 0, 0},
                         {0, 1, 1, 1, 1, 1, 1, 1, 0},
                         {0, 0, 2, 0, 0, 0, 2, 0, 0},
                         {0, 0, 2, 0, 0, 0, 2, 0, 0},
                         {0, 0, 2, 2, 2, 2, 2, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0}};
    while (1) {
        show(img);
        printf("\nDigite uma nova cor (ou aperte -1 para sair). ");
        scanf("%d", &n);
        if (n<0) break;
        do {
            printf("Posição? ");
            scanf("%d %d", &i, &j);
        } while (i<0 || i>=DIM || j<0 || j>=DIM);
        coloringArea(img, i, j, n);
    }

    return 0;
}//FINAL DA MAIN

void color(int color) {
    switch (color) {
        case 0 : printf("\033[107m  \033[m"); break;//branco
        case 1 : printf("\033[102m  \033[m"); break;//verde
        case 2 : printf("\033[100m  \033[m"); break;//preto
        case 3 : printf("\033[103m  \033[m"); break;//amarelo
        case 4 : printf("\033[106m  \033[m"); break;//azul
    }
}

void show(int img[DIM][DIM]) {
    int i, j;

    printf("   0 1 2 3 4 5 6 7 8 \n");
    for (i = 0; i < DIM; i++) {
        printf("%d ", i);
        for (j = 0; j < DIM; j++)
            color(img[i][j]);
        printf("\n");
    }
}

//converte coord. (x,y) em um único valor que referencia a coordenada
int *pixel(int i, int j) {
    int *p = (int*) malloc(sizeof(int));
    *p = i * DIM + j;
    return p;
}

void coloringArea(int img[DIM][DIM], int i, int j, int n) {
    Queue *q = Queue_create(DIM*DIM);
    int p, a = img[i][j];

    img[i][j] = n;
    Queue_push(q, pixel(i, j));
    
    while (!Queue_isEmpty(q) && a != n) {
        p = *((int*)Queue_pop(q));
        i = p / DIM;
        j = p % DIM;

        if (img[i][j+1] == a) { 
            img[i][j+1] = n; 
            Queue_push(q, pixel(i, j+1));
        }
        if (img[i+1][j] == a) { 
            img[i+1][j] = n; 
            Queue_push(q, pixel(i+1, j));
        }
        if (i > 0)
            if (img[i-1][j] == a) { 
                img[i-1][j] = n; 
                Queue_push(q, pixel(i-1, j));
            }
        if (j > 0)
            if (img[i][j-1] == a) { 
                img[i][j-1] = n; 
                Queue_push(q, pixel(i, j-1));
            } 
    }
    Queue_destroy(q);
}

void coloringArea2(int img[DIM][DIM], int i, int j, int n) {
    //n - nova cor
    //i , j - coordenada para mudar a cor
    Queue *q = Queue_create(DIM*DIM);
    int p, a = img[i][j];  //a recebe o valor da coord. dada de img

    img[i][j] = n;//img recebe a cor nova na coordenada dada
    Queue_push(q, pixel(i, j));
    
    while (!Queue_isEmpty(q) && a != n) {
        p = *((int*)Queue_pop(q));
        i = p / DIM; //conversão de x
        j = p % DIM; //conversão de y

        if (img[i][j+1] != a && img[i][j+1] != n) { 
            img[i][j+1] = n; 
            Queue_push(q, pixel(i, j+1));
        }
        if (img[i+1][j] != a&& img[i+1][j] != n) { 
            img[i+1][j] = n; 
            Queue_push(q, pixel(i+1, j));
        }
        /*
//eu
        if (img[i-1][j-1] == a) { 
            img[i-1][j-1] = n; 
            Queue_push(q, pixel(i-1, j-1));
        }
        if (img[i-1][j+1] == a) { 
            img[i-1][j+1] = n; 
            Queue_push(q, pixel(i-1,j+1));
        }
        if (img[i+1][j-1] == a) { 
            img[i+1][j-1] = n; 
            Queue_push(q, pixel(i+1,j-1));
        }
        if (img[i+1][j+1] == a) { 
            img[i+1][j+1] = n; 
            Queue_push(q, pixel(i+1,j+1));
        }
//eu
    */
        if (i > 0)
            if (img[i-1][j] != a&& img[i-1][j] != n) { 
                img[i-1][j] = n; 
                Queue_push(q, pixel(i-1, j));
            }
        if (j > 0)
            if (img[i][j-1] != a&& img[i][j-1] != n) { 
                img[i][j-1] = n; 
                Queue_push(q, pixel(i, j-1));
            } 
    }
    Queue_destroy(q);
}