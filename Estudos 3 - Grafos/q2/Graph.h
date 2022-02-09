typedef struct Graph Graph;
typedef struct Vertex Vertex;
typedef struct Edge Edge;

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
};

struct Edge {
    Edge *next;
    Vertex *origin;
    Vertex *target;
    float *dist;
};

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