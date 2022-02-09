#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Ponto2d.h"

struct Point2d{
    float x;
    float y;
};

Point2d *Point2d_create(float a, float b){
    Point2d *p = malloc(sizeof(Point2d));
    p->x=a;
    p->y=b;
return p;}

Point2d *Point2d_delete(Point2d *p){
    free(p);
    p=NULL;
return 0;}

float Point2d_getX(Point2d *p){
return p->x;}
float Point2d_getY(Point2d *p){
return p->y;}

Point2d *Point2d_setX(Point2d *p, float n){
    p->x=n;
return p;}
Point2d *Point2d_setY(Point2d *p, float n){
    p->y=n;
return p;}

float Point2d_distance(Point2d *a,Point2d *b){
    float c,d,r,auxa,auxb;
    auxa = (b->x) - (a->x) ;
    auxb = (b->y) - (a->y) ;
    c = pow(auxa,2);
    d = pow(auxb,2);
    r=c+d;

return sqrt(r);}