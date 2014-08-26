#include"queue.h"

int queue_enqueue(Queue *que, const void *data){
	return list_push(que, data);
}

int queue_dequeue(Queue *que, void **data){
	return list_shift(que, data);
}