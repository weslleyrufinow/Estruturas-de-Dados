#include<stdio.h>
#include<stdlib.h>
#include"Graphq3.h"

//gcc -c heapmain.c Graphq3.c && gcc -o heapmain.out heapmain.o Graphq3.o && ./heapmain.out

int main(){
    Node m[15] = {{0},{1},{2},{3},{4},{5},{6},{7},{8},{9},{10},{11},{12},{13},{14}};
    Node *t;

    int i,aux;
    //Heap *heap = CreateHeap(15, 0); //Min Heap

    int n[15] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
    float f[] = {2,2.8,3,3.6,4,4.5,5,7,7.3};
    //0=2 |1=2.8 |2=3 |3=3.6 |4=4 |5=4.5 |6=5 |7=7 |8=7.3
    Graph *g = Graph_create(compar);
    Vertex **path = NULL,*v;
/*    
for(i = 14 ; i >= 0; i--){
    Graph_insert(g,&n[i]);
}
*/
for(i = 0 ; i < 15; i++){
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
//Graph_print(g,print);

path = Busca_DFS(g,g->first->value);

printf("Resultado da busca em profundidade:\n");
for (int i = 0; i < g->n; i++) {
    print(path[i]->value);
    //insert(heap,path[i]);
    printf(" ");
}
printf("\n");

dijkstra(g,g->first);

//print_heap(heap);
/*
for (int i = 0; i < g->n; i++) {
    v = PopMin(heap);
    //printf("Pop: ");print(v->value);printf("\n");
    //print_heap(heap);
}
*/


Graph_destroy(g);
}