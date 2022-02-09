#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "Tree.h"


Tree *tree_create (void *value, Tree *left, Tree *right){
    Tree *tree = NULL;
    if(value){
        tree = (Tree *) malloc(sizeof(Tree));
        tree->value = value;
        tree->left  = (Tree *)left;
        tree->right = (Tree *)right;
        
    }
return tree;}

void tree_destroy(Tree *tree) {
    if (tree) {
        tree_destroy(tree->left);
        tree_destroy(tree->right);
        free(tree);
    }
}

void print_char(void *a){
    printf("%c", *((char*) a));
}

int compar_char(void *a, void *b) {
    return *((char*) a) - *((char*) b);
}

Tree *tree_find_main(Tree *tree, void *value, int (*compar)(void*,void*), void (*print_char)(void*)){
    Tree *p = NULL;
    p = tree_find(tree,value,compar);
    if(p == NULL){
        printf("Tree_find retornou NULL\n");
    }else{
        printf("Valor encontrado: ");
        print_char(p->value); printf("\n");
    }
}

Tree *tree_find(Tree *tree, void *value, int (*compar)(void*,void*)){
    Tree *node = NULL;

    if (tree && value && compar) {
        if (compar(value, tree->value) == 0)
            node = tree;
        else {
            node = tree_find(tree->left, value, compar);
            if (node == NULL)
                node = tree_find(tree->right, value, compar);
        }
    }

    return node;
}

void tree_print_main(Tree *tree, void (*print)(void *)){
    tree_print(tree,print);
    printf("\n");
}

void tree_print(Tree *tree, void (*print)(void *)) {
    if (tree && print) {
        printf("(");
        print(tree->value);
        printf(" ");
        tree_print(tree->left, print);
        tree_print(tree->right, print);
        printf(")");
    }
    else
        printf("<> ");
}

void tree_inOrder(Tree *tree, void (*process)(void *)){
    if(tree){
        if(tree->value){
            tree_inOrder(tree->left, process);
            process(tree);
            tree_inOrder(tree->right, process);
        }
    }
}

void tree_preOrder(Tree *tree, void (*process)(void *)){
    if(tree){
        if(tree->value){
            process(tree);
            tree_preOrder(tree->left, process);
            tree_preOrder(tree->right, process);
        }
    }
}

void tree_postOrder(Tree *tree, void (*process)(void *)){
    if(tree){
        if(tree->value){
            tree_postOrder(tree->left, process);
            tree_postOrder(tree->right, process);
            process(tree);
        }
    }
}

/*
 3 + 6 * 4 - 1 + 5
        +
      /   \
     *     5
   /   \
  +     -
 / \   / \
3   6 4   1

Pre-ordem:
 + * + 3 6 - 4 1 5

In-ordem:
3 + 6 * 4 - 1 + 5

Pos-ordem:
3 6 + 4 1 - * 5 +
*/
/*
void tree_queue(Tree *tree, Queue *q){
    if(tree){
        if(tree->value){
            tree_queue(tree->left,q);
            tree_queue(tree->right,q);
            Queue_push(q,tree->value);
        }
    }
}
*/

void tree_print_level_main(Tree *bst, void (*print)(void *)){
    int level = 0;
    if (print) {
        tree_print_level(bst, print, level, '.');
    }
}

void tree_print_level(Tree *bst, void (*print)(void *), int level, char c){
    int i;

    for (i=0; i<level; i++)
        printf("\t");

    printf("%c/", c);
    if (bst) {
        print(bst->value);
        printf("\n");


        tree_print_level(bst->right, print, level + 1, 'r');
        tree_print_level(bst->left,  print, level + 1, 'l');
    }
    else
        printf("~\n");
}



void tree_height_main(Tree *tree){
    int n;
    n = tree_height(tree);
    printf("Altura da arvore: %d\n", n);
}

