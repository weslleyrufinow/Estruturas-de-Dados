//CONVERTE EXP INFIXA PARA POSFIXA
//FUNCIONA COM/SEM PARENTESIS, PRIORIDADES BEM/NÃO DEFINIDAS E COM NUMEROS DE MAIS DE UM DIGITO 

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "StackInt.h"
#define size 256
// gcc StackInt.c Posfix_3.c -c ;gcc StackInt.o Posfix_3.o ; ./a.out
int priority(char c){
    switch (c){
        case '(': return 0;
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
    }
return -1;}

int evaluate(char *expression){
    StackInt *stack = StackInt_create(size);
    int i,j,x,y,z;
    char *subexp = malloc(strlen(expression));

    for(i = 0; expression[i] ; i++){
        if(isdigit(expression[i])){
            
            for( j = 0; isdigit(expression[i]); j++, i++ )
                subexp[j] = expression[i];
            subexp[j] = '\0';
            StackInt_push(stack,atoi(subexp));
        }

        if( strchr("+-*/",expression[i]) ){
            y = StackInt_pop(stack);
            x = StackInt_pop(stack);
            switch(expression[i]){
                case '+': StackInt_push(stack,x+y);break;
                case '-': StackInt_push(stack,x-y);break;
                case '*': StackInt_push(stack,x*y);break;
                case '/': StackInt_push(stack,x/y);break;
            }
        }
    }

    z = StackInt_pop(stack);
    StackInt_destroy(stack);
return z;}

char *posfixa(char *in){
    StackInt *stk = StackInt_create(size);
    char     *out =  malloc(sizeof(char));
    int         i,j;
    i = j = 0;

    for(i = 0 ; in[i] ; i++){

        if(in[i] == '(')
            StackInt_push(stk,in[i]);
            
        if(isdigit(in[i]))
            out[j++] = in[i];
        else if(strchr("+-*/",in[i])){
            out[j++] = ' ';
            while ( !StackInt_isEmpty(stk) && ( priority(in[i]) <= priority(StackInt_top(stk)) ) )
                out[j++] = StackInt_pop(stk);

            StackInt_push(stk,in[i]);
        }
        else if(in[i] == ')'){
            while (StackInt_top(stk) != '(')
                out[j++] = StackInt_pop(stk);
            StackInt_pop(stk);
                
        }
    }
    while(!StackInt_isEmpty(stk))
        out[j++] = StackInt_pop(stk);
    out[j] = '\0';
    StackInt_destroy(stk);
return out;}

int main(){
    char exp[size];
    printf("Infixa: ");
    scanf("%[^\n]s", exp);
    printf("Posfixa: %s\n",posfixa(exp));
    printf("Resultado: %d\n",evaluate( posfixa(exp) ) );
return 0;}
