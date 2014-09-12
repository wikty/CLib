#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

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
	Queue *que;
	if(( que = (Queue *)malloc(sizeof(Queue))) == NULL){
		return -1;
	}
	queue_init(que, destroy, match);

	UserInfo *u;

	puts("Enqueue 0-item");
	if((u = (UserInfo *)malloc(sizeof(UserInfo))) == NULL){
		queue_destroy(que);
		free(que);
		return -1;
	}
	u->seq = 0;
	sprintf(u->username, "%d-item", u->seq);
	queue_enqueue(que, u);
	queue_dump(que, print);
	puts("");

	puts("Enqueue 1-item");
	if((u = (UserInfo *)malloc(sizeof(UserInfo))) == NULL){
		queue_destroy(que);
		free(que);
		return -1;
	}
	u->seq = 1;
	sprintf(u->username, "%d-item", u->seq);
	queue_enqueue(que, u);
	queue_dump(que, print);
	puts("");

	puts("Dequeue 0-item");
	queue_dequeue(que, &u);
	free(u);
	queue_dump(que, print);
	puts("");

	puts("Enqueue 2-item");
	if((u = (UserInfo *)malloc(sizeof(UserInfo))) == NULL){
		queue_destroy(que);
		free(que);
		return -1;
	}
	u->seq = 2;
	sprintf(u->username, "%d-item", u->seq);
	queue_enqueue(que, u);
	queue_dump(que, print);
	puts("");

	queue_destroy(que);
	free(que);
	return 0;
}