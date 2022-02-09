//CONVERTE EXP INFIXA PARA POSFIXA
//SÓ FUNCIONA COM PARENTESIS, PRIORIDADES BEM DEFINIDAS E NUMEROS COM SO UM DIGITO

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "StackInt.h"
#define size 256

char *posfixa(char *in){
    StackInt *stk = StackInt_create(size);
    char     *out =  malloc(sizeof(char));
    int         i,j;
    i = j = 0;

    for(i = 0 ; in[i] ; i++){
        if(isdigit(in[i]))
            out[j++] = in[i];
        else if(strchr("+-*/",in[i]))
                StackInt_push(stk,in[i]);
        else if(in[i] == ')')
                out[j++] = StackInt_pop(stk);
    }
    out[j] = '\0';
    StackInt_destroy(stk);
return out;}

int main(){
    char exp[size];
    printf("Infixa: ");
    scanf("%s", exp);
    printf("Posfixa: %s\n",posfixa(exp));
return 0;}
