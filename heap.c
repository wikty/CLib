#include <stdlib.h>

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
static int heap_insert_adjust(Heap *hp);
/*
 *	@param: tail
 *			heap's last item
 */
static int heap_shift_adjust(Heap *hp);
/*
 *	@param: direction
 *			1 => from index to bottom
 *			-1 => from index to top
 */
static int heap_index_adjust(Heap *hp, int index, int direction);


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

int heap_quick_adjust(Heap *hp){
	if(heap_is_empty(hp)){
		return -1;
	}
	int n = heap_len(hp);

	int index = (int)((n-2)/2);
	void *temp = NULL;
	while(index >= 0){
		heap_index_adjust(hp, index, 1);
		index--;
	}
	return 0;
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

		/* ajust from sub-tree (int)((n-2)/2) ~ 0 */
		return heap_quick_adjust(hp);
	}
	return -1;
}

/*
 * this is a max-heap
 */
int heap_insert(Heap *hp, const void *data){
	
	if(hp->nodes == NULL){
		/* heap's first node */
		if((hp->nodes = (void **)malloc(sizeof(void *))) == NULL){
			return -1;
		}
		hp->nodes[0] = (void *)data;
		hp->length = 1;
		return 0;
	}

	
	/* resize heap */
	if((hp->nodes = (void **)realloc(hp->nodes, sizeof(void *) * (heap_len(hp)+1))) == NULL){
		return -1;
	}
	hp->length++;
	hp->nodes[heap_len(hp)-1] = (void *)data;
	/* adjust heap */
	return heap_insert_adjust(hp);
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
	if((hp->nodes = (void **)realloc(hp->nodes, sizeof(void *) * (heap_len(hp)-1))) == NULL){
		return -1;
	}
	hp->length--;
	/* store the heap peek node */
	*data = hp->nodes[0];
	hp->nodes[0] = (void *)temp;

	/* adjust heap */
	return heap_shift_adjust(hp);
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

int heap_insert_adjust(Heap *hp){
	if(heap_is_empty(hp)){
		return -1;
	}
	return heap_index_adjust(hp, heap_len(hp)-1, -1);
}

int heap_shift_adjust(Heap *hp){
	if(heap_is_empty(hp)){
		return -1;
	}
	return heap_index_adjust(hp, 0, 1);
}

int heap_index_adjust(Heap *hp, int index, int direction){
	if(heap_is_empty(hp)){
		return -1;
	}
	int n = heap_len(hp);
	if(index < 0 || index >= n || direction == 0){
		return -1;
	}

	void *temp = hp->nodes[index];
	if(direction > 0){
		/* from index to bottom */
		while(index < n){
			void **current=NULL, **left=NULL, **right=NULL;
			current = &(hp->nodes[index]);
			if(heap_left_index(index) < heap_len(hp)){
				left = &(hp->nodes[heap_left_index(index)]);
			}
			
			if(heap_right_index(index) < heap_len(hp)){
				right = &(hp->nodes[heap_right_index(index)]);
			}
			

			if(left != NULL && right != NULL){
				/* have both left and right child */
				int cmpval = hp->compare(*left, *right);
				if(cmpval < 0){
					if(hp->compare(*right, *current) > 0){
						*current = *right;
						*right = temp;
						index = heap_right_index(index);
					}
					else{
						break;
					}
				}
				else{
					/* left >= right */
					if(hp->compare(*left, *current) > 0){
						*current = *left;
						*left = temp;
						index = heap_left_index(index);
					}
					else{
						break;
					}
				}
			}
			else if(left != NULL){
				/* only have left child */
				/*  if a node don't have left child meaning that
					it don't have right child too, it is a leaf node
				*/
				if(hp->compare(*left, *current) > 0){
					*current = *left;
					*left = temp;
				}
				/* because heap is a balanced tree, so if there is no
				   right node, meaning left have no child
				*/
				break;
			}
			else{
				/* 
					have no child
				*/
				break;
			}
		}
		return 0;
	}
	else{
		/* from index to top */
		while(index > 0){
			void **current = &(hp->nodes[index]);
			void **parent = &(hp->nodes[heap_parent_index(index)]);
			if(hp->compare(*current, *parent) > 0){
				*current = *parent;
				*parent = temp;
			}
			else{
				break;
			}
			index = heap_parent_index(index);
		}
		/* new node is top node */
		return 0;
	}

}

/*
void heap_linearize(const Heap *hp, List *lst){

}

void heap_dump(const Heap *hp, void (*print)(const void *data)){

}
*/