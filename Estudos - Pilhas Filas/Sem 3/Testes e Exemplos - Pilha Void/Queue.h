typedef struct Queue Queue;

Queue  *Queue_create(int);
void    Queue_destroy(Queue *);
int     Queue_isEmpty(Queue *);
int     Queue_isFull(Queue *);

void    Queue_push(Queue *, void *);
void   *Queue_pop(Queue *);
void   *Queue_begin(Queue *);
void   *Queue_end(Queue *);
int     Queue_getSize(Queue *);

void    Queue_print(Queue *,void (*)(void *));