int tree_height(Tree *tree){
    int l, r;
    if (tree == NULL) {
        return 0;
    }
    else {
        l = 1 + tree_height(tree->left);
        r = 1 + tree_height(tree->right);

        if(l > r)
            return l;
        else
            return r;
    }
}

void tree_eval_main(Tree *t){
    int n;
    n = tree_eval(t);
    printf("Resultado da expressao: %d\n",n);
}

int tree_eval(Tree *t) {
    char c;
    
    if (t) {
        c = *( (char*)t->value );
        
        if (c == '+') {
            return tree_eval(t->left) + tree_eval(t->right);
        }
        else if (c == '*') {
            return tree_eval(t->left) * tree_eval(t->right);
        }
        else if (c == '-') {
            return tree_eval(t->left) - tree_eval(t->right);
        }
        else if (c == '/') {
            return tree_eval(t->left) / tree_eval(t->right);
        }
        else 
            return c - 48;
    }
    else
        return 0;
}

/*** File rbtree.c - Red-Black Tree ***/
/*
 *   Shane Saunders
 */
#include <stdlib.h>
#include <stdio.h>

/* Prototypes for functions only visible within this file. */
rbtree_node_t *rbtree_restructure(rbtree_t *t, int tos, rbtree_node_t *x, rbtree_node_t *y, rbtree_node_t *z);
rbtree_node_t *rbtree_restructure2(rbtree_t *t, int tos, rbtree_node_t *x, rbtree_node_t *y, rbtree_node_t *z);

/* rbtree_alloc() - Allocates space for a red-black tree and returns a pointer
 * to it.  The function compar compares they keys of two items, and returns a
 * negative, zero, or positive integer depending on whether the first item is
 * less than, equal to, or greater than the second.
 */
rbtree_t *rbtree_alloc(int (*compar)(const void *, const void *))
{
	rbtree_t *t;

	t = malloc(sizeof(rbtree_t));
	t->root = NULL;
	t->compar = compar;
	t->stack = malloc(RBTREE_STACK_SIZE * sizeof(rbtree_node_t *));
	t->n = 0;

	return t;
}



void rbtree_print_level_main(rbtree_node_t *bst, void (*print)(void *)){
    int level = 0;
    if (print) {
        rbtree_print_level(bst, print, level, '.');
    }
}

void rbtree_print_level(rbtree_node_t *bst, void (*print)(void *), int level, char c){
    int i;

    for (i=0; i<level; i++)
        printf("\t");

    printf("%c/", c);
    if (bst) {
        print(bst->item);
        printf("\n");


        rbtree_print_level(bst->right, print, level + 1, 'r');
        rbtree_print_level(bst->left,  print, level + 1, 'l');
    }
    else
        printf("~\n");
}


/* rbtree_free() - Frees space used by the red-black tree pointed to by t. */
void rbtree_free(rbtree_t *t)
{
	rbtree_node_t *p, **stack;
	int tos;

	/* In order to free all nodes in the tree a depth first search is performed
     * This is implemented using a stack.
     */

	if (t->root)
	{
		stack = t->stack;
		stack[0] = t->root;
		tos = 1;
		while (tos)
		{
			p = stack[--tos];
			if (p->left)
			{
				stack[tos++] = p->left;
			}
			if (p->right)
			{
				stack[tos++] = p->right;
			}
			free(p);
		}
		free(stack);
	}

	free(t);
}

/* rbtree_insert() - Inserts an item into the red-black tree pointed to by t,
 * according the the value its key.  The key of an item in the red-black
 * tree must be unique among items in the tree.  If an item with the same key
 * already exists in the tree, a pointer to that item is returned.  Otherwise,
 * NULL is returned, indicating insertion was successful.
 */
