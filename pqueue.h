#ifndef PQUEUE_H_
#define PQUEUE_H_

#include "heap.h"

typedef Heap PriorityQueue;

#define pqueue_init	heap_init
#define pqueue_destroy heap_destroy
#define pqueue_enqueue	heap_insert
#define pqueue_dequeue	heap_shift
#define pqueue_peek	heap_peek
#define pqueue_len	heap_len
#define pqueue_is_empty	heap_is_empty

#endif