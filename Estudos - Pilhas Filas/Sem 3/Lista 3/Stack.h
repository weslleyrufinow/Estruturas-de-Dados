typedef struct Stack Stack;

Stack *stack_create(int size);
void   stack_destroy(Stack *stack);
int    stack_isEmpty(Stack *stack);
int    stack_isFull(Stack *stack);
int    stack_getSize(Stack *stack);
void   stack_push(Stack *stack, void *element);
void  *stack_pop(Stack *stack);
void  *stack_top(Stack *stack);

void   stack_print(Stack *stack, void (*print)(void *));