void *rbtree_insert(rbtree_t *t, void *item)
{
	rbtree_node_t *x, *p, *q, *m, **attach_x;
	int (*compar)(const void *, const void *);
	int cmp_result;
	rbtree_colour_t col;
	rbtree_node_t **stack;
	int tos;

	tos = 0;
	if ((p = t->root))
	{
		compar = t->compar;
		stack = t->stack;

		/* Repeatedly explore either the left branch or the right branch
		* depending on the value of the key, until an empty branch is chosen.
		*/
		for (;;)
		{
			stack[tos++] = p;
			cmp_result = compar(item, p->item);
			if (cmp_result < 0)
			{
				p = p->left;
				if (!p)
				{
					p = stack[--tos];
					attach_x = &p->left;
					break;
				}
			}
			else if (cmp_result > 0)
			{
				p = p->right;
				if (!p)
				{
					p = stack[--tos];
					attach_x = &p->right;
					break;
				}
			}
			else
			{
				return p->item;
			}
		}
		col = Red;
	}
	else
	{
		attach_x = &t->root;
		col = Black;
	}

	x = malloc(sizeof(rbtree_node_t));
	x->left = x->right = NULL;
	x->item = item;
	x->colour = col;

	*attach_x = x;
	t->n++;

	/* Restructuring or recolouring will be needed if node x and its parent, p,
     * are both red.
     */
	if (tos > 0)
		while (p->colour == Red)
		{ /* Double red problem. */

			/* Obtain a pointer to p's parent, m, and sibling, q. */
			m = stack[--tos];
			q = p == m->left ? m->right : m->left;

			/* Determine whether restructuring or recolouring is needed. */
			if (!q || q->colour == Black)
			{
				/* Sibling is black.  ==>  Perform restructuring. */

				/* Restructure according to the left to right order, of nodes
				* m, p, and x.
				*/
				m = rbtree_restructure(t, tos, m, p, x);
				m->colour = Black;
				m->left->colour = m->right->colour = Red;

				/* Restructuring eliminates the double red problem. */
				break;
			}
			/* else */

			/* Sibling is also red.  ==>  Perform recolouring. */
			p->colour = Black;
			q->colour = Black;

			if (tos == 0)
				break; /* The root node always remains black. */

			m->colour = Red;

			/* Continue, checking colouring higher up. */
			x = m;
			p = stack[--tos];
		}

	return NULL;
}

/* rbtree_find() - Find an item in the red-black tree with the same key as the
 * item pointed to by `key_item'.  Returns a pointer to the item found, or NULL
 * if no item was found.
 */
void *rbtree_find(rbtree_t *t, void *key_item)
{
	rbtree_node_t *p, *next_p;
	int (*compar)(const void *, const void *);
	int cmp_result;

	compar = t->compar;

	if ((next_p = t->root))
	{
		/* Repeatedly explore either the left or right branch, depending on the
		* value of the key, until the correct item is found.
		*/
		do
		{
			p = next_p;
			cmp_result = compar(key_item, p->item);
			if (cmp_result < 0)
			{
				next_p = p->left;
			}
			else if (cmp_result > 0)
			{
				next_p = p->right;
			}
			else
			{
				/* Item found. */
				return p->item;
			}
		} while (next_p);
	}

	return NULL;
}

/* rbtree_find_min() - Returns a pointer to the minimum item in the red-black
 * tree pointed to by t.  If there are no items in the tree a NULL pointer is
 * returned.
 */
void *rbtree_find_min(rbtree_t *t)
{
	rbtree_node_t *p, *next_p;

	if ((next_p = t->root))
	{
		/* To locate the minimum, the left branches is repeatedly chosen until
	 * we can explore no further.
         */
		do
		{
			p = next_p;
			next_p = p->left;
		} while (next_p);
	}
	else
	{
		return NULL;
	}

	return p->item;
}

/* rbtree_delete() - Delete an item in the red-black tree with the same key as
 * the item pointed to by `key_item'.  Returns a pointer to the deleted item,
 * and NULL if no item was found.
 */
