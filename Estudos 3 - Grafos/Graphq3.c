#include <stdio.h>
#include <stdlib.h>
#include "Graphq3.h"
#define inf 9999
/*
//Ponteiro pro início de uma lista de nós
struct Graph {
    int n;
    Vertex *first;
    int (*compar)(void *, void *);
};


struct Vertex {
    void *value;
    Edge *first;
    Vertex *next;
    int vizited;
};

struct Edge {
    Edge *next;
    Vertex *origin;
    Vertex *target;
    float *dist;
};
*/

Vertex *not_visited(Edge *edge){
Edge *e = NULL;
    if(edge){
        e = edge;
        while(e){
            if(e->target->vizited == 0)
                return e->target;
            e = e->next;
        }
    }
}

void DFS(Vertex *v, Vertex **path, int *cont){
    Vertex *k = NULL;
    if(v){
        v->vizited = 1;
        path[*cont] = v;

        while(k = not_visited(v->first)){
            *cont+=1;
            DFS(k,path,cont);
        }
        
    }
}

Vertex **Busca_DFS(Graph *g, void *start){
    Vertex **path = NULL, *v = NULL;
    int i, cont = 0;
    if(g && start){
        if(v = Vertex_find(g,start)){
            path = malloc( (g->n) * sizeof(Vertex*) );
            for(i = 0; i < (g->n) ; i++){
                path[i] = NULL;
            }
            DFS(v,path,&cont);
        }
    }
return path;}

int compar(void *x, void *y){
    int a,b,n;
    a = *((int *)x);
    b = *((int *)y);
    n = a - b;
    //printf("a: %d b: %d n: %d\n",a,b,n);
return n;}

void print(void *n){
    int a = *((int *)n);
    if(n){
        printf("%d",a);
    }else{
        printf("NULL");
    }
}

void print_float(void *n){
    float a = *((float *)n);
    if(n){
        printf("%.2f",a);
    }else{
        printf("NULL");
    }
}

Graph *Graph_create(int (*compar)(void *, void *)) {
    Graph *g = malloc(sizeof(Graph));
    if (g && compar) {
        g->n = 0;
        g->first = NULL;
        g->compar = compar;
    }
    return g;
}

void Graph_destroy(Graph *g) {
    if (g) {
        Vertex_destroy(g->first);
        free(g);
    }
}

void Graph_insert(Graph *g, void *value) {
    Vertex *new = NULL;
    if(g && value){
        new = Vertex_create(value);
        new->next = g->first;
        g->first = new;
        g->n++;
    }
}

void Graph_link(Graph *g, void *value1, void *value2, void *dist) {//value1 origem; value2 destino
    Vertex *o = NULL, *t = NULL;
    Edge *e = NULL, *new = NULL;

    if(g && value1 && value2){
        o = Vertex_find(g,value1);
        t = Vertex_find(g,value2);
        if(o && t){
            e = o->first;
            if (e == NULL){
                o->first = Edge_create();
                o->first->origin = o;
                o->first->target = t;
                o->first->dist = dist;
            }else{  
                new = Edge_create();
                new->origin = o;
                new->target = t;
                new->dist = dist;
                new->next = o->first;
                o->first = new;
            }
        }
    }
}

void Graph_delete(Graph *g, void *value) {
    Vertex *v = NULL, *cur = NULL, *vant = NULL;
    Edge *e = NULL, *ant = NULL;

    if(g && value){
        v = Vertex_find(g,value);
        if(v){
            cur = g->first;

            while(cur){
                ant = NULL;
                e = cur->first;
                while(e){
                    if(g->compar(value,e->target->value) == 0){
                        if(ant){
                            ant->next = e->next;
                        }else{
                            cur->first = e->next;
                        }
                        free(e);
                        break;
                    }
                    ant = e;
                    e = e->next;
            }
            cur = cur->next;
        }
        cur = g->first;
        while(cur){
            if(g->compar(value,cur->value) == 0){
                if(vant){
                    vant->next = cur->next;
                }else{
                    g->first = cur->next;
                }
                free(cur);
            }
            vant = cur;
            cur = cur->next;
        }
        g->n--;
        }

    }else{
        printf("Grafo NULL ou value NULL");
    }
}

