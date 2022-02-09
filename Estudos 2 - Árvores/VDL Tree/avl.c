/*** File avl.c - AVL Tree ***/
/*
 *   Shane Saunders
 */
#include <stdlib.h>
#include "avl.h"

/* Test implementation which uses the stack history to replace the use of next
 * and prev pointers.
 */
/* Implementação de teste que usa o histórico de pilha para substituir o uso do next
 * e ponteiros anteriores.
 */

/* avl_alloc () - Aloca espaço para uma árvore AVL e retorna um ponteiro para ela.
 * A função compara as chaves de dois itens e retorna um negativo,
 * zero ou número inteiro positivo, dependendo se o primeiro item é menor que,
 * igual ou maior que o segundo.
 */
avl_t *avl_alloc(int (* compar)(const void *, const void *)) {
    avl_t *t;

    t = malloc(sizeof(avl_t));
    t->root = NULL;
    t->compar = compar;
    t->stack = malloc(AVL_STACK_SIZE * sizeof(avl_node_t *));
    t->path_info = malloc(AVL_STACK_SIZE * sizeof(signed char));
    t->n = 0;

    return t;
}


/* avl_free() - Frees space used by the AVL tree pointed to by t. */
/* avl_free () - Libera espaço usado pela árvore AVL apontada por t. */
void avl_free(avl_t *t) {
    int tos;
    avl_node_t *p, **stack;

    /* In order to free all nodes in the tree a depth first search is performed
     * This is implemented using a stack.
     */
    /*
     * A fim de liberar todos os nós na árvore, 
     * uma primeira pesquisa em profundidade é realizada
     * Isso é implementado usando uma pilha.
    */
    if(t->root) {
        stack = t->stack;
	    stack[0] = t->root;
        tos = 1;
        while(tos) {
            p = stack[--tos];
            if(p->left) {
                stack[tos++] = p->left;
            }
            if(p->right) {
                stack[tos++] = p->right;
            }
            free(p);
        }
    }

    free(t->stack);
    free(t->path_info);
    free(t);
}


/* avl_insert() - Inserts an item into the AVL tree pointed to by t,
 * according the the value its key.  The key of an item in the AVL tree must
 * be unique among items in the tree.  If an item with the same key already
 * exists in the tree, a pointer to that item is returned.  Otherwise, NULL is
 * returned, indicating insertion was successful.
 */