void *rbtree_delete(rbtree_t *t, void *key_item)
{
	rbtree_node_t *p, *r, *x, *y, *z, *b, *new_y;
	rbtree_node_t *m;
	rbtree_colour_t remove_col;
	void *return_item;
	int (*compar)(const void *, const void *);
	int cmp_result;
	rbtree_node_t **stack;
	int i, tos;

	/* Attempt to locate the item to be deleted. */
	if ((p = t->root))
	{
		compar = t->compar;
		stack = t->stack;
		tos = 0;

		for (;;)
		{
			stack[tos++] = p;
			cmp_result = compar(key_item, p->item);
			if (cmp_result < 0)
			{
				p = p->left;
			}
			else if (cmp_result > 0)
			{
				p = p->right;
			}
			else
			{
				/* Item found. */
				break;
			}
			if (!p)
				return NULL;
		}
	}
	else
	{
		return NULL;
	}

	/* p points to the node to be deleted, and is currently on the top of the
     * stack.
     */
	if (!p->left)
	{
		tos--; /* Adjust tos to remove p. */
		/* Right child replaces p. */
		if (tos == 0)
		{
			r = t->root = p->right;
			x = y = NULL;
		}
		else
		{
			x = stack[--tos];
			if (p == x->left)
			{
				r = x->left = p->right;
				y = x->right;
			}
			else
			{
				r = x->right = p->right;
				y = x->left;
			}
		}
		remove_col = p->colour;
	}
	else if (!p->right)
	{
		tos--; /* Adjust tos to remove p. */
		/* Left child replaces p. */
		if (tos == 0)
		{
			r = t->root = p->left;
			x = y = NULL;
		}
		else
		{
			x = stack[--tos];
			if (p == x->left)
			{
				r = x->left = p->left;
				y = x->right;
			}
			else
			{
				r = x->right = p->left;
				y = x->left;
			}
		}
		remove_col = p->colour;
	}
	else
	{
		/* Save p's stack position. */
		i = tos - 1;

		/* Minimum child, m, in the right subtree replaces p. */
		m = p->right;
		do
		{
			stack[tos++] = m;
			m = m->left;
		} while (m);
		m = stack[--tos];

		/* Update either the left or right child pointers of p's parent. */
		if (i == 0)
		{
			t->root = m;
		}
		else
		{
			x = stack[i - 1]; /* p's parent. */
			if (p == x->left)
			{
				x->left = m;
			}
			else
			{
				x->right = m;
			}
		}

		/* Update the tree part m is removed from, and assign m the child
		* pointers of p (only if m is not the right child of p).
		*/
		stack[i] = m; /* Node m replaces node p on the stack. */
		x = stack[--tos];
		r = m->right;
		if (tos != i)
		{ /* x is equal to the parent of m. */
			y = x->right;
			x->left = r;
			m->right = p->right;
		}
		else
		{ /* m was the right child of p, and x is equal to m. */
			y = p->left;
		}
		m->left = p->left;

		/* We treat node m as the node which has been removed. */
		remove_col = m->colour;
		m->colour = p->colour;
	}

	/* Get return value and free the space used by node p. */
	return_item = p->item;
	free(p);

	t->n--;

	/* The pointers x, y, and r point to nodes which may be involved in
     * restructuring and recolouring.
     *  x - the parent of the removed node.
     *  y - the sibling of the removed node.
     *  r - the node which replaced the removed node.
     * From the above code, the next entry off the stack will be the parent of
     * node x.
     */

	/* The number of black nodes on paths to all external nodes (NULL child
     * pointers) must remain the same for all paths.  Restructuring or
     * recolouring of nodes may be necessary to enforce this.
     */
	if (remove_col == Black)
	{
		/* Removal of a black node requires some adjustment. */

		if (!r || r->colour == Black)
		{
			/* A black node replaced the deleted black node.  Note that
			* external nodes (NULL child pointers) are always black, so
			* if r is NULL it is treated as a black node.
			*/

			/* This causes a double-black problem, since node r would need to
			* be coloured double-black in order for the black colour on
			* paths through r to remain the same as for other paths.
			*/

			/* If r is the root node, the double-black colour is not necessary
			* to maintain the colour balance.  Otherwise, some adjustment of
			* nearby nodes is needed in order to eliminate the double-black
			* problem.  NOTE:  x points to the parent of r.
			*/
			if (x)
				for (;;)
				{

					/* There are three adjustment cases:
					*  1.  r's sibling, y, is black and has a red child, z.
					*  2.  r's sibling, y, is black and has two black children.
					*  3.  r's sibling, y, is red.
					*/
					if (y->colour == Black)
					{

						/* Note the conditional evaluation for assigning z. */
						if (((z = y->left) && z->colour == Red) ||
							((z = y->right) && z->colour == Red))
						{
							/* Case 1:  perform a restructuring of nodes x, y, and
							* z.
							*/

							b = rbtree_restructure(t, tos, x, y, z);
							b->colour = x->colour;
							b->left->colour = b->right->colour = Black;

							break;
						}
						else
						{
							/* Case 2:  recolour node y red. */

							y->colour = Red;

							if (x->colour == Red)
							{
								x->colour = Black;
								break;
							}
							/* else */

							if (tos == 0)
								break; /* Root level reached. */
									   /* else */

							r = x;
							x = stack[--tos]; /* x <- parent of x. */
							y = x->left == r ? x->right : x->left;
						}
					}
					else
					{
						/* Case 3:  Restructure nodes x, y, and z, where:
						*  - If node y is the left child of x, then z is the left
						*    child of y.  Otherwise z is the right child of y.
						*/
						if (x->left == y)
						{
							new_y = y->right;
							z = y->left;
						}
						else
						{
							new_y = y->left;
							z = y->right;
						}

						rbtree_restructure(t, tos, x, y, z);
						y->colour = Black;
						x->colour = Red;

						/* Since x has moved down a place in the tree, and y is the
						* new the parent of x, the stack must be adjusted so that
						* the parent of x is correctly identified in the next call
						* to rbtree_restructure().
						*/
						stack[tos++] = y;

						/* After restructuring, node r has a black sibling, new_y,
						* so either case 1 or case 2 applies.  If case 2 applies
						* the double-black problem does not reappear.
						*/
						y = new_y;

						/* Note the conditional evaluation for assigning z. */
						if (((z = y->left) && z->colour == Red) ||
							((z = y->right) && z->colour == Red))
						{
							/* Case 1:  perform a restructuring of nodes x, y, and
							* z.
							*/

							b = rbtree_restructure(t, tos, x, y, z);
							b->colour = Red; /* Since node x was red. */
							b->left->colour = b->right->colour = Black;
						}
						else
						{
							/* Case 2:  recolour node y red. */

							/* Note that node y is black and node x is red. */

							y->colour = Red;
							x->colour = Black;
						}

						break;
					}
				}
		}
		else
		{
			/* A red node replaced the deleted black node. */

			/* In this case we can simply colour the red node black. */
			r->colour = Black;
		}
	}

	return return_item;
}

