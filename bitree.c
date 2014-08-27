#include "bitree.h"

void bitree_init(BiTree *bt, 
				void (*destroy)(void *data),
				int (*compare)(const void *data1, const void *data2)){
	bt->root = NULL;
	bt->size = 0;
	bt->destroy = destroy;
	bt->compare = compare;
}


void bitree_destroy(BiTree *bt){
	/* remove the whole of tree */
	bitree_remove_left(bt, NULL);

	memset(bt, 0, sizeof(*bt));
}

int bitree_add_left(BiTree *bt, BiTreeNode *pNode, const void *data){
	BiTreeNode *pNewNode, **ppNode;
	if(pNode == NULL){
		if(!bitree_is_empty(bt)){
			return -1;
		}
		/* add root node */
		ppNode = (BiTreeNode **)&(bt->root);
	}
	else{
		if(pNode->left != NULL){
			return -1;
		}
		ppNode = (BiTreeNode **)&(pNode->left);
	}

	if((pNewNode = (BiTreeNode *)malloc(sizeof(BiTreeNode))) == NULL){
		return -1;
	}
	pNewNode->data = data;
	pNewNode->left = NULL;
	pNewNode->right = NULL;

	*ppNode = pNewNode;

	bt->size++;

	return 0;
}

int bitree_add_right(BiTree *bt, BiTreeNode *pNode, const void *data){
	BiTreeNode *pNewNode, **ppNode;
	if(pNode == NULL){
		if(!bitree_is_empty(bt)){
			return -1;
		}
		/* add root node */
		ppNode = (BiTreeNode **)&(bt->root);
	}
	else{
		if(pNode->right != NULL){
			return -1;
		}
		ppNode = (BiTreeNode **)&(pNode->right);
	}

	if((pNewNode = (BiTreeNode *)malloc(sizeof(BiTreeNode))) == NULL){
		return -1;
	}
	pNewNode->data = data;
	pNewNode->left = NULL;
	pNewNode->right = NULL;

	*ppNode = pNewNode;

	bt->size++;

	return 0;
}

int bitree_remove_left(BiTree *bt, BiTreeNode *pNode){
	if(bitree_is_empty(bt)){
		return -1;
	}
	BiTreeNode **ppNode;
	if(pNode == NULL){
		/* remove the whole of tree */
		ppNode = (BiTreeNode **)&(bt->root);
	}
	else{
		/* remove pNode->left */
		if(pNode->left == NULL){
			/* left don't exist */
			return 0;
		}
		ppNode = (BiTreeNode **)&(pNode->left);
	}

	if(bitree_remove_left(bt, *ppNode) != 0){
		return -1;
	}
	if(bitree_remove_right(bt, *ppNode) != 0){
		return -1;
	}

	if(bt->destroy != NULL){
		bt->destroy((*ppNode)->date);
	}

	free(*ppNode);
	*ppNode = NULL;

	bt->size--;
	return 0;
}

int bitree_remove_right(BiTree *bt, BiTreeNode *pNode){
	if(bitree_is_empty(bt)){
		return -1;
	}
	BiTreeNode **ppNode;
	if(pNode == NULL){
		/* remove the whole of tree */
		ppNode = (BiTreeNode **)&(bt->root);
	}
	else{
		/* remove pNode->left */
		if(pNode->right == NULL){
			/* right don't exist */
			return 0;
		}
		ppNode = (BiTreeNode **)&(pNode->right);
	}

	if(bitree_remove_left(bt, *ppNode) != 0){
		return -1;
	}
	if(bitree_remove_right(bt, *ppNode) != 0){
		return -1;
	}

	if(bt->destroy != NULL){
		bt->destroy((*ppNode)->date);
	}

	free(*ppNode);
	*ppNode = NULL;

	bt->size--;
	return 0;
}

int bitree_merge(BiTree *bt, BiTree *left, BiTree *right, const void *data){
	if(left == NULL || right == NULL){
		return -1;
	}
	bitree_init(bt, left->destroy, left->compare);
	/* add root node */
	if(bitree_add_left(bt, NULL, data) != 0){
		bitree_destroy(bt);
		return -1;
	}
	bt->root->left = left->root;
	bt->root->right = right->root;

	left->root = NULL;
	left->size = 0;
	left->destroy = NULL;
	left->compare = NULL;
	right->root = NULL;
	right->size = 0;
	right->destroy = NULL;
	right->compare = NULL;


	bt->size = bt->size + left->size + right->size;
	return 0;
}

int bitree_preorder(const BiTreeNode *pNode, List *lst){
	if(lst == NULL){
		return -1;
	}
	if(pNode == NULL){
		return 0;
	}
	if(list_push(lst, bitree_get_data(pNode)) != 0){
		return -1;
	}
	if(pNode->left != NULL){
		if(bitree_preorder(pNode->left, lst) != 0){
			return -1;
		}
	}
	if(pNode->right != NULL){
		if(bitree_preorder(pNode->right, lst) != 0){
			return -1;
		}
	}
	return 0;
}

int bitree_inorder(const BiTreeNode *pNode, List *lst){
	if(lst == NULL){
		return -1;
	}
	if(pNode == NULL){
		return 0;
	}
	if(pNode->left != NULL){
		if(bitree_inorder(pNode->left, lst) != 0){
			return -1;
		}
	}
	if(list_push(lst, bitree_get_data(pNode)) != 0){
		return -1;
	}
	if(pNode->right != NULL){
		if(bitree_inorder(pNode->right, lst) != 0){

		}
	}
	return 0;
}

int bitree_postorder(const BiTreeNode *pNode, List *lst){
	if(lst == NULL){
		return -1;
	}
	if(pNode == NULL){
		return 0;
	}
	if(pNode->left != NULL){
		if(bitree_postorder(pNode->left, lst) != 0){
			return -1;
		}
	}
	if(pNode->right != NULL){
		if(bitree_postorder(pNode->right, lst) != ){
			return -1;
		}
	}
	if(list_push(lst, bitree_get_data(pNode)) != 0){
		return -1;
	}
	return 0;
}
/*
int bitree_search(BiTree *bt, const void *data, BiTreeNode** ppNode){
	if(bitree_is_empty(bt)){
		*ppNode = NULL;
		return 0;
	}
	List *lst;
	if((lst = (List *)malloc(sizeof(List))) == NULL){
		return -1;
	}
	list_init(lst, NULL, bt->compare);
	bitree_preorder(bt->root, lst);
	list_search()

	free(lst);
	return 0;
}
*/