void Graph_print(Graph *g, void (*print)(void *)){
    Vertex *v = NULL;
    Edge *e = NULL;
    if(g && print){
        printf("Numero de vertices: %d\n",g->n);
        v = g->first;
        while(v){
            printf("V("); 
            print(v->value); 
            printf(") \t E:{");
            e = v->first;
            while(e){
                printf("(");
                //print(v->value);
                print(e->origin->value);
                printf(",");
                print(e->target->value);
                printf(") D:");
                print_float(e->dist);
                e = e->next;
                printf("%s",e ? ", " : "}");
            }
            printf("\n");

            v = v->next;
        }
        
    }else{
        printf("Grafo NULL ou erro na funcao print\n");
    }
    
}

Vertex *Vertex_create(void *value) {
    Vertex *v = malloc(sizeof(Vertex));
    if (v) {
        v->value = value;
        v->first = NULL;
        v->next = NULL;
        v->vizited = 0;
        v->fechado = 0;
    }
    return v;
}

void Vertex_destroy(Vertex *v) {
    Vertex *temp = NULL;
    if (v) {
        while (v) {
            Edge_destroy(v->first);
            temp = v;
            v = v->next;
            free(temp);
        }
    }
}

Vertex *Vertex_find(Graph *g, void *value) {
    Vertex *cur = NULL;
    if (g && value) {
        cur = g->first;
        while (cur) {
            /*
            printf("\n");
            printf("cur: ");print(cur->value);printf(" | ");
            printf("value: ");print(value);printf(" | ");
            printf("cur->value: ");print(value);printf(" ");
            */
            if (g->compar(value, cur->value) == 0)
                break;
            cur = cur->next;
        }
    }
    //printf("return cur: ");print(cur->value);printf("\n");
    return cur;
}

Edge *Edge_create() {
    Edge *e = malloc(sizeof(Edge));
    if (e) {
        e->next = NULL;
        e->origin = NULL;
        e->target = NULL;
        e->dist = NULL;
    }
    return e;
}

void Edge_destroy(Edge *e) {
    Edge *temp = NULL;
    if (e) {
        while (e) {
            temp = e;
            e = e->next;
            free(temp);
        }
    }
}

Edge *Edge_find(Graph *g, void *value1, void *value2) {
    Vertex *o = NULL, *t = NULL;
    Edge *e = NULL;
    if(g && value1 && value2){
        o = Vertex_find(g,value1);
        t = Vertex_find(g,value2);        
        if(o && t){
            e = o->first;
            while(e){
                if(g->compar(value2,e->target->value) == 0){
                    return e;
                }
                e = e->next;
            }
            
        }
    }
return NULL;}

void Edge_print(Edge *e){
    if(e){
        printf("Origem: ");print(e->origin->value);
        printf(" | Destino:");print(e->target->value);
        printf(" | Dist:");print_float(e->dist);printf("\n");
    }else{
        printf("Erro de segmentação || NULL || aresta inexistente\n");
    }
}

Heap *CreateHeap(int capacity,int heap_type){
    Heap *h = (Heap * ) malloc(sizeof(Heap *)); //one is number of heap

    //check if memory allocation is fails
    if(h == NULL){
        printf("Memory Error!");
        return NULL;
    }
    h->heap_type = heap_type;
    h->count=0;
    h->capacity = capacity;
    h->arr = malloc(capacity * sizeof(Vertex*)); //size in bytes

    //check if allocation succeed
    if ( h->arr == NULL){
        printf("Memory Error!");
        return NULL;
    }
    return h;
}

void insert(Heap *h, Vertex *key){
    if( h->count < h->capacity){
        h->arr[h->count] = key;
        heapify_bottom_top(h, h->count);
        h->count++;
    }
}

void heapify_bottom_top(Heap *h,int index){
    Vertex *temp;
    int parent_node = (index-1)/2;

    if(h->arr[parent_node] > h->arr[index]){
        //swap and recursive call
        temp = h->arr[parent_node];
        h->arr[parent_node] = h->arr[index];
        h->arr[index] = temp;
        heapify_bottom_top(h,parent_node);
    }
}

void heapify_top_bottom(Heap *h, int parent_node){
    int left = parent_node*2+1;
    int right = parent_node*2+2;
    int min;
    Vertex *temp;

    if(left >= h->count || left <0)
        left = -1;
    if(right >= h->count || right <0)
        right = -1;

    if(left != -1 && h->arr[left] < h->arr[parent_node])
        min=left;
    else
        min =parent_node;
    if(right != -1 && h->arr[right] < h->arr[min])
        min = right;

    if(min != parent_node){
        temp = h->arr[min];
        h->arr[min] = h->arr[parent_node];
        h->arr[parent_node] = temp;

        // recursive  call
        heapify_top_bottom(h, min);
    }
}

