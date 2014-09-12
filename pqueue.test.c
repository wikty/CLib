#include <stdio.h>

#include "pqueue.h"

typedef struct UserInfo_{
	int seq;
	char username[20];
}UserInfo;

int compare(const void *data1, const void *data2){
	return strcmp(((UserInfo *)data1)->username, ((UserInfo *)data2)->username);
}

void destroy(void* data){
	free(data);
}

void print(const void *data){
	puts(((UserInfo *)data)->username);
}

UserInfo *u[10];
PriorityQueue* pq;

int setup(){
	if((pq = (PriorityQueue *)malloc(sizeof(PriorityQueue))) == NULL){
		return -1;
	}
	pqueue_init(pq, NULL, compare);

	for(int i=0; i<10; i++){
		if((u[i] = (UserInfo *)malloc(sizeof(UserInfo))) == NULL){
			free(pq);
			for(int j=i-1; j>=0; j--){
				free(u[j]);
				return -1;
			}
		}
		u[i]->seq = i;
		sprintf(u[i]->username, "%d-item", i);
	}
	return 0;
}

void enddown(){
	pqueue_destroy(pq);
	free(pq);
	pq = NULL;

	for(int i=0; i<10; i++){
		free(u[i]);
		u[i] = NULL;
	}
}

int main(){
	setup();

	puts("5-item enqueue");
	pqueue_enqueue(pq, u[5]);
	
	puts("");
	puts("PriorityQueue: ");
	for(int i=0; i<pqueue_len(pq); i++){
		print(pq->nodes[i]);
	}
	puts("");


	puts("9-item enqueue");
	pqueue_enqueue(pq, u[9]);

	puts("");
	puts("PriorityQueue: ");
	for(int i=0; i<pqueue_len(pq); i++){
		print(pq->nodes[i]);
	}
	puts("");

	puts("3-item enqueue");
	pqueue_enqueue(pq, u[3]);

	puts("");
	puts("PriorityQueue: ");
	for(int i=0; i<pqueue_len(pq); i++){
		print(pq->nodes[i]);
	}
	puts("");

	puts("0-item enqueue");
	pqueue_enqueue(pq, u[0]);

	puts("");
	puts("PriorityQueue: ");
	for(int i=0; i<pqueue_len(pq); i++){
		print(pq->nodes[i]);
	}
	puts("");

	puts("8-item enqueue");
	pqueue_enqueue(pq, u[8]);

	puts("");
	puts("PriorityQueue: ");
	for(int i=0; i<pqueue_len(pq); i++){
		print(pq->nodes[i]);
	}
	puts("");

	void *data = NULL;
	puts("dequeue");
	pqueue_dequeue(pq, &data);
	print(data);

	puts("");
	puts("PriorityQueue: ");
	for(int i=0; i<pqueue_len(pq); i++){
		print(pq->nodes[i]);
	}
	puts("");

	puts("dequeue");
	pqueue_dequeue(pq, &data);
	print(data);

	puts("");
	puts("PriorityQueue: ");
	for(int i=0; i<pqueue_len(pq); i++){
		print(pq->nodes[i]);
	}
	puts("");

	puts("6-item enqueue");
	pqueue_enqueue(pq, u[6]);

	puts("");
	puts("PriorityQueue: ");
	for(int i=0; i<pqueue_len(pq); i++){
		print(pq->nodes[i]);
	}
	puts("");

	enddown();
	return 0;
}