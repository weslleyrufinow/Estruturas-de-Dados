#include <stdio.h>
#include <stdlib.h>

/*
qsort percisa de uma funcao de comparacao que retorne:
 0 if x == y
 <0 if x<y
 >0 if x>y 
*/
//fazer isso para compara as strings
struct student{
    int id;
    char nome[20];
};
typedef struct student student;

int compareId(const void *x, const void *y){
    student *st1 = (student *) x;
    student *st2 = (student *) y;
return st1->id - st2->id;}

int main(){
    int i;
    struct student st[4] = {{444,"bob"},{333,"adam"},
                            {222,"dany"},{111,"cleo"}};

    //vetor, numero de elementos do vetor, sizeof(tipo do vetor),funcao que retorna valor inteiro
    qsort(st,4,sizeof(struct student), compareId);

    for(i = 0; i<4 ; i++){
        printf("%d %s\n",st[i].id,st[i].nome);
    }
return 0;}