Vertex *PopMin(Heap *h){
    Vertex *pop;
    if(h->count==0){
        printf("\n__Heap is Empty__\n");
        return NULL;
    }
    // replace first node by last and delete last
    pop = h->arr[0];
    h->arr[0] = h->arr[h->count-1];
    h->count--;
    heapify_top_bottom(h, 0);
    return pop;
}

void print_heap(Heap *h){
    int i;
    //printf("____________Print Heap_____________\n");
    for(i=0;i< h->count;i++){
        //printf("-> %d ",h->arr[i]);
        print(h->arr[i]->value);
        printf(" ");
    }
    printf("\n");
}

Heap *init(Graph *g, void *start){
    Heap *q = CreateHeap(15,0);
    Vertex *v, *s;
    Node *n;

    v = g->first;
    while(v){
        n = (Node *) v->value;

        if(g->compar(start,v->value) == 0){
            n->distance = 0;
        }else{
            n->distance = inf;
        }

        insert(q,v);
        v = v->next;
    }
return q;}


void relax(Edge *e, Heap *q){
    int index,aux;
    float *aux2;
    Node *o = e->origin->value;
    Node *t = e->target->value;

    aux2 = o->distance + e->dist;
    if(*((int *)aux2) < (t->distance)){
        
        t->distance = *((int *)aux2);

        aux = *((int *)e->origin->value);
        heapify_bottom_top(q,aux);

        //print_heap(q);
    }
}

void dijkstra(Graph *g, void *start){
    Heap *heap;
    Vertex *v;
    Edge *e;
    int i;

    heap = init(g,start);
    while(heap->count > 0){

        print_heap(heap);

        v = PopMin(heap);
        e = v->first;
        while(e){
            relax(e,heap);
            print_heap;
            e = e->next;
        }
    }

}



void Graph_print_peso(Graph *g, void (*print)(void *)){
    Vertex *v = NULL;
     Edge *e = NULL;
    if(g && print){
        v = g->first;

        while(v){
            printf("Vertice ");
            print(v->value);
            printf("\n\tVizinhos: ");
            e = v->first;

            while(e){
                printf("(");
                print(v->value);
                printf(" -> ");
                print(e->target->value);
                printf(" = %.2f)", e->peso);
                printf(" ");
                e = e->next;
            }
            printf("\n");
            v = v->next;
        }
    }
}


void attDist(Edge *edge, float *dist, int *vis){
    Edge *e = NULL;
    int t;
    if (edge) {
        e = edge;
        while (e) {
            t =*((int*)e->target->value);
            if (vis[t] == 0);
                dist[t] += e->peso;
            e = e->next;
        }
    } 

    for(int i = 0; i < 15; i++){
        printf("%.2f ", dist[i]);
    }
    printf("Atualizado\n");
}

int MenorDist(float *dist, int *visitado, int NV) {
    int i, menor = -1, primeiro = 1;
    for(i=0; i < NV; i++){
        if(dist[i] >= 0 && visitado[i] == 0) {
            if(primeiro) {
                menor = i;
                primeiro = 0;
            } else {
                if(dist[menor] > dist[i])
                    menor = i;
            }
        }
    }
    printf("menor: %d\n", menor);
    return menor;
}

void dijkstra1 (Graph *g, int ini, int *ant, float *dist) {
    int i, cont, NV, *visitado, vert;
    Vertex *ind;
    Edge *edg = NULL;
    cont = NV = g->n;
    visitado = (int*) malloc(NV * sizeof(int));

    for(i = 0; i < NV; i++) {
        ant[i] = -1;
        dist[i] = -1;
        visitado[i] = 0;
    }

    dist[ini] = 0;

    while(cont > 0) {
        vert = MenorDist(dist, visitado, NV);
        visitado[vert] = 1;
        if (vert == -1)
            break;

        ind = Vertex_find(g, &vert);

        attDist(ind->first, dist, visitado);
        ant[cont - 1] = vert;

        cont--;
    }
        
    free(visitado);
}