/*
 * avl_insert () - Insere um item na árvore AVL apontado por t,
 * de acordo com o valor de sua chave. A chave de um item na árvore AVL deve
 * ser único entre os itens da árvore. Se um item com a mesma chave já
 * existe na árvore, um ponteiro para esse item é retornado. Caso contrário, NULL é
 * retornado, indicando que a inserção foi bem-sucedida.
*/
void *avl_insert(avl_t *t, void *item) {
    int (* compar)(const void *, const void *);
    int cmp_result;
    void *return_result;
    avl_node_t *x, *p, *q, *r, **attach_x;
    avl_node_t **stack;
    int tos, stack_n;
    signed char *path_info;

    compar = t->compar;

    /* The stack stores information about the path to a node.  For the array
     * stack, stack[i] holds the (i)th nodes on the path from the root, with
     * the 0th node being the root node.  For the array path_info[],
     * path_info[i] is -1 or 1 depending on whether the left or right branch
     * branch was traversed from the (i)th node.  The path_info array can then
     * be used for updating balance information.
     */
    /*
     * A pilha armazena informações sobre o caminho para um nó. Para a matriz
     * pilha, pilha [i] contém os (i) ésimos nós no caminho da raiz, com
     * o 0º nó sendo o nó raiz. Para a matriz path_info [],
     * path_info [i] é -1 ou 1 dependendo se o branch esquerdo ou direito
     * ramificação foi atravessada a partir do (i) ésimo nó. A matriz path_info pode então
     * ser usado para atualizar informações de saldo.
    */
    stack = t->stack;
    path_info = t->path_info;
    tos = 0;

    /* Search for insertion position, starting from the root node, if it
     * exists.
     */
    /*
     * Procure a posição de inserção, a partir do nó raiz, se
     * existe.
    */
    if((p = t->root)) {
	/* Repeatedly explore either the left branch or the right branch
	 * depending on the value of the key, until an empty branch position
	 * is found.
	 */
    /*
    * Explore repetidamente o ramo esquerdo ou direito
    * dependendo do valor da chave, até uma posição de ramo vazia
    * seja encontrado.
    */
        for(;;) {
            stack[tos] = p;
            cmp_result = compar(item, p->item);
            if(cmp_result < 0) {
                path_info[tos] = -1;
                tos++;
                p = p->left;
                if(!p) {
                    attach_x = &stack[tos-1]->left;
                    break;
                }
            }
            else 
                if(cmp_result > 0) {
                    path_info[tos] = 1;
                    tos++;
                    p = p->right;
                    if(!p) {
                        attach_x = &stack[tos-1]->right;
                        break;
                    }
                }
                else {
                    return p->item;
                }
	    }
    }
    else {
	    attach_x = &t->root;
    }

    /* Null will be returned, indicating there was no item with the same key in
     * the tree.
     */
    /*
     * Nulo será retornado, indicando que não havia nenhum item com a mesma chave em
     * a árvore.
    */
    return_result = NULL;
    
    /* Allocated space for the new node. */
    /* Espaço alocado para o novo nó. */
    x = malloc(sizeof(avl_node_t));
    x->left = x->right = NULL;
    x->balance = 0;
    x->item = item;

    /* attach_x is a pointer to the pointer variable to add the node to the
     * tree.
     */
    /* attach_x é um ponteiro para a variável de ponteiro para adicionar o nó ao
     * árvore.
     */
    *attach_x = x;
    t->n++;
    	
    /* Now traverse the stack, updating balance information of ancestors,
     * and performing rotation if necessary.
     */
    /* Agora atravesse a pilha, atualizando as informações de equilíbrio dos ancestrais,
     * e realizando rotação, se necessário.
     */
    stack_n = tos;
    while(tos) {
        p = stack[--tos];
        if(p->balance == 0) {
            /* Balance changes from 0 to 1 or -1.  The length of the
            * longest path from  p to a leaf has increased by 1, so
            * continue the iteration to the parent of p.
            */
           /* O saldo muda de 0 para 1 ou -1. O comprimento do
            * caminho mais longo de p para uma folha aumentou em 1, então
            * continue a iteração para o pai de p.
            */
            p->balance += path_info[tos];
        }
        else {
            p->balance += path_info[tos];
            if(p->balance == 0) {
            /* The balance has changed from -1 or 1 to 0.  The length
            * of the longest path from p to a leaf has not changed,
            * so stop the iteration.
            */
           /* O saldo mudou de -1 ou 1 para 0. O comprimento
            * do caminho mais longo de p para uma folha não mudou,
            * então pare a iteração.
            */
                break;  /* Tree is balanced. */
            }
            else {
            /* Balance changes from 1 to 2 or from -1 to -2.
            * Now the tree is unbalanced, and rotation must be
            * performed.
            *
            * For this description, define direction x as the
            * direction of the over-balance, and direction y, as the
            * other direction.   For this description it is simpler to
            * refer to the x child and the y child, since the use left
            * and right depends on the tree balance.
            */

            /* The kind of rotation that occurs depends on whether
            * the balance of p's child (from which p was reached), q,
            * is in the same direction as the balance of p.
            * This is determined by looking at path_info[tos].
            */
           /* O saldo muda de 1 para 2 ou de -1 para -2.
            * Agora a árvore está desequilibrada e a rotação deve ser
            * realizado.
            *
            * Para esta descrição, defina a direção x como o
            * direção do equilíbrio excessivo e direção y, como o
            * outra direção. Para esta descrição é mais simples
            * referem-se ao filho xeo filho y, uma vez que o uso deixou
            * e certo depende do equilíbrio da árvore.
            */

            /* O tipo de rotação que ocorre depende se
            * o equilíbrio do filho de p (a partir do qual p foi alcançado), q,
            * está na mesma direção que o equilíbrio de p.
            * Isso é determinado observando path_info [tos].
            */
                q = stack[tos + 1];
                if(path_info[tos] == path_info[tos + 1]) {
                /* There is the the following tree structure:
                *  A - x child tree of q.
                *  B - y child tree of q.
                *  C - y child of p.
                */
               /* Existe a seguinte estrutura de árvore:
                * A - x árvore filha de q.
                * B - y árvore filha de q.
                * C - y filho de p.
                */

                    /* For the rotation:
                    *  - tree B replaces node q as the child of p.
                    *  - node p replaces tree B as the child of q.
                    */
                   /* Para a rotação:
                    * - a árvore B substitui o nó q como filho de p.
                    * - o nó p substitui a árvore B como filho de q.
                    */
                    if(path_info[tos] == 1) {
                        p->right = q->left;
                        q->left = p;
                    }
                    else {
                        p->left = q->right;
                        q->right = p;
                    }

                    p->balance = q->balance = 0;

                    /* A child pointer of p's parent changes from p to q.
                    * If p was the root, the root node changes.
                    */
                   /* Um ponteiro filho do pai de p muda de p para q.
                    * Se p for a raiz, o nó raiz muda.
                    */
                    if(tos != 0) {
                        if(path_info[tos-1] == 1) {
                            stack[tos-1]->right = q;
                        }
                        else {
                            stack[tos-1]->left = q;
                        }
                    }
                    else {
                        t->root = q;
                    }
                
                    break;
                }
                else {
                    if(tos + 2 != stack_n) {
                        r = stack[tos + 2];
                    }
                    else {
                        r = x;  /* Special case: r is the inserted node. */
                    }
                    /* There is the following tree structure:
                    *  A - x child tree of q.
                    *  B - x child tree of r.
                    *  C - y child tree of r.
                    *  D - y child tree of p.
                    */

                    /* For the rotation:
                    *  - tree B replaces node r as the child of q.
                    *  - tree C replaces node q as the child of p.
                    *  - node q replaces tree B as the child of r.
                    *  - node p replaces tree C as the child of r.
                    */
                   /* Existe a seguinte estrutura de árvore:
                    * A - x árvore filha de q.
                    * B - x árvore filha de r.
                    * C - árvore filha de y de r.
                    * D - árvore filha y de p.
                    * /

                    / * Para a rotação:
                    * - a árvore B substitui o nó r como filho de q.
                    * - a árvore C substitui o nó q como filho de p.
                    * - o nó q substitui a árvore B como filho de r.
                    * - o nó p substitui a árvore C como filho de r.
                    */
                    if(path_info[tos] == 1) {
                        q->left = r->right;
                        p->right = r->left;
                        r->right = q;
                        r->left = p;  
                        if(r->balance == 1) {
                            p->balance = -1;
                            q->balance = 0;
                        }
                        else 
                            if(r->balance == -1) {
                                p->balance = 0;
                                q->balance = 1;
                            }
                            else {
                                p->balance = q->balance = 0;
                            }
                    }
                    else {
                        q->right = r->left;
                        p->left = r->right;
                        r->left = q;
                        r->right = p;
                        if(r->balance == 1) {
                            p->balance = 0;
                            q->balance = -1;
                        }
                        else 
                            if(r->balance == -1) {
                                p->balance = 1;
                                q->balance = 0;
                            }
                            else {
                                        p->balance = q->balance = 0;
                            }
                    }
                    r->balance = 0;
                
                    /* A child pointer of p's parent changes from p to r.
                    * If p was the root, the root node changes.
                    */
                   /* Um ponteiro filho do pai de p muda de p para r.
                    * Se p for a raiz, o nó raiz muda.
                    */
                    if(tos != 0) {
                        if(path_info[tos-1] == 1) {
                            stack[tos-1]->right = r;
                        }
                        else {
                            stack[tos-1]->left = r;
                        }
                    }
                    else {
                        t->root = r;
                    }
                    break;
                }
            }
        }
    }
    
    return return_result;
}


