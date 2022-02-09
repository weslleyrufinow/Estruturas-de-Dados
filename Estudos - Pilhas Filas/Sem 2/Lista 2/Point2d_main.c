#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Ponto2d.h"

struct Point2d{
    float x;
    float y;
};

int main() {
    Point2d *p1 = Point2d_create(1, 4);
    Point2d *p2 = Point2d_create(3, 7);
    
    printf("p1 = (%.2f, %.2f)\n", p1->x, p1->y);
    printf("p2 = (%.2f, %.2f)\n", p2->x, p2->y);
    
    p1->x = 0;
    p1->y = 5;
    
    printf("p1 = (%.2f, %.2f)\n", p1->x, p1->y);
    
    printf("Distancia  = %f\n", Point2d_distance(p1, p2));
    // saida esperada: 'Distancia  = 3.605551'
    
    return 0;
}

