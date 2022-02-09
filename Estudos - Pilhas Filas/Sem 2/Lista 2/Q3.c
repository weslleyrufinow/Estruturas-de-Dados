#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ponto2d.h"

int main() {
    Point2d *p1 = Point2d_create(0, 0);
    Point2d *p2 = Point2d_create(0, 0);
    Point2d *p3 = Point2d_create(0, 0);
    float a,b,c,r;
    
    printf("Vertice 1 X(e então enter), Y(e então enter): \n");
    scanf("%f",&a); scanf("%f",&b); Point2d_setX(p1,a); Point2d_setY(p1,b);

    printf("Vertice 2 X(e então enter), Y(e então enter): \n");
    scanf("%f",&a); scanf("%f",&b); Point2d_setX(p2,a); Point2d_setY(p2,b);

    printf("Vertice 3 X(e então enter), Y(e então enter): \n");
    scanf("%f",&a); scanf("%f",&b); Point2d_setX(p3,a); Point2d_setY(p3,b);

    
    a = Point2d_distance(p1, p3);
    b = Point2d_distance(p1, p2);
    c = Point2d_distance(p2, p3);
    /*
    printf("a  = %f\n", a);
    printf("b  = %f\n", b);
    printf("c  = %f\n", c);
    */
    r = a + b + c;
    printf("Distancia  = %f\n", r);
    
    return 0;
}