/* avl_find() - Find an item in the AVL tree with the same key as the
 * item pointed to by `key_item'.  Returns a pointer to the item found, or NULL
 * if no item was found.
 */
/* avl_find () - Encontre um item na árvore AVL com a mesma chave que o
 * item apontado por `key_item '. Retorna um ponteiro para o item encontrado, ou NULL
 * se nenhum item foi encontrado.
 */
void *avl_find(avl_t *t, void *key_item) {
    int (* compar)(const void *, const void *);
    int cmp_result;
    avl_node_t *p, *next_p;

	
    if((next_p = t->root)) {
         compar = t->compar;
	 
        /* Repeatedly explore either the left or right branch, depending on the
        * value of the key, until the correct item is found.
        */
       /* Explore repetidamente o branch esquerdo ou direito, dependendo do
        * valor da chave, até que o item correto seja encontrado.
        */
        do {
	        p = next_p;
	        cmp_result = compar(key_item, p->item);
            if(cmp_result < 0) {
                next_p = p->left;
            }
	        else 
                if(cmp_result > 0) {
		            next_p = p->right;
	            }
	            else {
		        /* Item found. */
                    return p->item;
	            }
	    } while(next_p);
    }

    return NULL;
}


/* avl_find_min() - Returns a pointer to the minimum item in the AVL
 * tree pointed to by t.  If there are no items in the tree a NULL pointer is
 * returned.
 */
