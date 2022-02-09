#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
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