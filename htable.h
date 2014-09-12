#ifndef HTABLE_H_
#define HTABLE_H_

#include "list.h"

typedef struct HTable_{
	/* hash table total buckets number */
	unsigned int buckets;
	/* hash table used buckets number */
	unsigned int size;
	List *table;
	int (*hash)(const void *key);
	void (*destroy)(void *data);
	int (*match)(const void *key1, const void *key2);
}HTable;

/*
 *  @param: hash => return a number(0 <= number && number <= buckets-1 )
 */
extern int htable_init(HTable *htb, 
					   unsigned int buckets,
					   int (*hash)(const void *key),
					   void (*destroy)(void *data),
					   int (*match)(const void *key1, const void *key2));

extern void htable_destroy(HTable *htb);

extern int htable_insert(HTable *htb, const void *data);

extern int htable_remove(HTable *htb, const void *data);

extern int htable_has_data(HTable *htb, const void *data);

extern void htable_dump(HTable *htb, void (*print)(const void *data));

#define htable_len(htb)	((htb)->size)

#endif