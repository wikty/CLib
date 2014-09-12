#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <stdlib.h>
#include "bitree.h"

#define AVL_LEFT_HEAVY	1
#define AVL_RIGHT_HEAVY	-1
#define AVL_BALANCED	0

typedef BiTree AvlTree;

/* AvlNode as BiTreeNode's data */
typedef struct AvlNode_{
	void *data;
	/* balancing factor */
	int factor;
	/* lazy removing, avoid adjust tree when the removed data is inserted again */
	int hidden;
}AvlNode;

extern void avltree_init(AvlTree *alt,
						void (*destroy)(void *data),
						int (*compare)(const void *data1, const void *data2));

extern void avltree_destroy(AvlTree *alt);

/*
 *	@return: -1 => failure
 *			 0 => success
 *			 1 => existed
 */
extern int avltree_insert(AvlTree *alt, const void *data);

extern int avltree_remove(AvlTree *alt, const void *data);

extern int avltree_linearize(const AvlTree *alt, List *lst);

extern void avltree_dump(const AvlTree *alt, void (*print)(const void *data));

#define avltree_size(alt)	((alt)->size)
/*#define avltree_root(alt)	((alt)->root)*/
#define avltree_root_data(alt)	((alt)->root == NULL ? NULL : ((AvlNode *)alt->root->data)->data)
#define avltree_is_empty(alt) ((alt)->root == NULL ? 1 : 0)

#endif