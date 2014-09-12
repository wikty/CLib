#ifndef HEAP_H_
#define HEAP_H_
/*
 * implement as a max-heap(a left-balance bitree)
 */
typedef struct Heap_{
	/* heap current length */
	unsigned int length;
	/* point to a void pointer array */
	void **nodes;
	/* compare two data, return 1, 0, -1 */
	int (*compare)(const void *data1, const void *data2);
	void (*destroy)(void *data);
}Heap;

extern int heap_init(Heap* hp,
					 void (*destroy)(void *data),
					 int (*compare)(const void *data1, const void *data2));

extern void heap_destroy(Heap *hp);

/*
 *  @function: if you want insert n node into a new heap
 *			   use heap_insert n times => 0(nlgn)
 *			   use heap_quick_build => 0(n)
 *	@param: n should larger than 1
 *	@param: data is a pointer array
 *			   
 */
extern int heap_quick_build(Heap *hp, const void **data, unsigned int n);

extern int heap_quick_adjust(Heap *hp);

extern int heap_insert(Heap *hp, const void *data);

/*
 *  @function: remove heap top data
 */
extern int heap_shift(Heap *hp, void **data);

/*
 * @function: get heap peek, not remove
 */
extern int heap_peek(Heap *hp, void **data);

/*
extern void heap_linearize(const Heap *hp, List *lst);
extern void heap_dump(const Heap *hp, void (*print)(const void *data));
*/

#define heap_len(hp)	((hp)->length)
#define heap_is_empty(hp)	((hp)->length == 0 ? 1 : 0)

#endif