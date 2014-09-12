#ifndef QUEUQ_H_
#define QUEUE_H_

#include "list.h"

typedef List Queue;
#define queue_init	list_init
#define queue_destroy	list_destroy
#define queue_len	list_len
#define queue_head	list_head
#define queue_tail	list_tail
#define queue_dump	list_dump

extern int queue_enqueue(Queue *que, const void *data);
extern int queue_dequeue(Queue *que, void **data);

#endif