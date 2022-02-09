/*
    Questão 1: Crie uma função que receba uma string e retorne o ponteiro para uma nova string invertida.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *inverte(char word[], int t){
    char *word2=malloc(t+1);
    int i,j;
    for(i=t-1,j=0; i>=0,j<t; i--,j++){
        word2[j]=word[i];
    }
    word2[j]='\0';
return word2;} 

int main(){

    char word[100]={"amor"}, *pont=0;

    pont = inverte(word,strlen(word));

    puts(word);
    puts(pont);

return 0;}