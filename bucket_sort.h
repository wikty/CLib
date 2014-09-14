#ifndef BUCKET_SORT_H_
#define BUCKET_SORT_H_

/*
 *		Name:				Bucket Sort
 *		Stability:			true
 *		Comparision:		false
 *		Time-Performance:	O(n)
 *		Space-Performance:	O(k)
 *		In-Position:		false
 *		
 */

#include "list.h"

typedef struct Bucket_{
	List **buckets;
	int size;

	void (*destroy)(void *data);
	int (*compare)(const void *data1, const void *data2);
	int (*hash)(const void *data);
}Bucket;

extern int bucket_init(Bucket *buk,
						void (*destroy)(void *data),
						int (*compare)(const void *data1, const void *data2),
						int (*hash)(const void *key),
						unsigned int size);

extern void bucket_destroy(Bucket *buk);

extern int bucket_insert(Bucket *buk, const void *data);

/*
 *	@param: lst
 *		User should initialize it to hold sorted data
 */
extern int bucket_sort(Bucket *buk, List *lst);

#endif