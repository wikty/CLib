#include <stdlib.>

#include "heap.h"

/*
 * Internal marco, User don't be allowed to access heap's node
 */
#define heap_parent_index(index)	((int)(((index)-1)/2))
#define heap_left_index(index)	((index)*2+1)
#define heap_right_index(index)	((index)*2+2)

/*
 * Internal functions, User don't be allowed to access heap's node
 */
static int heap_has_left(Heap *hp, unsigned int index);
static int heap_has_right(Heap *hp, unsigned int index);
static int heap_is_leaf(Heap *hp, unsigned int index);


int heap_init(Heap *hp,
			  void (*destroy)(void *data), 
			  int (*compare)(const void *data1, const void *data2)){
	if(compare == NULL){
		return -1;
	}
	
	hp->nodes = NULL;
	hp->length = 0;
	hp->destroy = destroy;
	hp->compare = compare;
	return 0;
}

void heap_destroy(Heap *hp){
	if(hp->destroy != NULL){
		for(int i=0; i<heap_len(hp); i++){
			hp->destroy(hp->nodes[i]);
		}
	}
	free(hp->nodes);

	memset(hp, 0, sizeof(*hp));
}

/*
 *  @function: from bottom to top build heap with
 */
int heap_quick_build(Heap *hp, const void **data, unsigned int n){
	if(heap_is_empty(hp) && n > 1){
		if((hp->nodes = (void **)malloc(n * sizeof(void *))) == NULL){
			return -1;
		}
		for(int i=0; i<n; i++){
			hp->nodes[i] = (void *)data[i];
		}
		hp->length = n;

		/* ajust from sub-tree (int)((n-2)/2) */
		int index = (int)((n-2)/2);
		void *temp = NULL;
		while(index >= 0){
			int lindex = heap_left_index(index);
			int rindex = heap_right_index(index);
			if(lindex < heap_len(hp)){
				/* has left child */
				if(hp->compare(hp->nodes[index], hp->nodes[lindex]) < 0){
					temp = hp->nodes[index];
					hp->nodes[index] = hp->nodes[lindex];
					hp->nodes[lindex] = temp;
				}
			}
			if(heap_right_index(index) < heap_len(hp)){
				/* has right child */
				if(hp->compare(hp->nodes[index], hp->nodes[rindex]) < 0){
					temp = hp->nodes[index];
					hp->nodes[index] = hp->nodes[rindex];
					hp->nodes[rindex] = temp;
				}
			}
			index--;
		}
		return 0;
	}
	return -1;
}

/*
 * this is a max-heap
 */
int heap_insert(Heap *hp, const void *data){
	
	if(hp->nodes == NULL){
		/* heap's first node */
		if(hp->nodes = (void **)malloc(sizeof(void *)) == NULL){
			return -1;
		}
		hp->nodes[0] = data;
		hp->length = 1;
		return 0;
	}

	
	/* resize heap */
	if((hp->nodes = (void **)realloc(hp->nodes, sizeof(void *) * (heap_len(hp)+1)) == NULL){
		return -1;
	}
	hp->length++;
	/* adjust heap */
	int index = head_len(hp) - 1;
	hp->nodes[index] = data;
	while(index > 0){
		void **current = &(hp->nodes[index]);
		void **parent = &(hp->nodes[heap_parent_index(index)]);
		switch(hp->compare(*current, *parent)){
			case 1:
				*current = *parent;
				*parent = data;
				break;
			case 0:
			case -1:
				return 0;
		}
		index = heap_parent_index(index);
	}
	return 0;
}

int heap_shift(Heap *hp, void **data){
	/* can't shift a empty heap */
	if(heap_is_empty(hp)){
		return -1;
	}
	/* heap just has one node */
	if(heap_len(hp) == 1){
		*data = hp->nodes[0];
		hp->length = 0;
		free(hp->nodes);
		hp->nodes = NULL;
		return 0;
	}


	/* resize heap */
	void *temp = hp->nodes[heap_len(hp)-1];
	if((hp->nodes = (void **)realloc(hp->nodes, sizeof(void *) * (heap_len(hp)-1)) == NULL){
		return -1;
	}
	hp->length--;
	/* store the heap peek node */
	*data = hp->nodes[0];
	/* adjust heap */
	hp->nodes[0] = temp;
	int index = 0;
	void *p = NULL;
	void **current = (void **)&p;
	void **left = (void **)&p;
	void **right = (void **)&p;
	while(1){
		*current = hp->nodes[index];
		*left = (heap_left_index(index) < heap_len(hp) ? hp->nodes[heap_left_index(index)] : NULL);
		*right = (heap_right_index(index) < heap_len(hp) ? hp->nodes[heap_right_index(index)] : NULL);
		if(*left != NULL && *right != NULL){
			/* have both left and right child */
			switch(hp->compare(*left, *right)){
				case 0:
				case 1:
					if(hp->compare(*left, *current) == 1){
						*current = *left;
						*left = temp;
						index = heap_left_index(index);
					}
					else{
						return 0;
					}
					break;
				case -1:
					if(hp->compare(*right, *current) == 1){
						*current = *right;
						*right = temp;
						index = heap_right_index(index);
					}
					else{
						return 0;
					}
					break;
			}
		}
		else if(*left != NULL){
			/* only have left child */
			if(hp->compare(*left, *current) == 1){
				*current = *left;
				*left = temp;
			}
			return 0;
		}
		else{
			/* 
				have no child, if a node don't have left child
				meaning than it don't have right child too, it
				is a leaf node
			*/
			return 0;
		}
	}
}

int heap_peek(Heap *hp, void **data){
	if(heap_is_empty(hp)){
		*data = NULL;
		return -1;
	}
	*data = hp->nodes[0];
	return 0;
}


/*
 * Internal function
 */
int heap_has_left(Heap *hp, unsigned int index){
	return (heap_left_index(index) < heap_len(hp) ? 1 : 0);
}

int heap_has_right(Heap *hp, unsigned int index){
	return (heap_right_index(index) < heap_len(hp) ? 1 : 0);
}

int heap_is_leaf(Heap *hp, unsigned int index){
	return (heap_left_index(index) >= heap_len(hp) ? 1 : 0);
}