/* rbtree_delete_min() - Deletes the item with the smallest key from the binary
 * search tree pointed to by t.  Returns a pointer to the deleted item.
 * Returns a NULL pointer if there are no items in the tree.
 */
void *rbtree_delete_min(rbtree_t *t)
{
	rbtree_node_t *p, *r, *x, *y, *z, *b, *new_y;
	rbtree_colour_t remove_col;
	void *return_item;
	rbtree_node_t **stack;
	int tos;

	/* Attempt to locate the item to be deleted. */
	if ((p = t->root))
	{
		stack = t->stack;
		tos = 0;

		/* To locate the minimum, the left branches is repeatedly chosen until
		* we can explore no further.
		*/
		do
		{
			stack[tos++] = p;
			p = p->left;
		} while (p);
		p = stack[--tos]; /* Node to be deleted. */
	}
	else
	{
		return NULL;
	}

	/* Right child replaces p. */
	if (tos == 0)
	{
		r = t->root = p->right;
		x = y = NULL;
	}
	else
	{
		x = stack[--tos];
		r = x->left = p->right;
		y = x->right;
	}
	remove_col = p->colour;

	/* Get return value and free space used by node p. */
	return_item = p->item;
	free(p);

	t->n--;

	/* The pointers x, y, and r point to nodes which may be involved in
     * restructuring and recolouring.
     *  x - the parent of the removed node.
     *  y - the sibling of the removed node.
     *  r - the node which replaced the removed node.
     */

	/* The number of black nodes on paths to all external nodes (NULL child
     * pointers) must remain the same for all paths.  Restructuring or
     * recolouring of nodes may be necessary to enforce this.
     */
	if (remove_col == Black)
	{
		/* Removal of a black node requires some adjustment. */

		if (!r || r->colour == Black)
		{
			/* A black node replaced the deleted black node.  Note that
			* external nodes (NULL child pointers) are always black, so
			* if r is NULL it is treated as a black node.
			*/

			/* This causes a double-black problem, since node r would need to
			* be coloured double-black in order for the black colour on
			* paths through r to remain the same as for other paths.
			*/

			/* If r is the root node, the double-black colour is not necessary
			* to maintain the colour balance.  Otherwise, some adjustment of
			* nearby nodes is needed in order to eliminate the double-black
			* problem.  NOTE:  x points to the parent of r.
			*/
			if (x)
				for (;;)
				{

					/* There are three adjustment cases:
					*  1.  r's sibling, y, is black and has a red child, z.
					*  2.  r's sibling, y, is black and has two black children.
					*  3.  r's sibling, y, is red.
					*/
					if (y->colour == Black)
					{

						/* Note the conditional evaluation for assigning z. */
						if (((z = y->left) && z->colour == Red) ||
							((z = y->right) && z->colour == Red))
						{
							/* Case 1:  perform a restructuring of nodes x, y, and
							* z.
							*/

							b = rbtree_restructure2(t, tos, x, y, z);
							b->colour = x->colour;
							b->left->colour = b->right->colour = Black;

							break;
						}
						else
						{
							/* Case 2:  recolour node y red. */

							y->colour = Red;

							if (x->colour == Red)
							{
								x->colour = Black;
								break;
							}
							/* else */

							if (tos == 0)
								break; /* Root level reached. */
									   /* else */

							r = x;
							x = stack[--tos]; /* x <- parent of x. */
							y = x->left == r ? x->right : x->left;
						}
					}
					else
					{
						/* Case 3:  Restructure nodes x, y, and z, where:
						*  - If node y is the left child of x, then z is the left
						*    child of y.  Otherwise z is the right child of y.
						*/
						if (x->left == y)
						{
							new_y = y->right;
							z = y->left;
						}
						else
						{
							new_y = y->left;
							z = y->right;
						}

						rbtree_restructure2(t, tos, x, y, z);
						y->colour = Black;
						x->colour = Red;

						/* Since x has moved down a place in the tree, and y is the
						* new the parent of x, the stack must be adjusted so that
						* the parent of x is correctly identified in the next call
						* to rbtree_restructure().
						*/
						stack[tos++] = y;

						/* After restructuring, node r has a black sibling, new_y,
						* so either case 1 or case 2 applies.  If case 2 applies
						* the double-black problem does not reappear.
						* Note:  x still points to the parent of r, but y must be
						* updated to point to r's new sibling, new_y.
						*/
						y = new_y;

						/* Note the conditional evaluation for assigning z. */
						if (((z = y->left) && z->colour == Red) ||
							((z = y->right) && z->colour == Red))
						{
							/* Case 1:  perform a restructuring of nodes x, y, and
							* z.
							*/

							b = rbtree_restructure2(t, tos, x, y, z);
							b->colour = Red; /* Since node x was red. */
							b->left->colour = b->right->colour = Black;
						}
						else
						{
							/* Case 2:  recolour node y red. */

							/* Note that node y is black and node x is red. */

							y->colour = Red;
							x->colour = Black;
						}

						break;
					}
				}
		}
		else
		{
			/* A red node replaced the deleted black node. */

			/* In this case we can simply colour the red node black. */
			r->colour = Black;
		}
	}

	return return_item;
}

