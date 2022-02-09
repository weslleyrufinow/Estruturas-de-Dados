#include <stdio.h>
#include <string.h>
#include "avl.h"

typedef struct car {
    char *name;
    char *brand;
} Car;

int comparCar(const void *a, const void *b) {
    Car *c1 = (Car*)a;
    Car *c2 = (Car*)b;
    return strcmp(c1->name, c2->name);
}

void printfTreeCar(avl_node_t *tree) {
    Car *c; 
    if (tree != NULL) {
        c = (Car*)tree->item;
        
        printfTreeCar(tree->left);
        printf("(%s, %s) ", c->name, c->brand);
        printfTreeCar(tree->right);
    }
}

/**
 * gcc avl.c avl-exemplo-car.c -c && gcc avl.o avl-exemplo-car.o && ./a.out
 * */
int main() {
    Car c[] = { {"207","Peugeot"}, 
                {"Gol","Volkswagen"},
                {"HB20","Hyundai"},
                {"Focus","Ford"},
                {"QQ","Chery"} };

    avl_t *treeCar = avl_alloc(comparCar);

    avl_insert(treeCar, &c[0]);
    avl_insert(treeCar, &c[1]);
    avl_insert(treeCar, &c[2]);
    avl_insert(treeCar, &c[3]);
    avl_insert(treeCar, &c[4]);

    printfTreeCar(treeCar->root);
    printf("\n");

    Car car = {"HB20", NULL}; //soh eh necessario o nome para comparar
    avl_delete(treeCar, &car);

    printfTreeCar(treeCar->root);
    printf("\n");

    avl_delete_min(treeCar);

    printfTreeCar(treeCar->root);
    printf("\n");

    return 0;
}