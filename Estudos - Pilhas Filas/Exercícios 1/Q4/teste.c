#include <stdio.h>
#include <stdlib.h>

int main(){

    float NUM, P, I ;

     scanf("%f",&NUM);

    P = 0;

    I = 0;

    while (NUM > 0){

            if (NUM % 2 == 0){

                    P = P + 1;

            }else{

                    I = I + 1;

             }

             NUM = NUM - 1;

    }

    printf("%f",P); 

    printf("%f",I);


return 0;}