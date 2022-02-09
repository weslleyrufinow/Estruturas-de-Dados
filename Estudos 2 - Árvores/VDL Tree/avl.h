/*** File avl.h - AVL Tree ***/
/*
 *   Shane Saunders
 */
#ifndef AVL_H
#define AVL_H


/* Size of the stack used for storing path travesersed through the tree.
 * This should be defined to be plenty large enough to accomodate the maximum
 * practical tree depth which could be expected.
 */
/* Tamanho da pilha usada para armazenar o caminho percorrido pela árvore.
  * Deve ser definido para ser grande o suficiente para acomodar o máximo
  * profundidade prática da árvore que poderia ser esperada.
  */
#define AVL_STACK_SIZE 1000


/* Structure type for nodes in the AVL tree. */
typedef struct avl_node {
    void *item;
    struct avl_node *left, *right;
    signed char balance;
} avl_node_t;

/* Structure type for the AVL tree. */
typedef struct avl {
    avl_node_t *root;
    int n;
    int (* compar)(const void *, const void *);
    avl_node_t **stack;
    signed char *path_info;
} avl_t;

/* avl_alloc() - Allocates space for a AVL tree and returns a pointer to it.
 * The function compar compares they keys of two items, and returns a negative,
 * zero, or positive integer depending on whether the first item is less than,
 * equal to, or greater than the second.
 */
/* avl_alloc () - Aloca espaço para uma árvore AVL e retorna um ponteiro para ela.
  * A função compara as chaves de dois itens e retorna um negativo,
  * zero ou número inteiro positivo, dependendo se o primeiro item é menor que,
  * igual ou maior que o segundo.
  */
avl_t *avl_alloc(int (* compar)(const void *, const void *));

/* avl_free() - Frees space used by the AVL tree pointed to by t. */
/* avl_free () - Libera espaço usado pela árvore AVL apontada por t. */
void avl_free(avl_t *t);

/* avl_insert() - Inserts an item into the AVL tree pointed to by t,
 * according the the value its key.  The key of an item in the AVL tree must
 * be unique among items in the tree.  If an item with the same key already
 * exists in the tree, a pointer to that item is returned.  Otherwise, NULL is
 * returned, indicating insertion was successful.
 */
/* avl_insert () - Insere um item na árvore AVL apontado por t,
  * de acordo com o valor de sua chave. A chave de um item na árvore AVL deve
  * ser único entre os itens da árvore. Se um item com a mesma chave já
  * existe na árvore, um ponteiro para esse item é retornado. Caso contrário, NULL é
  * retornado, indicando que a inserção foi bem-sucedida.
  */
void *avl_insert(avl_t *t, void *item);

/* avl_find() - Find an item in the AVL tree with the same key as the
 * item pointed to by `key_item'.  Returns a pointer to the item found, or NULL
 * if no item was found.
 */
/* avl_find () - Encontre um item na árvore AVL com a mesma chave que o
  * item apontado por `key_item '. Retorna um ponteiro para o item encontrado, ou NULL
  * se nenhum item foi encontrado.
  */
void *avl_find(avl_t *t, void *key_item);

/* avl_find_min() - Returns a pointer to the minimum item in the AVL
 * tree pointed to by t.  If there are no items in the tree a NULL pointer is
 * returned.
 */
/* avl_find_min () - Retorna um ponteiro para o item mínimo no AVL
  * árvore apontada por t. Se não houver itens na árvore, um ponteiro NULL é
  * devolvida.
  */
void *avl_find_min(avl_t *t);

/* avl_delete() - Delete the first item found in the AVL tree with
 * the same key as the item pointed to by `key_item'.  Returns a pointer to the
 * deleted item, and NULL if no item was found.
 */
/* avl_delete () - Exclui o primeiro item encontrado na árvore AVL com
  * a mesma chave do item apontado por `key_item '. Retorna um ponteiro para o
  * item excluído e NULL se nenhum item for encontrado.
  */
void *avl_delete(avl_t *t, void *key_item);

/* avl_delete_min() - Deletes the item with the smallest key from the AVL
 * tree pointed to by t.  Returns a pointer to the deleted item.
 * Returns a NULL pointer if there are no items in the tree.
 */
/* avl_delete_min () - Exclui o item com a menor chave do AVL
  * árvore apontada por t. Retorna um ponteiro para o item excluído.
  * Retorna um ponteiro NULL se não houver itens na árvore.
  */
void *avl_delete_min(avl_t *t);

#endif
