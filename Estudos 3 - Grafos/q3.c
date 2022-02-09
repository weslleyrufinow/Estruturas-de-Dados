#include <stdio.h>
#include <stdlib.h>
#include "Graphq3.h"
#include "List.h"

//gcc -c Graphq3.c List.c q3.c && gcc -o q3.out Graphq3.o List.o q3.o && ./q3.out
int main(){
    Node m[15] = {{0},{1},{2},{3},{4},{5},{6},{7},{8},{9},{10},{11},{12},{13},{14}};
    Node *l;
    int i,n[15] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
    float f[] = {2,2.8,3,3.6,4,4.5,5,7,7.3};
    //0=2 |1=2.8 |2=3 |3=3.6 |4=4 |5=4.5 |6=5 |7=7 |8=7.3
Graph *g = Graph_create(compar);
Edge *e = NULL;

    int t = 12;
    float *dist;
    int *ant;

for(i = 14 ; i >= 0; i--){
    Graph_insert(g,&n[i]);
}

for(i = 0; i < 1; i++){
    Graph_link(g,&n[0],&n[1],&f[2]);
    Graph_link(g,&n[0],&n[3],&f[0]);
    //0=2 |1=2.8 |2=3 |3=3.6 |4=4 |5=4.5 |6=5 |7=7 |8=7.3
    Graph_link(g,&n[1],&n[4],&f[0]);
    //0=2 |1=2.8 |2=3 |3=3.6 |4=4 |5=4.5 |6=5 |7=7 |8=7.3
    Graph_link(g,&n[2],&n[0],&f[3]);
    Graph_link(g,&n[2],&n[3],&f[2]);
    //0=2 |1=2.8 |2=3 |3=3.6 |4=4 |5=4.5 |6=5 |7=7 |8=7.3
    Graph_link(g,&n[3],&n[4],&f[2]);
    Graph_link(g,&n[3],&n[7],&f[0]);
    //0=2 |1=2.8 |2=3 |3=3.6 |4=4 |5=4.5 |6=5 |7=7 |8=7.3
    Graph_link(g,&n[4],&n[5],&f[7]);
    Graph_link(g,&n[4],&n[8],&f[0]);
    Graph_link(g,&n[4],&n[9],&f[8]);
    //0=2 |1=2.8 |2=3 |3=3.6 |4=4 |5=4.5 |6=5 |7=7 |8=7.3
    Graph_link(g,&n[5],&n[9],&f[0]);
    //0=2 |1=2.8 |2=3 |3=3.6 |4=4 |5=4.5 |6=5 |7=7 |8=7.3
    Graph_link(g,&n[6],&n[2],&f[0]);
    //0=2 |1=2.8 |2=3 |3=3.6 |4=4 |5=4.5 |6=5 |7=7 |8=7.3
    Graph_link(g,&n[7],&n[6],&f[2]);
    Graph_link(g,&n[7],&n[11],&f[4]);
    //0=2 |1=2.8 |2=3 |3=3.6 |4=4 |5=4.5 |6=5 |7=7 |8=7.3
    Graph_link(g,&n[8],&n[7],&f[2]);
    Graph_link(g,&n[8],&n[12],&f[4]);
    //0=2 |1=2.8 |2=3 |3=3.6 |4=4 |5=4.5 |6=5 |7=7 |8=7.3
    Graph_link(g,&n[9],&n[8],&f[7]);
    Graph_link(g,&n[9],&n[13],&f[4]);
    //0=2 |1=2.8 |2=3 |3=3.6 |4=4 |5=4.5 |6=5 |7=7 |8=7.3
    Graph_link(g,&n[10],&n[6],&f[4]);
    Graph_link(g,&n[10],&n[11],&f[2]);
    //0=2 |1=2.8 |2=3 |3=3.6 |4=4 |5=4.5 |6=5 |7=7 |8=7.3
    Graph_link(g,&n[11],&n[6],&f[6]);
    Graph_link(g,&n[11],&n[10],&f[2]);
    Graph_link(g,&n[11],&n[12],&f[2]);
    //0=2 |1=2.8 |2=3 |3=3.6 |4=4 |5=4.5 |6=5 |7=7 |8=7.3
    Graph_link(g,&n[12],&n[11],&f[2]);
    Graph_link(g,&n[12],&n[13],&f[7]);
    //0=2 |1=2.8 |2=3 |3=3.6 |4=4 |5=4.5 |6=5 |7=7 |8=7.3
    Graph_link(g,&n[13],&n[12],&f[7]);
    Graph_link(g,&n[13],&n[14],&f[5]);
    //0=2 |1=2.8 |2=3 |3=3.6 |4=4 |5=4.5 |6=5 |7=7 |8=7.3
    Graph_link(g,&n[14],&n[12],&f[1]);
}
Graph_print(g,print);

e = Edge_find(g,&n[0],&n[1]);


    ant = malloc(g->n * sizeof(int));
    dist = malloc(g->n * sizeof(float));

    dijkstra1(g, t, ant, dist);


    for (int i = 0; i < g->n; i++) {
        printf("%d ", ant[i]);
    }


    printf("\n");

Edge_print(e);

Graph_destroy(g);
return 0;}