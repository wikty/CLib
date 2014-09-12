#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "bitree.h"
#include "avltree.h"

#define avltree_get_avl(pNode)	((AvlNode *)((pNode)->data))


static int insert(AvlTree *alt, BiTreeNode **ppNode, const void *data, int *balanced);
static int remove(AvlTree *alt, BiTreeNode *pNode, const void *data);
static void avltree_remove_right(AvlTree *alt, BiTreeNode *pNode);
static void avltree_remove_left(AvlTree *alt, BiTreeNode *pNode);
static void rotate_left(BiTreeNode **ppNode);
static void rotate_right(BiTreeNode **ppNode);
static void *extract_avl(const void *data){
	if(((AvlNode *)data)->hidden){
		return NULL;
	}
	return ((AvlNode *)data)->data;
}

void avltree_init(AvlTree *alt,
					void (*destroy)(void *data),
					int (*compare)(const void *data1, const void *data2)
	){
	alt->root = NULL;
	alt->compare =  compare;
	alt->destroy = destroy;
	alt->size = 0;
}

void avltree_destroy(AvlTree *alt){
	avltree_remove_left(alt, NULL);

	memset(alt, 0, sizeof(*alt));
}


int avltree_insert(AvlTree *alt, const void *data){
	int balanced = 0;
	return insert(alt, &(alt->root), data, &balanced);
}

int avltree_remove(AvlTree *alt, const void *data){
	return remove(alt, alt->root, data);
}

int avltree_linearize(const AvlTree *alt, List *lst){
	return bitree_map(alt->root, extract_avl, lst, 1);
}

void avltree_dump(const AvlTree *alt, void (*print)(const void *data)){
	List lst;
	list_init(&lst, NULL, NULL);

	bitree_map(alt->root, extract_avl, &lst, 1);
	list_dump(&lst, print);

	list_destroy(&lst);
}

/*
 * Internal function
 */
void avltree_remove_left(AvlTree *alt, BiTreeNode *pNode){
	if(alt->root == NULL){
		return;
	}
	BiTreeNode **ppNode;
	if(pNode == NULL){
		ppNode = &(alt->root);
	}
	else{
		if(pNode->left == NULL){
			return;
		}
		ppNode = &(pNode->left);
	}

	if(*ppNode != NULL){
		avltree_remove_left(alt, *ppNode);
		avltree_remove_right(alt, *ppNode);
	}

	if(alt->destroy != NULL){
		alt->destroy(avltree_get_avl(*ppNode)->data);
	}

	free((*ppNode)->data);
	free(*ppNode);
	*ppNode = NULL;

	alt->size--;
	return;
}

void avltree_remove_right(AvlTree *alt, BiTreeNode *pNode){
	if(alt->root == NULL){
		return;
	}
	
	BiTreeNode **ppNode;
	if(pNode == NULL){
		ppNode = &(alt->root);
	}
	else{
		if(pNode->right == NULL){
			return;
		}
		ppNode = &(pNode->right);
	}

	if(*ppNode != NULL){
		avltree_remove_left(alt, *ppNode);
		avltree_remove_right(alt, *ppNode);
	}

	if(alt->destroy != NULL){
		alt->destroy(avltree_get_avl(*ppNode)->data);
	}

	free((*ppNode)->data);
	free(*ppNode);
	*ppNode = NULL;

	alt->size--;
	return;
}

void rotate_left(BiTreeNode **ppNode){
	BiTreeNode *lNode = (*ppNode)->left;

	if(avltree_get_avl(lNode)->factor == AVL_LEFT_HEAVY){
		/* LL rotate */
		(*ppNode)->left = lNode->right;
		lNode->right = *ppNode;
		avltree_get_avl(*ppNode)->factor = AVL_BALANCED;
		*ppNode = lNode;
		avltree_get_avl(lNode)->factor = AVL_BALANCED;
	}
	else{
		/* LR rotate */
		BiTreeNode *lrNode = lNode->right;
		lNode->right = lrNode->left;
		(*ppNode)->left = lrNode->right;
		lrNode->left = lNode;
		lrNode->right = *ppNode;
		
		switch(avltree_get_avl(lrNode)->factor){
			case AVL_LEFT_HEAVY:
				avltree_get_avl(*ppNode)->factor = AVL_RIGHT_HEAVY;
				avltree_get_avl(lNode)->factor = AVL_BALANCED;
				avltree_get_avl(lrNode)->factor = AVL_BALANCED;
				break;
			case AVL_RIGHT_HEAVY:
				avltree_get_avl(*ppNode)->factor = AVL_BALANCED;
				avltree_get_avl(lNode)->factor = AVL_LEFT_HEAVY;
				avltree_get_avl(lrNode)->factor = AVL_BALANCED;
				break;
			case AVL_BALANCED:
				avltree_get_avl(*ppNode)->factor = AVL_BALANCED;
				avltree_get_avl(lNode)->factor = AVL_BALANCED;
				avltree_get_avl(lrNode)->factor = AVL_BALANCED;
				break;
		}
		*ppNode = lrNode;
	}

}

