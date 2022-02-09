#include <stdio.h>
#include <string.h>
#include "rbtree.h"

typedef struct car {
    char *name;
    char *brand;
} Car;

int comparCar(const void *a, const void *b) {
    Car *c1 = (Car*)a;
    Car *c2 = (Car*)b;
    return strcmp(c1->name, c2->name);
}

void printfTreeCar(rbtree_node_t *tree) {
    Car *c; 
    if (tree != NULL) {
        c = (Car*)tree->item;
        
        printfTreeCar(tree->left);
        printf("(%s, %s) ", c->name, c->brand);
        printfTreeCar(tree->right);
    }
}

/**
 * gcc rbtree.c rbtree-exemplo-car.c -c && gcc rbtree.o rbtree-exemplo-car.o && ./a.out
 * */
int main() {
    Car c[] = { {"207","Peugeot"}, 
                {"Gol","Volkswagen"},
                {"HB20","Hyundai"},
                {"Focus","Ford"},
                {"QQ","Chery"} };

    rbtree_t *treeCar = rbtree_alloc(comparCar);

    rbtree_insert(treeCar, &c[0]);
    rbtree_insert(treeCar, &c[1]);
    rbtree_insert(treeCar, &c[2]);
    rbtree_insert(treeCar, &c[3]);
    rbtree_insert(treeCar, &c[4]);

    printfTreeCar(treeCar->root);
    printf("\n");

    Car car = {"HB20", NULL}; //soh eh necessario o nome para comparar
    rbtree_delete(treeCar, &car);

    printfTreeCar(treeCar->root);
    printf("\n");

    rbtree_delete_min(treeCar);

    printfTreeCar(treeCar->root);
    printf("\n");

    return 0;
}