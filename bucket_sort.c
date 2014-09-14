#include <stdlib.h>

#include "list.h"
#include "bucket.h"

static void merge(List *lst, List *lst1, int (*compare)(const void *data1, const void *data2));

int bucket_init(Bucket *buk,
				void (*destroy)(void *data),
				int (*compare)(const void *data1, const void *data2),
				int (*hash)(const void *key),
				unsigned int size){
	if(buk == NULL || compare == NULL || hash == NULL || size < 1 ){
		return -1;
	}
	if((buk->buckets = (List **)malloc(sizeof(List *) * size)) == NULL){
		return -1;
	}
	for(int i=0; i<size; i++){
		buk->buckets[i] = NULL;
	}


	buk->destroy = destroy;
	buk->compare = compare;
	buk->hash = hash;
	buk->size = size;
}

void bucket_destroy(Bucket *buk){
	for(int i=0; i<buk->size; i++){
		if(buk->buckets[i] != NULL){



			/* free the list */
			free(buk->buckets[i]);
		}
	}

	memset(buk, 0, sizeof(*buk));
}

int bucket_insert(Bucket *buk, const void *data){
	if(buk == NULL || data == NULL){
		return -1;
	}

	int index = buk->hash(data) % buk->size;
	if(buk->buckets[index] == NULL){
		if((buk->buckets[index] = (List *)malloc(sizeof(List))) == NULL){
			return -1;
		}
	}

	Node *pNode = list_head(buk->buckets[index]);
	if(pNode == NULL){
		list_push(buk->buckets[index], data);
	}
	else{
		while(pNode){
			if(buk->compare(data, list_node_data(pNode)) < 0){
				list_insert(buk->buckets[index], pNode, data);
				return 0;
			}
			pNode = list_node_next(pNode);
		}
		list_push(buk->buckets[index], data);
	}
	return 0;
}

int bucket_sort(Bucket *buk, List *lst){
	if(buk == NULL || lst == NULL){
		return -1;
	}

	for(int i=0; i<buk->size; i++){
		if(buk->buckets[i] != NULL){
			merge(lst, buk->buckets[i], buk->compare);
		}
	}
	return 0;
}


/*
 *	Internal Functions
 */

void merge(List *lst, List *lst1, int (*compare)(const void *data1, const void *data2)){
	Node *pNode=NULL, *pNode1=NULL;

	pNode = list_head(lst);
	pNode1 = list_head(lst1);
	List temp;
	while(pNode != NULL && pNode1 != NULL)	{
		int cmpval = compare(list_node_data(pNode), list_node_data(pNode1));
		if(cmpval < 0){
			list_push(&temp, list_node_data(pNode));
			pNode = list_node_next(pNode);
		}
		else{
			list_push(&temp, list_node_data(pNode1));
			pNode1 = list_node_next(pNode1);
		}
	}

	if(pNode != NULL){
		while(pNode){
			list_push(&temp, list_node_data(pNode));
			pNode = list_node_next(pNode);
		}
	}
	if(pNode1 != NULL){
		while(pNode1){
			list_push(&temp, list_node_data(pNode1));
			pNode1 = list_node_next(pNode1);
		}
	}

	void *data = NULL;
	while(list_pop(lst, &data) == 0){
		/* nothing */
	}

	pNode = list_head(&temp);
	while(pNode){
		list_push(lst, list_node_data(pNode));
		pNode = list_node_next(pNode);
	}
	return 0;
}