/*** Restructuring functions. ***/

/* rbtree_restructure() - General restructuring function - checks for all
 * restructuring cases.
 */
rbtree_node_t *rbtree_restructure(rbtree_t *t, int tos, rbtree_node_t *x, rbtree_node_t *y, rbtree_node_t *z)
{
	rbtree_node_t *parent, *mid_node;

	if (y == x->left)
	{
		if (z == y->left)
		{ /* in-order:  z, y, x */
			mid_node = y;
			y->left = z;
			x->left = y->right;
			y->right = x;
		}
		else
		{ /* in-order:  y, z, x */
			mid_node = z;
			y->right = z->left;
			z->left = y;
			x->left = z->right;
			z->right = x;
		}
	}
	else
	{
		if (z == y->left)
		{ /* in-order:  x, z, y */
			mid_node = z;
			x->right = z->left;
			z->left = x;
			y->left = z->right;
			z->right = y;
		}
		else
		{ /* in-order:  x, y, z */
			mid_node = y;
			x->right = y->left;
			y->left = x;
			y->right = z;
		}
	}

	if (tos != 0)
	{
		parent = t->stack[tos - 1];
		if (x == parent->left)
		{
			parent->left = mid_node;
		}
		else
		{
			parent->right = mid_node;
		}
	}
	else
	{
		t->root = mid_node;
	}

	return mid_node;
}

