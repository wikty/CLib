#ifndef OHTABLE_H_
#define OHTABLE_H_

typedef struct OHTable_{
	/* hash table total length */
	unsigned int positions;
	/* hash table used length */
	unsigned int size;
	/* A address represent the position had a data 
	 * and removed already, so when search data just
	 * regard NULL or table run out as data isn't existed
	 */
	void *vacated;

	int (*hash1)(const void *data);
	int (*hash2)(const void *data);
	int (*match)(const void *key1, const void *key2);
	void (*destroy)(void *data);
	/* pointer to some void pointer */
	void **table;
}OHTable;

/*
 *  @param: 
 * 			positions is pow(2, p) and hash2 return a odd number
 *			or
 *			positions is a prime number and hash2 return a number 
 *			bewteen 0 and positions
 */
extern int ohtable_init(OHTable *ohtb,
						unsigned int positions,
						int (*hash1)(const void *data),
						int (*hash2)(const void *data),
						void (*destroy)(void *data),
						int (*match)(const void *key1, const void *key2));

extern void ohtable_destroy(OHTable *ohtb);

/*
 *  @return: 1 => existed
 *			 0 => success
 *			 -1 => table is filled, or hash function is not correctly
 */
extern int ohtable_insert(OHTable *ohtb, const void *data);

/*
 *  @return: -1 => data not in table
 *			 0 => success
 */
extern int ohtable_remove(OHTable *ohtb, const void *data);

/*
 *  @return: 0 => not in table
 *			 1 => in table
 */
extern int ohtable_has_data(OHTable *ohtb, const void *data);

extern void ohtable_dump(OHTable *ohtb, void (*print)(const void *data));

#define ohtable_len(ohtb) ((ohtb)->size)

#endif