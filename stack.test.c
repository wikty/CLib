#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

typedef struct UserInfo_{
	int seq;
	char username[20];
}UserInfo;


int match(const void *data1, const void *data2){
	if(((UserInfo *)data1)->seq == ((UserInfo *)data2)->seq &&
		strcmp(((UserInfo *)data1)->username, ((UserInfo *)data2)->username) == 0){
		return 1;
	}
	return 0;
}

void destroy(void* data){
	free(data);
}

void print(const void *data){
	if(data == NULL){
		return;
	}
	puts(((UserInfo *)data)->username);
}
// int match_int(const void *data1, const void *data2){
// 	if(*((int *)data1) == *((int *)data2)){
// 		return 1;
// 	}
// 	return 0;
// }

int main(){
	Stack *stk;
	if((stk = (Stack *)malloc(sizeof(Stack))) == NULL){
		return -1;
	}
	stack_init(stk, destroy, match);

	UserInfo *u;

	puts("Push 0-item into Stack: ");
	if((u = (UserInfo *)malloc(sizeof(UserInfo))) == NULL){
		stack_destroy(stk);
		free(stk);
		return -1;
	}
	u->seq = 0;
	sprintf(u->username, "%d-item", u->seq);
	stack_push(stk, u);
	stack_dump(stk, print);
	puts("");

	puts("Push 1-item into Stack: ");
	if((u = (UserInfo *)malloc(sizeof(UserInfo))) == NULL){
		stack_destroy(stk);
		free(stk);
		return -1;
	}
	u->seq = 1;
	sprintf(u->username, "%d-item", u->seq);
	stack_push(stk, u);
	stack_dump(stk, print);
	puts("");

	puts("Get Stack's peek");
	u = stack_peek(stk);
	print(u);
	puts("");

	puts("Pop 1-item from Stack: ");
	stack_pop(stk, &u);
	free(u);
	stack_dump(stk, print);
	puts("");

	puts("Pop 0-item from Stack: ");
	stack_pop(stk, &u);
	free(u);
	stack_dump(stk, print);
	puts("");

	puts("Pop empty Stack: ");
	stack_pop(stk, &u);
	free(u);
	stack_dump(stk, print);
	puts("");

	puts("Push new item Stack: ");
	if((u = (UserInfo *)malloc(sizeof(UserInfo))) == NULL){
		stack_destroy(stk);
		free(stk);
		return -1;
	}
	u->seq = 0;
	sprintf(u->username, "%d-new-item", u->seq);
	stack_push(stk, u);
	stack_dump(stk, print);
	puts("");

	stack_destroy(stk);
	free(stk);
	return 0;
}