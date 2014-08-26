#include"stack.h"

int stack_push(Stack *stk, const void *data){
	return list_push(stk, data);
}

int stack_pop(Stack *stk, void **data){
	return list_pop(stk, data);
}