/* avl_find_min () - Retorna um ponteiro para o item mínimo no AVL
 * árvore apontada por t. Se não houver itens na árvore, um ponteiro NULL é
 * devolvida.
 */
void *avl_find_min(avl_t *t) {
    avl_node_t *p, *next_p;

    if((next_p = t->root)) {
        /* To locate the minimum, the left branches is repeatedly chosen until
	     * we can explore no further.
         */
        /* Para localizar o mínimo, os ramos esquerdos são escolhidos repetidamente até
         * não podemos explorar mais.
         */
        do {
            p = next_p;
            next_p = p->left;
        } while(next_p);
    }
    else {
	    return NULL;
    }
    
    return p->item;
}


/* avl_delete() - Delete the first item found in the AVL tree with
 * the same key as the item pointed to by `key_item'.  Returns a pointer to the
 * deleted item, and NULL if no item was found.
 */
/* avl_delete () - Exclui o primeiro item encontrado na árvore AVL com
 * a mesma chave do item apontado por `key_item '. Retorna um ponteiro para o
 * item excluído e NULL se nenhum item for encontrado.
 */
void *avl_delete(avl_t *t, void *key_item) {
    void *return_item;
    int (* compar)(const void *, const void *);
    int cmp_result;
    avl_node_t *p, *prev_p;
    avl_node_t *m, *prev_m;
    avl_node_t *q, *r;
    avl_node_t **stack;
    int tos, stack_p;
    signed char *path_info;

    /* If the tree is empty return NULL. */
    if(!(p = t->root)) return NULL;    
    
    compar = t->compar;

    /* The stack stores information about the path to a node.  For the array
     * stack, stack[i] holds the (i)th nodes on the path from the root, with
     * the 0th node being the root node.  For the array path_info[],
     * path_info[i] is -1 or 1 depending on whether the left or right branch
     * branch was traversed from the (i)th node.  The path_info[] array can
     * then be used for updating balance information.
     */
    /* A pilha armazena informações sobre o caminho para um nó. Para a matriz
     * pilha, pilha [i] contém os (i) ésimos nós no caminho da raiz, com
     * o 0º nó sendo o nó raiz. Para a matriz path_info [],
     * path_info [i] é -1 ou 1 dependendo se o galho é esquerdo ou direito
     * ramificação foi atravessada a partir do (i) ésimo nó. O array path_info [] pode
     * então ser usado para atualizar informações de saldo.
     */
    stack = t->stack;
    path_info = t->path_info;
    tos = 0;
    
    /* Attempt to locate the item to be deleted. */
    /* Tenta localizar o item a ser excluído. */
    for(;;) {
	    cmp_result = compar(key_item, p->item);
        if(cmp_result < 0) {
            path_info[tos] = -1;
            stack[tos++] = p;
            p = p->left;
        }
        else 
            if(cmp_result > 0) {
                path_info[tos] = 1;
                stack[tos++] = p;
                p = p->right;
            }
            else {
                /* Item found. */
                break;
            }
            if(!p) {
                /* Item not found. */
                return NULL;
            }
    }

    /* p points to the node to be deleted.  Currently, prev_p is on the top of
     * the stack.
     */
    /* p aponta para o nó a ser excluído. Atualmente, prev_p está no topo de
     * a pilha.
     */
    if(!p->left) {
	    /* Right child replaces p. */
        if(tos == 0) {
                t->root = p->right;
        }
        else {
            prev_p = stack[tos-1];
            if(p == prev_p->left) {
                prev_p->left = p->right;
            }
            else {
                prev_p->right = p->right;
            }
        }
    }
    else if(!p->right) {
	/* Left child replaces p. */
        if(tos == 0) {
            t->root = p->left;
        }
        else {
            prev_p = stack[tos-1];
            if(p == prev_p->left) {
                prev_p->left = p->left;
            }
            else {
                prev_p->right = p->left;
            }
        }
    }
    else {
        /* Minimum child, m, in the right subtree replaces p. */
        path_info[tos] = 1;
        stack[tos] = p;
        stack_p = tos++;  /* Save the stack position of p. */

        m = p->right;  /* Guaranteed not to be NULL. */
        do {
            path_info[tos] = -1;
            stack[tos++] = m;
            m = m->left;
        } while(m);
        m = stack[--tos];

        /* Update either the left or right child pointers of prev_p. */
        /* Atualize os ponteiros filho esquerdo ou direito de prev_p. */
        if(stack_p == 0) {
                t->root = m;
        }
        else {
            prev_p = stack[stack_p - 1];
            if(p == prev_p->left) {
                prev_p->left = m;
            }
	        else {
		        prev_p->right = m;
	        }
	    }

        /* Update the tree part m was removed from, and assign m the child
        * pointers of p (only if m is not the right child of p).
        */
       /* Atualizar a parte da árvore m foi removida e atribuir m ao filho
        * ponteiros de p (somente se m não for o filho certo de p).
        */
        prev_m = stack[tos-1];
        if(prev_m != p) {
            prev_m->left = m->right;
            m->right = p->right;
        }
        m->left = p->left;

        /* Give node m the balance node p had, and replace the stack entry for
        * p with m.
        */
       /* Dê ao nó m o nó de equilíbrio que p tinha e substitua a entrada da pilha por
        * p com m.
        */
        m->balance = p->balance;
        stack[stack_p] = m;
    }

    /* Get return value and free space used by node p. */
    /* Obtém o valor de retorno e o espaço livre usado pelo nó p. */
    return_item = p->item;
    free(p);
    t->n--;

    /* Perform rotations if necessary to rebalance the tree.  This is done
     * by traversing the stack, updating balance information of ancestors,
     * and performing rotations if necessary.
     *
     * Pointer p now points to the node being considered for rebalance.
     */
    /* Execute rotações, se necessário, para reequilibrar a árvore. Isso está feito
     * percorrendo a pilha, atualizando as informações de equilíbrio dos ancestrais,
     * e realizando rotações, se necessário.
     *
     * O ponteiro p agora aponta para o nó que está sendo considerado para o rebalanceamento.
     */
    while(tos) {
        p = stack[--tos];
        if(p->balance == 0) {
            /* Balance changes from 0 to 1 or -1.  The length of only one
            * path from p to a leaf has decreased by 1, so the length of the
            * longest path is unchanged.  Therefore iteration can stop.
            */
           /* O saldo muda de 0 para 1 ou -1. O comprimento de apenas um
            * caminho de p para uma folha diminuiu em 1, então o comprimento do
            * o caminho mais longo permanece inalterado. Portanto, a iteração pode parar.
            */
            p->balance -= path_info[tos];
            break;  /* Tree is balanced. */
        }
        else {
            p->balance -= path_info[tos];

            /* Note that if balance changed from -1 or 1 to 0, the length of
            * the longest path from p to a leaf must have decreased.
            * Therefore iterations for balance updates will continue.
            */
           /* Observe que se o saldo mudou de -1 ou 1 para 0, o comprimento de
            * o caminho mais longo de p para uma folha deve ter diminuído.
            * Portanto, as iterações para atualizações de saldo continuarão.
            */
            
            if(p->balance != 0) {
                /* Balance changes from 1 to 2 or from -1 to -2.
                * Now the tree is unbalanced, and rotation must be
                * performed.
                *
                * For this description, define direction x as the
                * direction of the over-balance, and direction y, as the
                * other direction.   For this description it is simpler to
                * refer to the x child and the y child, since the use left
                * and right depends on the tree balance.
                */

                /* The kind of rotation that occurs depends on whether
                * the balance of p's other child (not the child p was reached
                * from) is in the same direction as the balance of p.
                */
               /* O saldo muda de 1 para 2 ou de -1 para -2.
                * Agora a árvore está desequilibrada e a rotação deve ser
                * realizado.
                *
                * Para esta descrição, defina a direção x como o
                * direção do equilíbrio excessivo e direção y, como o
                * outra direção. Para esta descrição é mais simples
                * referem-se ao filho xeo filho y, uma vez que o uso deixou
                * e certo depende do equilíbrio da árvore.
                * /

                / * O tipo de rotação que ocorre depende se
                * o saldo da outra criança de p (não a criança p foi alcançada
                * de) está na mesma direção que o equilíbrio de p.
                */
                if(path_info[tos] == 1) {
                    q = p->left;  /* p's other child. */
                }
                else {
                    q = p->right;  /* p's other child. */
                }
                if(path_info[tos] != q->balance) {
                    /* The balance (p, q) will be either:
                    * (2,1), (2,0), (-2,-1), or (-2,0)
                    */
                    
                    /* There is the the following tree structure:
                    *  A - x child tree of q.
                    *  B - y child tree of q.
                    *  C - y child of p.  (Deletion occurred in tree C.)
                    */

                    /* For the rotation:
                    *  - tree B replaces node q as the child of p.
                    *  - node p replaces tree B as the child of q.
                    */
                   /* O saldo (p, q) será:
                    * (2,1), (2,0), (-2, -1) ou (-2,0)
                    * /
                    
                    / * Existe a seguinte estrutura de árvore:
                    * A - x árvore filha de q.
                    * B - y árvore filha de q.
                    * C - y filho de p. (A exclusão ocorreu na árvore C.)
                    * /

                    / * Para a rotação:
                    * - a árvore B substitui o nó q como filho de p.
                    * - o nó p substitui a árvore B como filho de q.
                    */
                    if(path_info[tos] != 1) {
                        p->right = q->left;
                        q->left = p;
                    }
                    else {
                        p->left = q->right;
                        q->right = p;
                    }

                    /* A child pointer of p's parent changes from p to q.
                    * If p was the root, the root node changes.
                    */
                   /* Um ponteiro filho do pai de p muda de p para q.
                    * Se p for a raiz, o nó raiz muda.
                    */
                    if(tos != 0) {
                        if(path_info[tos-1] == 1) {
                            stack[tos-1]->right = q;
                        }
                        else {
                            stack[tos-1]->left = q;
                        }
                    }
                    else {
                        t->root = q;
                    }

                    /* Update balance information of nodes p and q. */
                    if(q->balance == 0) {
                        p->balance = p->balance > 0 ? 1 : -1;
                        q->balance = -p->balance;
                        break;  /* Tree is balanced. */
                    }
                    else {
                        p->balance = q->balance = 0;
                    }
                
                    /* Unless q->balance == 0, iterations will continue, since
                    * the length of longest path has decreased.
                    */
                   /* A menos que q-> balance == 0, as iterações continuarão, uma vez que
                    * o comprimento do caminho mais longo diminuiu.
                    */
                }
                else {
                    /* The balance of (p, q) will be either:
                    * (2,-1) or (-2,1)
                    */
                
                    /* There is the following tree structure:
                    *  A - x child tree of q.
                    *  B - x child tree of r.
                    *  C - y child tree of r.
                    *  D - y child tree of p.  (Deletion occurred in tree D)
                    */

                    /* For the rotation:
                    *  - tree B replaces node r as the child of q.
                    *  - tree C replaces node q as the child of p.
                    *  - node q replaces tree B as the child of r.
                    *  - node p replaces tree C as the child of r.
                    */
                   /* O saldo de (p, q) será:
                    * (2, -1) ou (-2,1)
                    * /
                
                    / * Existe a seguinte estrutura de árvore:
                    * A - x árvore filha de q.
                    * B - x árvore filha de r.
                    * C - árvore filha de y de r.
                    * D - árvore filha y de p. (Exclusão ocorreu na árvore D)
                    * /

                    / * Para a rotação:
                    * - a árvore B substitui o nó r como filho de q.
                    * - a árvore C substitui o nó q como filho de p.
                    * - o nó q substitui a árvore B como filho de r.
                    * - o nó p substitui a árvore C como filho de r.
                    */
                    if(path_info[tos] != 1) {
                        r = q->left;
                        q->left = r->right;
                        p->right = r->left;
                        r->right = q;
                        r->left = p;  
                        if(r->balance == 1) {
                            p->balance = -1;
                            q->balance = 0;
                        }
                        else if(r->balance == -1) {
                            p->balance = 0;
                            q->balance = 1;
                        }
                        else {
                            p->balance = q->balance = 0;
                        }
                    }
                    else {
                        r = q->right;
                        q->right = r->left;
                        p->left = r->right;
                        r->left = q;
                        r->right = p;
                        if(r->balance == 1) {
                            p->balance = 0;
                            q->balance = -1;
                        }
                        else if(r->balance == -1) {
                            p->balance = 1;
                            q->balance = 0;
                        }
                        else {
                            p->balance = q->balance = 0;
                        }
                    }
                    r->balance = 0;
                
                    /* A child pointer of p's parent changes from p to r.
                    * If p was the root, the root node changes.
                    */
                   /* Um ponteiro filho do pai de p muda de p para r.
                    * Se p for a raiz, o nó raiz muda.
                    */
                    if(tos != 0) {
                        if(path_info[tos-1] == 1) {
                            stack[tos-1]->right = r;
                        }
                        else {
                            stack[tos-1]->left = r;
                        }
                    }
                    else {
                        t->root = r;
                    }
                
                    /* Continue with further iterations, since the length of
                    * longest path has decreased.
                    */
                   /* Continue com outras iterações, uma vez que o comprimento de
                    * o caminho mais longo diminuiu.
                    */
                }
            }
        }
    }
    
    return return_item;
}