void rotate_right(BiTreeNode **ppNode){
	BiTreeNode *rNode = (*ppNode)->right;

	if(avltree_get_avl(rNode)->factor == AVL_RIGHT_HEAVY){
		/* RR Rotate */
		(*ppNode)->right = rNode->left;
		rNode->left = *ppNode;
		avltree_get_avl(*ppNode)->factor = AVL_BALANCED;
		*ppNode = rNode;
		avltree_get_avl(rNode)->factor = AVL_BALANCED;
	}
	else{
		/* RL Rotate */
		BiTreeNode *rlNode = rNode->left;
		(*ppNode)->right = rlNode->left;
		rNode->left = rlNode->right;
		rlNode->left = *ppNode;
		rlNode->right = rNode;

		switch(avltree_get_avl(rlNode)->factor){
			case AVL_LEFT_HEAVY:
				avltree_get_avl(*ppNode)->factor = AVL_BALANCED;
				avltree_get_avl(rNode)->factor = AVL_RIGHT_HEAVY;
				avltree_get_avl(rlNode)->factor = AVL_BALANCED;
				break;
			case AVL_RIGHT_HEAVY:
				avltree_get_avl(*ppNode)->factor = AVL_LEFT_HEAVY;
				avltree_get_avl(rNode)->factor = AVL_BALANCED;
				avltree_get_avl(rlNode)->factor = AVL_BALANCED;
				break;
			case AVL_BALANCED:
				avltree_get_avl(*ppNode)->factor = AVL_BALANCED;
				avltree_get_avl(rNode)->factor = AVL_BALANCED;
				avltree_get_avl(rlNode)->factor = AVL_BALANCED;
				break;
		}
		*ppNode = rlNode;
	}
}


int insert(AvlTree *alt, BiTreeNode **ppNode, const void *data, int *balanced){
	AvlNode *avlNode;

	if(alt->root == NULL){
		if((avlNode = (AvlNode *)malloc(sizeof(AvlNode))) == NULL){
			return -1;
		}

		avlNode->hidden = 0;
		avlNode->factor = AVL_BALANCED;
		avlNode->data = (void *)data;

		return bitree_add_left(alt, NULL, avlNode);
	}
	else{
		int cmpval, retval;
		cmpval = alt->compare(data, avltree_get_avl(*ppNode)->data);
		if(cmpval < 0)	{
			if((*ppNode)->left == NULL){
				if((avlNode = (AvlNode *)malloc(sizeof(AvlNode))) == NULL){
					return -1;
				}

				avlNode->hidden = 0;
				avlNode->factor = AVL_BALANCED;
				avlNode->data = (void *)data;

				if((retval = bitree_add_left(alt, *ppNode, avlNode)) != 0){
					return retval;
				}

				*balanced = 0;
			}
			else{
				if((retval = insert(alt, &((*ppNode)->left), data, balanced)) != 0){
					return retval;
				}
			}

			/* rebalance tree */
			if((*balanced) == 0){
				switch(avltree_get_avl(*ppNode)->factor){
					case AVL_LEFT_HEAVY:
						rotate_left(ppNode);
						*balanced = 1;
						break;
					case AVL_RIGHT_HEAVY:
						avltree_get_avl(*ppNode)->factor = AVL_BALANCED;
						*balanced = 1;
						break;
					case AVL_BALANCED:
						avltree_get_avl(*ppNode)->factor = AVL_LEFT_HEAVY;
						break;
				}
			}
		}
		else if(cmpval > 0){
			if((*ppNode)->right == NULL){
				if((avlNode = (AvlNode *)malloc(sizeof(AvlNode))) == NULL){
					return -1;
				}

				avlNode->hidden = 0;
				avlNode->factor = AVL_BALANCED;
				avlNode->data = (void *)data;

				if((retval = bitree_add_right(alt, *ppNode, avlNode)) != 0){
					return retval;
				}

				*balanced = 0;
			}
			else{
				if((retval = insert(alt, &((*ppNode)->right), data, balanced)) != 0){
					return retval;
				}
			}

			/* rebalance tree */
			if((*balanced) == 0){
				switch(avltree_get_avl(*ppNode)->factor){
					case AVL_LEFT_HEAVY:
						avltree_get_avl(*ppNode)->factor = AVL_BALANCED;
						*balanced = 1;
						break;
					case AVL_RIGHT_HEAVY:
						rotate_right(ppNode);
						*balanced = 1;
						break;
					case AVL_BALANCED:
						avltree_get_avl(*ppNode)->factor = AVL_RIGHT_HEAVY;
						break;
				}
			}
		}
		else{
			if(avltree_get_avl(*ppNode)->hidden){
				/* data had be hidden */
				if(alt->destroy != NULL){
					alt->destroy(avltree_get_avl(*ppNode)->data);
				}

				avltree_get_avl(*ppNode)->data = (void *)data;
				avltree_get_avl(*ppNode)->hidden = 0;

				*balanced = 1;
			}
			else{
				/* data is existed */
				return 1;
			}
		}
	}
	return 0;
}

int remove(AvlTree *alt, BiTreeNode *pNode, const void *data){
	int cmpval, retval;

	if(pNode == NULL){
		return -1;
	}

	cmpval = alt->compare(data, avltree_get_avl(pNode)->data);
	if(cmpval < 0){
		retval = remove(alt, pNode->left, data);
	}
	else if(cmpval > 0){
		retval = remove(alt, pNode->right, data);
	}
	else{
		avltree_get_avl(pNode)->hidden = 1;
		alt->size--;
		retval = 0;
	}

	return retval;
}