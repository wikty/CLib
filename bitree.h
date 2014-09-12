#ifndef BITREE_H_
#define BITREE_H_

#include <stdlib.h>

#include "list.h"

typedef struct BiTreeNode_{
	void *data;
	/* if insert same just count++ */
	unsigned int count;
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

/*
 *	@param: pNode
 *			if add root node, pNode is NULL
 *	@return: -1 => may be pNode had a left child, so failure
 *			0 => success
 */
extern int bitree_add_left(BiTree *bt, BiTreeNode *pNode, const void *data);


/*
 *	@param: pNode
 *			if add root node, pNode is NULL
 *	@return: -1 => may be pNode had a right child, so failure
 *			 0 => success
 */
extern int bitree_add_right(BiTree *bt, BiTreeNode *pNode, const void *data);

/*
 *  @param: pNode
 *			if want to remove the whole of the tree, pass NULL
 *	@return: 0 => success
 *			 -1 => failure
 */
extern int bitree_remove_left(BiTree *bt, BiTreeNode *pNode);

/*
 *  @param: pNode
 *			if want to remove the whole of the tree, pass NULL
 *	@return: 0 => success
 *			 -1 => failure
 */
extern int bitree_remove_right(BiTree *bt, BiTreeNode *pNode);

/*
 * @param: lst
 *			User should initialize lst, will store data node
 * NOTICE: lst's node and bt's node pointer the same data space
 * 		    so if lst have destroy function, when destroy lst, the
 *			bt is destroied too
 */
extern int bitree_preorder(const BiTreeNode *pNode, List *lst);

/*
 * @param: lst
 *			User should initialize lst, will store data node
 */
extern int bitree_inorder(const BiTreeNode *pNode, List *lst);

/*
 * @param: lst
 *			User should initialize lst, will store data node
 */
extern int bitree_postorder(const BiTreeNode *pNode, List *lst);

/*
 *	@function: walk through tree and process node with func(by preorder)
 *	@param: lst
 *			hold the process func's result, if no need, just give NULL
 *	@param: order
 *			0 => preorder
 *			1 => inorder
 *			-1 => postorder
 */
extern int bitree_map(const BiTreeNode *pNode, void* (*func)(const void *data), List *lst, int order);

/*
 *  @param: print
 *			NOTICE it's return a void pointer
 */
extern int bitree_dump(const BiTree *bt, void* (*print)(const void *data));

/*
extern int bitree_search(BiTree *bt, const void *data, BiTreeNode **ppNode);
*/

/*
 *  @param: data
 *			new tree bt's root data
 *	@function: after merge into new tree, the original tree is not avaiable
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