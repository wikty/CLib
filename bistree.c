#include <stdlib.h>
#include <string.h>
#include "bitree.h"
#include "bistree.h"


int bistree_insert(BisTree *bst, const void *data){

	BisTreeNode *pNode;
	if((pNode = (BisTreeNode *)malloc(sizeof(BisTreeNode))) == NULL){
		return -1;
	}
	pNode->left = NULL;
	pNode->right = NULL;
	pNode->count = 1;
	pNode->data = (void *)data;

	/* add root node */
	if(bst->root == NULL){
		bst->root = pNode;
		bst->size = 1;
		return 0;
	}

	BisTreeNode **ppNode = &(bst->root);
	while(1){
		int temp = bst->compare(data, (*ppNode)->data);
		if(temp < 0){
			if((*ppNode)->left == NULL){
				(*ppNode)->left = pNode;
				bst->size++;
				return 0;
			}
			ppNode = &((*ppNode)->left);
		}
		else if(temp > 0){
			if((*ppNode)->right == NULL){
				(*ppNode)->right = pNode;
				bst->size++;
				return 0;
			}
			ppNode = &((*ppNode)->right);
		}
		else{
			(*ppNode)->count++;
			free(pNode);
			return (*ppNode)->count;
		}
	}
}

int bistree_remove(BisTree *bst, const void *data){
	if(bst->root == NULL){
		return -1;
	}

	//BisTreeNode *pParentNode = NULL;
	BisTreeNode *pNode;
	BisTreeNode **ppNode = &(bst->root);
	while(1){
		int temp = bst->compare(data, (*ppNode)->data);
		if(temp < 0){
			if((*ppNode)->left == NULL){
				return -1;
			}
			//pParentNode = *ppNode;
			ppNode = &((*ppNode)->left);
		}
		else if(temp > 0){
			if((*ppNode)->right == NULL){
				return -1;
			}
			//pParentNode = *ppNode;
			ppNode = &((*ppNode)->right);
		}
		else{
			if((*ppNode)->count > 1){
				(*ppNode)->count--;
				return (*ppNode)->count;
			}
			else{
				/* count is 1, should remove node */
				if((*ppNode)->left == NULL && (*ppNode)->right == NULL){
					if(bst->destroy != NULL){
						bst->destroy((*ppNode)->data);
					}
					pNode = *ppNode;
					*ppNode = NULL;
					free(pNode);
					bst->size--;
					return 0;
				}
				else if((*ppNode)->left != NULL && (*ppNode)->right == NULL){
					if(bst->destroy != NULL){
						bst->destroy((*ppNode)->data);
					}
					pNode = *ppNode;
					*ppNode = (*ppNode)->left;
					free(pNode);
					bst->size--;
					return 0;
				}
				else if((*ppNode)->left == NULL && (*ppNode)->right != NULL){
					if(bst->destroy != NULL){
						bst->destroy((*ppNode)->data);
					}
					pNode = *ppNode;
					*ppNode = (*ppNode)->right;
					free(pNode);
					bst->size--;
					return 0;
				}
				else{
					pNode = (*ppNode)->left;
					BisTreeNode *parent = NULL;
					while(pNode->right != NULL){
						parent = pNode;
						pNode = pNode->right;
					}
					if(parent == NULL){
						(*ppNode)->left->right = (*ppNode)->right;
						pNode = *ppNode;
						*ppNode = (*ppNode)->left;
						return 0;
					}

					if(pNode->left != NULL){
						parent->right = pNode->left;
					}
					else{
						parent->right = NULL;
					}
					free(*ppNode);
					*ppNode = pNode;
					bst->size--;
					return 0;
				}
			}
		}
	}
	return -1;
}

int bistree_linearize(const BisTree *bst, List *lst){
	return bitree_inorder(bst->root, lst);
}