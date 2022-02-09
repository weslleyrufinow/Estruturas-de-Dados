#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


typedef struct Tree {
    void *value;
    struct Tree *left;
    struct Tree *right;
} Tree;

Tree *tree_create(void *value, Tree *left, Tree *right);
void  tree_destroy(Tree *tree);

void print_char(void *a);
int compar_char(void *a, void *b);

Tree *tree_find_main(Tree *tree, void *value, int (*compar)(void*,void*), void (*print_char)(void*));
Tree *tree_find(Tree *tree, void *value, int (*compar)(void*,void*));

void tree_print_main(Tree *tree, void (*print)(void *));
void tree_print(Tree *tree, void (*print)(void *));

void tree_inOrder(Tree *tree, void (*process)(void *));
void tree_preOrder(Tree *tree, void (*process)(void *));
void tree_postOrder(Tree *tree, void (*process)(void *));

void tree_print_level_main(Tree *bst, void (*print)(void *));
void tree_print_level(Tree *bst, void (*print)(void *), int level, char c);

void tree_height_main(Tree *tree);
int tree_height(Tree *tree);

void tree_eval_main(Tree *t);
int tree_eval(Tree *t);

/*** File rbtree.h - Red-Black Tree ***/
/*
 *   Shane Saunders
 */
#ifndef RBTREE_H
#define RBTREE_H

#define RBTREE_STACK_SIZE 1000


typedef enum {Red,Black} rbtree_colour_t;


/* Structure type for nodes in the red-black tree. */
typedef struct rbtree_node {
    void *item;
    struct rbtree_node *left, *right;
    rbtree_colour_t colour;
} rbtree_node_t;

/* Structure type for the red-black tree. */
typedef struct rbtree {
    rbtree_node_t *root;
    int n;
    int (* compar)(const void *, const void *);
    rbtree_node_t **stack;
} rbtree_t;

void rbtree_print_level_main(rbtree_node_t *bst, void (*print)(void *));
void rbtree_print_level(rbtree_node_t *bst, void (*print)(void *), int level, char c);


/* rbtree_alloc() - Allocates space for a red-black tree and returns a pointer
 * to it.  The function compar compares they keys of two items, and returns a
 * negative, zero, or positive integer depending on whether the first item is
 * less than, equal to, or greater than the second.
 */
rbtree_t *rbtree_alloc(int (* compar)(const void *, const void *));

/* rbtree_free() - Frees space used by the red-black tree pointed to by t. */
void rbtree_free(rbtree_t *t);

/* rbtree_insert() - Inserts an item into the red-black tree pointed to by t,
 * according the the value its key.  The key of an item in the red-black
 * tree must be unique among items in the tree.  If an item with the same key
 * already exists in the tree, a pointer to that item is returned.  Otherwise,
 * NULL is returned, indicating insertion was successful.
 */
void *rbtree_insert(rbtree_t *t, void *item);

/* rbtree_find() - Find an item in the red-black tree with the same key as the
 * item pointed to by `key_item'.  Returns a pointer to the item found, or NULL
 * if no item was found.
 */
void *rbtree_find(rbtree_t *t, void *key_item);

/* rbtree_find_min() - Returns a pointer to the minimum item in the red-black
 * tree pointed to by t.  If there are no items in the tree a NULL pointer is
 * returned.
 */
void *rbtree_find_min(rbtree_t *t);

/* rbtree_delete() - Delete an item in the red-black tree with the same key as
 * the item pointed to by `key_item'.  Returns a pointer to the  deleted item,
 * and NULL if no item was found.
 */
void *rbtree_delete(rbtree_t *t, void *key_item);

/* rbtree_delete_min() - Deletes the item with the smallest key from the binary
 * search tree pointed to by t.  Returns a pointer to the deleted item.
 * Returns a NULL pointer if there are no items in the tree.
 */
void *rbtree_delete_min(rbtree_t *t);

#endif

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

void avltree_print_level_main(avl_node_t *bst, void (*print)(void *));
void avltree_print_level(avl_node_t *bst, void (*print)(void *), int level, char c);


/* avl_alloc() - Allocates space for a AVL tree and returns a pointer to it.
 * The function compar compares they keys of two items, and returns a negative,
 * zero, or positive integer depending on whether the first item is less than,
 * equal to, or greater than the second.
 */
avl_t *avl_alloc(int (* compar)(const void *, const void *));

/* avl_free() - Frees space used by the AVL tree pointed to by t. */
void avl_free(avl_t *t);

/* avl_insert() - Inserts an item into the AVL tree pointed to by t,
 * according the the value its key.  The key of an item in the AVL tree must
 * be unique among items in the tree.  If an item with the same key already
 * exists in the tree, a pointer to that item is returned.  Otherwise, NULL is
 * returned, indicating insertion was successful.
 */
void *avl_insert(avl_t *t, void *item);

/* avl_find() - Find an item in the AVL tree with the same key as the
 * item pointed to by `key_item'.  Returns a pointer to the item found, or NULL
 * if no item was found.
 */
void *avl_find(avl_t *t, void *key_item);

/* avl_find_min() - Returns a pointer to the minimum item in the AVL
 * tree pointed to by t.  If there are no items in the tree a NULL pointer is
 * returned.
 */
void *avl_find_min(avl_t *t);

/* avl_delete() - Delete the first item found in the AVL tree with
 * the same key as the item pointed to by `key_item'.  Returns a pointer to the
 * deleted item, and NULL if no item was found.
 */
void *avl_delete(avl_t *t, void *key_item);

/* avl_delete_min() - Deletes the item with the smallest key from the AVL
 * tree pointed to by t.  Returns a pointer to the deleted item.
 * Returns a NULL pointer if there are no items in the tree.
 */
void *avl_delete_min(avl_t *t);

#endif