/* avl_delete_min() - Deletes the item with the smallest key from the AVL
 * tree pointed to by t.  Returns a pointer to the deleted item.
 * Returns a NULL pointer if there are no items in the tree.
 */
/* avl_delete_min () - Exclui o item com a menor chave do AVL
 * árvore apontada por t. Retorna um ponteiro para o item excluído.
 * Retorna um ponteiro NULL se não houver itens na árvore.
 */
void *avl_delete_min(avl_t *t) {
    void *return_item;
    avl_node_t *p;
    avl_node_t *q, *r;
    avl_node_t **stack;
    int tos;
    
    /* The stack stores information about the path to a node.  For the array
     * stack, stack[i] holds the (i)th nodes on the path from the root, with
     * the 0th node being the root node.  For the array path_info[],
     * path_info[i] is -1 or 1 depending on whether the left or right branch
     * branch was traversed from the (i)th node.  The path_info[] array can
     * then be used for updating balance information.
     */
    /* A pilha armazena informações sobre o caminho para um nó. Para a matriz
     * pilha, pilha [i] contém os (i) ésimos nós no caminho da raiz, com
     * o 0º nó sendo o nó raiz. Para a matriz path_info [],
     * path_info [i] é -1 ou 1 dependendo se o branch esquerdo ou direito
     * ramificação foi atravessada a partir do (i) ésimo nó. O array path_info [] pode
     * então ser usado para atualizar informações de saldo.
     */
    stack = t->stack;
    tos = 0;
    
    /* Attempt to locate the item to be deleted. */
    /* Tenta localizar o item a ser excluído. */
    if((p = t->root)) {
        /* To locate the minimum, the left branches is repeatedly chosen until
	    * we can explore no further.
         */
        /* Para localizar o mínimo, os ramos esquerdos são escolhidos repetidamente até
        * não podemos explorar mais.
        */
        do {
	        stack[tos++] = p;
            p = p->left;
	    } while(p);
	    p = stack[--tos];
    }
    else {
	    return NULL;
    }

    /* Right child of p replaces p. */
    if(tos == 0) {
        t->root = p->right;
    }
    else {
        stack[tos-1]->left = p->right;
	/* stack[tos-1] points to the parent of p. */
    }

    /* Get return value and free space used by node p. */
    return_item = p->item;
    free(p);
    t->n--;
  
    /* Perform rotations if necessary to rebalance the tree.  This is done
     * by traversing the stack, updating balance information of ancestors,
     * and performing rotations if necessary.
     *
     * Pointer p now points to the node being considered for rebalance.
     */
     /* Execute rotações, se necessário, para reequilibrar a árvore. Isso está feito
      * percorrendo a pilha, atualizando as informações de equilíbrio dos ancestrais,
      * e realizando rotações, se necessário.
      *
      * O ponteiro p agora aponta para o nó que está sendo considerado para o rebalanceamento.
      */
    while(tos) {
	p = stack[--tos];
	if(p->balance == 0) {
	    /* Balance changes from 0 to 1.  The length of only one
	     * path from p to a leaf has decreased by 1, so the length of the
	     * longest path is unchanged.  Therefore iteration can stop.
	     */
        /* O equilíbrio muda de 0 para 1. O comprimento de apenas um
         * caminho de p para uma folha diminuiu em 1, então o comprimento do
         * o caminho mais longo permanece inalterado. Portanto, a iteração pode parar.
         */
	    p->balance++;;
	    break;  /* Tree is balanced. */
	}
	else {
	    p->balance++;

	    /* Note that if balance changed from -1 to 0, the length of
	     * the longest path from p to a leaf must have decreased.
	     * Therefore iterations for balance updates will continue.
	     */
        /* Observe que se o equilíbrio mudou de -1 para 0, o comprimento de
        * o caminho mais longo de p para uma folha deve ter diminuído.
        * Portanto, as iterações para atualizações de saldo continuarão.
        */
	    
	    if(p->balance != 0) {
            /* Balance changes from 1 to 2.
            * Now the tree is unbalanced, and rotation must be
            * performed.
            */

            /* The kind of rotation that occurs depends on whether
            * the balance of p's other child (not the child p was reached
            * from) is in the same direction as the balance of p.
            */
           /* O saldo muda de 1 para 2.
             * Agora a árvore está desequilibrada e a rotação deve ser
             * realizado.
             * /

             / * O tipo de rotação que ocorre depende se
             * o saldo da outra criança de p (não a criança p foi alcançada
             * de) está na mesma direção que o equilíbrio de p.
             */
		    q = p->right;  /* p's other child. */
            if(q->balance != -1) {
                /* The balance (p, q) will be either:
                * (2,1), or (2,0)
                */
		    
                /* There is the the following tree structure:
                *  A - right child tree of q.
                *  B - left child tree of q.
                *  C - left child tree of p.
                *      (Deletion occurred in tree C.)
                */

                /* For the rotation:
                *  - tree B replaces node q as the right child of p.
                *  - node p replaces tree B as the left child of q.
                */
               /* O saldo (p, q) será:
                 * (2,1), ou (2,0)
                 * /

                 / * Existe a seguinte estrutura de árvore:
                 * A - árvore filha certa de q.
                 * B - árvore filha esquerda de q.
                 * C - árvore filha esquerda de p.
                 * (Exclusão ocorreu na árvore C.)
                 * /

                 / * Para a rotação:
                 * - a árvore B substitui o nó q como o filho certo de p.
                 * - o nó p substitui a árvore B como o filho esquerdo de q.
                 */
                p->right = q->left;
                q->left = p;

                /* A child pointer of p's parent changes from p to q.
                * If p was the root, the root node changes.
                */
                /* Um ponteiro filho do pai de p muda de p para q.
                 * Se p for a raiz, o nó raiz muda.
                 */
                if(tos != 0) {
                    stack[tos-1]->left = q;
                }
                else {
                    t->root = q;
                }

                /* Update balance information of nodes p and q. */
                if(q->balance == 0) {
                    p->balance = 1;
                    q->balance = -1;
                    break;  /* Tree is balanced. */
                }
                else {
                    p->balance = q->balance = 0;
                }
		    
		        /* Unless q->balance == 0, iterations will continue, since
		        * the length of longest path has decreased.
		        */
               /* A menos que q-> balance == 0, as iterações continuarão, uma vez que
                * o comprimento do caminho mais longo diminuiu.
                */
		    }
		    else {
                /* The balance of (p, q) will be (2,-1)
                */
		    
                /* There is the following tree structure:
                *  A - right child tree of q.
                *  B - right child tree of r.
                *  C - left child tree of r.
                *  D - left child tree of p. (Deletion occurred in tree D)
                */

                /* For the rotation:
                *  - tree B replaces node r as the left child of q.
                *  - tree C replaces node q as the right child of p.
                *  - node q replaces tree B as the right child of r.
                *  - node p replaces tree C as the left child of r.
                */
                /* O saldo de (p, q) será (2, -1)
                 * /

                 / * Existe a seguinte estrutura de árvore:
                 * A - árvore filha certa de q.
                 * B - árvore filha direita de r.
                 * C - árvore filha esquerda de r.
                 * D - árvore filha esquerda de p. (Exclusão ocorreu na árvore D)
                 * /

                 / * Para a rotação:
                 * - a árvore B substitui o nó r como o filho esquerdo de q.
                 * - a árvore C substitui o nó q como o filho certo de p.
                 * - o nó q substitui a árvore B como o filho certo de r.
                 * - o nó p substitui a árvore C como o filho esquerdo de r.
                 */
                r = q->left;
                q->left = r->right;
                p->right = r->left;
                r->right = q;
                r->left = p;  
                if(r->balance == 1) {
                    p->balance = -1;
                    q->balance = 0;
                }
                else if(r->balance == -1) {
                    p->balance = 0;
                    q->balance = 1;
                }
                else {
                    p->balance = q->balance = 0;
                }
		        r->balance = 0;
		    
                /* A child pointer of p's parent changes from p to r.
                * If p was the root, the root node changes.
                */
                /* Um ponteiro filho do pai de p muda de p para r.
                 * Se p for a raiz, o nó raiz muda.
                 */
                if(tos != 0) {
                    stack[tos-1]->left = r;
                }
                else {
                    t->root = r;
                }
		    
                /* Continue with further iterations, since the length of
                * longest path has decreased.
                */
                /* Continue com outras iterações, uma vez que o comprimento de
                 * o caminho mais longo diminuiu.
                 */
		        }
	        }
	    }
    }    
    return return_item;
}
