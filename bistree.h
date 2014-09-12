#ifndef BISTREE_H_
#define BISTREE_H_

#include <stdlib.h>

#include "list.h"
#include "bitree.h"

typedef BiTreeNode BisTreeNode;
typedef BiTree BisTree;

#define bistree_init	bitree_init
#define bistree_destroy	bitree_destroy
#define bistree_size(bst)	((bst)->size)
#define bistree_root(bst)	((bst)->root)
#define bistree_is_empty(bst) ((bst)->root == NULL ? 1 : 0)
#define bistree_dump	bitree_dump

/*
 *	@return: 0 => success
 *			 -1 => failure
 *			 2..n => bistree currently has n data
 */
extern int bistree_insert(BisTree *bst, const void *data);
extern int bistree_remove(BisTree *bst, const void *data);
extern int bistree_linearize(const BisTree *bst, List *lst);

#endif