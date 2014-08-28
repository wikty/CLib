#ifndef SET_H_
#define SET_H_

#include "list.h"

typedef List Set;

#define set_init	list_init
#define set_destroy	list_destroy	
#define set_len	list_len

extern int set_is_member(const Set *st, const void *data);

/*
 * @return: 0 => successfully
 *			1 => existed
 *			-1 => error occur
 */
extern int set_insert(Set *st, const void *data);
extern int set_remove(Set *st, const void *data);
extern int set_union(Set *st, const Set *st1, const Set *st2);
extern int set_intersection(Set *st, const Set *st1, const Set *st2);
extern int set_difference(Set *st, const Set *st1, const Set *st2);
extern int set_is_equal(const Set *st1, const Set *st2);
extern int set_is_subset(const Set *st, const Set *st1);


/*
typedef struct KSet_ {
	void *key;
	Set *set;
}KSet;
*/

#endif