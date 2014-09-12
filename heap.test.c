#include <stdio.h>

#include "heap.h"

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
Heap *hp;

int setup(){
	if((hp = (Heap *)malloc(sizeof(Heap))) == NULL){
		return -1;
	}
	heap_init(hp, destroy, compare);

	for(int i=0; i<10; i++){
		if((u[i] = (UserInfo *)malloc(sizeof(UserInfo))) == NULL){
			free(hp);
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
	heap_destroy(hp);
	free(hp);
	hp = NULL;

	/* heap will remove data */
	// for(int i=0; i<10; i++){
	// 	free(u[i]);
	// 	u[i] = NULL;
	// }
}

int main(){
	setup();

	for(int i=0; i<10; i++){
		heap_insert(hp, u[i]);
	}

	//heap_quick_build(hp, (const void **)u, 10);

	puts("Heap: ");
	for(int i=0; i<heap_len(hp); i++){
		print(hp->nodes[i]);
	}
	puts("");


	puts("Heap PeeK: ");
	void *data = NULL;
	heap_peek(hp, &data);
	print(data);
	puts("");

	puts("Remove 9-item");
	heap_shift(hp, &data);
	print(data);
	free(data);
	puts("");

	puts("Heap: ");
	for(int i=0; i<heap_len(hp); i++){
		print(hp->nodes[i]);
	}
	puts("");
	
	puts("Heap Peek: ");
	heap_peek(hp, &data);
	print(data);
	puts("");

	puts("Heap: ");
	for(int i=0; i<heap_len(hp); i++){
		print(hp->nodes[i]);
	}
	puts("");

	enddown();
	return 0;
}