/* rbtree_restructure2() - Restructuring function used by delete_min.  There
 * are fewer restructuring cases to consider since it is known that y will
 * always be the right child of x.
 */
rbtree_node_t *rbtree_restructure2(rbtree_t *t, int tos, rbtree_node_t *x, rbtree_node_t *y, rbtree_node_t *z)
{
	rbtree_node_t *parent, *mid_node;

	if (z == y->left)
	{ /* in-order:  x, z, y */
		mid_node = z;
		x->right = z->left;
		z->left = x;
		y->left = z->right;
		z->right = y;
	}
	else
	{ /* in-order:  x, y, z */
		mid_node = y;
		x->right = y->left;
		y->left = x;
		y->right = z;
	}

	if (tos != 0)
	{
		parent = t->stack[tos - 1];
		if (x == parent->left)
		{
			parent->left = mid_node;
		}
		else
		{
			parent->right = mid_node;
		}
	}
	else
	{
		t->root = mid_node;
	}

	return mid_node;
}


/* Test implementation which uses the stack history to replace the use of next
 * and prev pointers.
 */


/* avl_alloc() - Allocates space for a AVL tree and returns a pointer to it.
 * The function compar compares they keys of two items, and returns a negative,
 * zero, or positive integer depending on whether the first item is less than,
 * equal to, or greater than the second.
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



void avltree_print_level_main(avl_node_t *bst, void (*print)(void *)){
    int level = 0;
    if (print) {
        avltree_print_level(bst, print, level, '.');
    }
}

void avltree_print_level(avl_node_t *bst, void (*print)(void *), int level, char c){
    int i;

    for (i=0; i<level; i++)
        printf("\t");

    printf("%c/", c);
    if (bst) {
        print(bst->item);
        printf("\n");


        avltree_print_level(bst->right, print, level + 1, 'r');
        avltree_print_level(bst->left,  print, level + 1, 'l');
    }
    else
        printf("~\n");
}


/* avl_free() - Frees space used by the AVL tree pointed to by t. */
void avl_free(avl_t *t) {
    int tos;
    avl_node_t *p, **stack;

    /* In order to free all nodes in the tree a depth first search is performed
     * This is implemented using a stack.
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
    stack = t->stack;
    path_info = t->path_info;
    tos = 0;

    /* Search for insertion position, starting from the root node, if it
     * exists.
     */
    if((p = t->root)) {
	/* Repeatedly explore either the left branch or the right branch
	 * depending on the value of the key, until an empty branch position
	 * is found.
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
    return_result = NULL;
    
    /* Allocated space for the new node. */
    x = malloc(sizeof(avl_node_t));
    x->left = x->right = NULL;
    x->balance = 0;
    x->item = item;

    /* attach_x is a pointer to the pointer variable to add the node to the
     * tree.
     */
    *attach_x = x;
    t->n++;
    	
    /* Now traverse the stack, updating balance information of ancestors,
     * and performing rotation if necessary.
     */
    stack_n = tos;
    while(tos) {
        p = stack[--tos];
        if(p->balance == 0) {
            /* Balance changes from 0 to 1 or -1.  The length of the
            * longest path from  p to a leaf has increased by 1, so
            * continue the iteration to the parent of p.
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
                q = stack[tos + 1];
                if(path_info[tos] == path_info[tos + 1]) {
                /* There is the the following tree structure:
                *  A - x child tree of q.
                *  B - y child tree of q.
                *  C - y child of p.
                */

                    /* For the rotation:
                    *  - tree B replaces node q as the child of p.
                    *  - node p replaces tree B as the child of q.
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
void *avl_find(avl_t *t, void *key_item) {
    int (* compar)(const void *, const void *);
    int cmp_result;
    avl_node_t *p, *next_p;

	
    if((next_p = t->root)) {
         compar = t->compar;
	 
        /* Repeatedly explore either the left or right branch, depending on the
        * value of the key, until the correct item is found.
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
void *avl_find_min(avl_t *t) {
    avl_node_t *p, *next_p;

    if((next_p = t->root)) {
        /* To locate the minimum, the left branches is repeatedly chosen until
	    * we can explore no further.
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
    stack = t->stack;
    path_info = t->path_info;
    tos = 0;
    
    /* Attempt to locate the item to be deleted. */
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
        prev_m = stack[tos-1];
        if(prev_m != p) {
            prev_m->left = m->right;
            m->right = p->right;
        }
        m->left = p->left;

        /* Give node m the balance node p had, and replace the stack entry for
        * p with m.
        */
        m->balance = p->balance;
        stack[stack_p] = m;
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
    while(tos) {
        p = stack[--tos];
        if(p->balance == 0) {
            /* Balance changes from 0 to 1 or -1.  The length of only one
            * path from p to a leaf has decreased by 1, so the length of the
            * longest path is unchanged.  Therefore iteration can stop.
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
    stack = t->stack;
    tos = 0;
    
    /* Attempt to locate the item to be deleted. */
    if((p = t->root)) {
        /* To locate the minimum, the left branches is repeatedly chosen until
	    * we can explore no further.
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
    while(tos) {
	p = stack[--tos];
	if(p->balance == 0) {
	    /* Balance changes from 0 to 1.  The length of only one
	     * path from p to a leaf has decreased by 1, so the length of the
	     * longest path is unchanged.  Therefore iteration can stop.
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
	    
	    if(p->balance != 0) {
            /* Balance changes from 1 to 2.
            * Now the tree is unbalanced, and rotation must be
            * performed.
            */

            /* The kind of rotation that occurs depends on whether
            * the balance of p's other child (not the child p was reached
            * from) is in the same direction as the balance of p.
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
                p->right = q->left;
                q->left = p;

                /* A child pointer of p's parent changes from p to q.
                * If p was the root, the root node changes.
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
                if(tos != 0) {
                    stack[tos-1]->left = r;
                }
                else {
                    t->root = r;
                }
		    
                /* Continue with further iterations, since the length of
                * longest path has decreased.
                */
		        }
	        }
	    }
    }    
    return return_item;
}