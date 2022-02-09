#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
qsort percisa de uma funcao de comparacao que retorne:
 0 if x == y
 <0 if x<y
 >0 if x>y 
*/
struct student{
    int id;
    char nome[20];
};
typedef struct student student;

int compareString(const void *x, const void *y){
    student *st1 = (student *) x;
    student *st2 = (student *) y;
return strcmp(st1->nome,st2->nome);}

int main(){
    int i;
    struct student st[4] = {{444,"bob"},{333,"adam"},
                            {222,"dany"},{111,"cleo"}};

    qsort(st,4,sizeof(struct student), compareString);

    for(i = 0; i<4 ; i++){
        printf("%d %s\n",st[i].id,st[i].nome);
    }
return 0;}