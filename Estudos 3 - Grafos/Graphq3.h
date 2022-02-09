typedef struct Graph Graph;
typedef struct Vertex Vertex;
typedef struct Edge Edge;
typedef struct Heap Heap;
typedef struct Node Node;

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
    int fechado;
    int numberLinks;
    int visitado;
};

struct Edge {
    Edge *next;
    Vertex *origin;
    Vertex *target;
    float *dist;
    float peso;
};

struct Heap{
    Vertex **arr;
    int count;
    int capacity;
    int heap_type; // for min heap , 1 for max heap
};

struct Node{
    int distance;
};


void Graph_print_peso(Graph *g, void (*print)(void *));


void attDist(Edge *edge, float *dist, int *vis);
int MenorDist(float *dist, int *visitado, int NV);
void dijkstra1 (Graph *g, int ini, int *ant, float *dist);

Heap *CreateHeap(int capacity,int heap_type);
void insert(Heap *h, Vertex *key);
void heapify_bottom_top(Heap *h,int index);
void heapify_top_bottom(Heap *h, int parent_node);
Vertex *PopMin(Heap *h);
void print_heap(Heap *h);

Vertex *not_visited(Edge *edge);
void DFS(Vertex *v, Vertex **path,int *cont);
Vertex **Busca_DFS(Graph *g, void *start);
int compar(void *x, void *y);
void print(void *n);
void print_float(void *n);

Graph  *Graph_create(int (*compar)(void *x, void *y));
void    Graph_destroy(Graph *g);
void    Graph_insert(Graph *g, void *value);
void    Graph_link(Graph *g, void *origin, void *target, void *dist);
void    Graph_delete(Graph *g, void *value);
void    Graph_print(Graph *g, void (*print)(void *));

Vertex *Vertex_create(void *value);
void    Vertex_destroy(Vertex *v);
Vertex *Vertex_find(Graph *g, void *value);

Edge   *Edge_create();
void    Edge_destroy(Edge *e);
Edge   *Edge_find(Graph *g, void *value1, void *value2);

void Edge_print(Edge *e);

Heap *init(Graph *g, void *start);
void relax(Edge *e, Heap *q);
void dijkstra(Graph *g, void *start);

void dijkstra1 (Graph *g, int ini, int *ant, float *dist);

int MenorDist(float *dist, int *visitado, int NV);

void attDist(Edge *edge, float *dist, int *vis);

void Graph_print_peso(Graph *g, void (*print)(void *));