#ifndef STACK_H_
#define STACK_H_

#include "list.h"

typedef List Stack;

#define stack_init	list_init
#define stack_destroy list_destroy
#define stack_len	list_len
#define stack_peek(stk)	((stk)->tail == NULL ? NULL : (stk)->tail->data)

extern int stack_push(Stack *stk, const void *data);
extern int stack_pop(Stack *stk, void **data);