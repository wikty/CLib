#ifndef SET_H_
#define SET_H_

#include "list.h"

typedef List Set;

#define set_destroy	list_destroy	
#define set_len	list_len
#define set_dump list_dump

/*
 *	@param: match
 *			must specify a match function, because set operation
 *			depend on test member match
 *			if member match with another return 1, or return 0
 *	@param: destroy
 *			because element in multiple set, if destroy a element from one set
 *			another set will destroy the same element twice, so NOT RECOMMEND
 *			set destroy function for set
 *	@return: 0 => initialize succssfully
 *			-1 => initialize fail
 */
extern int set_init(Set *st, void (*destroy)(void *data), int (*match)(const void *data, const void *item));

/*
 *	@return: 1 => data is a member in st
 *			 0 => data is not in st
 */
extern int set_is_member(const Set *st, const void *data);

/*
 * @return: 0 => successfully
 *			1 => existed
 *			-1 => error occur
 */
extern int set_insert(Set *st, const void *data);

/*
 *	@return: 0 => success
 *			 -1 => failure
 *			 1 => data not in set
 */
extern int set_remove(Set *st, const void *data);

extern int set_union(Set *st, const Set *st1, const Set *st2);

extern int set_intersection(Set *st, const Set *st1, const Set *st2);

extern int set_difference(Set *st, const Set *st1, const Set *st2);

extern int set_is_equal(const Set *st1, const Set *st2);

extern int set_is_subset(const Set *st, const Set *st1);

extern int set_copy_to(const Set *st, Set *st1);

#endif