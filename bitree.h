#ifndef BITREE_H_
#define BITREE_H_

#include <stdlib.h>
#include "list.h"

typedef struct BiTreeNode_{
	void *data;
	struct BiTreeNode_ *left;
	struct BiTreeNode_ *right;
}BiTreeNode;

typedef struct BiTree_{
	BiTreeNode *root;
	unsigned int size;
	void (*destroy)(void *data);
	int (*compare)(const void *data1, const void *data2);
}BiTree;

extern void bitree_init(BiTree *bt, 
						void (*destroy)(void *data),
						int (*compare)(const void *data1, const void *data2));

extern void bitree_destroy(BiTree *bt);

extern int bitree_add_left(BiTree *bt, BiTreeNode *pNode, const void *data);

extern int bitree_add_right(BiTree *bt, BiTreeNode *pNode, const void *data);

extern int bitree_remove_left(BiTree *bt, BiTreeNode *pNode);

extern int bitree_remove_right(BiTree *bt, BiTreeNode *pNode);

/*
 * @param: lst => User should initialize lst, will store data node
 * NOTICE: lst's node and bt's node pointer the same data space
 * 		   so if lst have destroy function, when destroy lst, the
 *			bt is destroied too
 */
extern int bitree_preorder(const BiTreeNode *pNode, List *lst);

/*
 * @param: lst => User should initialize lst, will store data node
 */
extern int bitree_inorder(const BiTreeNode *pNode, List *lst);

/*
 * @param: lst => User should initialize lst, will store data node
 */
extern int bitree_postorder(const BiTreeNode *pNode, List *lst);

/*
extern int bitree_search(BiTree *bt, const void *data, BiTreeNode **ppNode);
*/

/*
 *  @param: data give to bt->root->data
 *  after merge new tree, the original tree is not avaiable
 */
extern int bitree_merge(BiTree *bt, BiTree *left, BiTree *right, const void *data);

#define bitree_size(bt)	((bt)->size)
#define bitree_root(bt)	((bt)->root)
#define bitree_is_empty(bt)	((bt)->root == NULL ? 1 : 0)
#define bitree_is_leafnode(pNode)	((pNode)->left == NULL && (pNode)->right == NULL)
#define bitree_get_left(pNode)	((pNode)->left)
#define bitree_get_right(pNode)	((pNode)->right)
#define bitree_get_data(pNode)	((pNode)->data)

#endif