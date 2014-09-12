#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "bistree.h"

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

void* print(const void *data){
	puts(((UserInfo *)data)->username);
	return NULL;
}

void l_print(const void *data){
	puts(((UserInfo *)data)->username);
}

UserInfo *u[10];
BisTree *bt, *bt1, *bt2;

int setup(){
	if((bt = (BisTree *)malloc(sizeof(BisTree))) == NULL){
		return -1;
	}
	if((bt1 = (BisTree *)malloc(sizeof(BisTree))) == NULL){
		free(bt);
		return -1;
	}
	if((bt2 = (BisTree *)malloc(sizeof(BisTree))) == NULL){
		free(bt);
		free(bt1);
		return -1;
	}
	bistree_init(bt, destroy, compare);
	bistree_init(bt1, destroy, compare);
	bistree_init(bt2, destroy, compare);

	for(int i=0; i<10; i++){
		if((u[i] = (UserInfo *)malloc(sizeof(UserInfo))) == NULL){
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
	bistree_destroy(bt);
	bistree_destroy(bt1);
	bistree_destroy(bt2);
	free(bt);
	free(bt1);
	free(bt2);

	for(int i=0; i<10; i++){
		free(u[i]);
	}
}

int main(){
	setup();

	puts("Add 5-item");
	bistree_insert(bt1, u[5]);
	
	puts("Add 3-item");
	bistree_insert(bt1, u[3]);
	puts("Add 4-item");
	bistree_insert(bt1, u[4]);
	puts("Add 2-item");
	bistree_insert(bt1, u[2]);
	puts("Add 0-item");
	bistree_insert(bt1, u[0]);
	puts("Add 1-item");
	bistree_insert(bt1, u[1]);

	puts("Add 8-item");
	bistree_insert(bt1, u[8]);
	puts("Add 6-item");
	bistree_insert(bt1, u[6]);
	puts("Add 9-item");
	bistree_insert(bt1, u[9]);
	
	

	puts("BST1 root node: ");
	print(bistree_root(bt1)->data);
	puts("BST1: ");
	bistree_dump(bt1, print);
	puts("");

	// puts("Add 4-item as BST2's root's left child ");
	// bistree_insert(bt2, u[4]);
	// puts("Add 5-item as BST2's root's right child ");
	// bistree_insert(bt2, u[5]);
	// puts("BST2 root node: ");
	// print(bistree_root(bt2)->data);
	// puts("BST2: ");
	// bistree_dump(bt2, print);
	// puts("");

	// printf("BT1 len: %d\n", bitree_size(bt1));
	// printf("BT2 len: %d\n", bitree_size(bt2));
	// printf("BT len: %d\n", bitree_size(bt));
	// puts("Merge BT1 and BT2 to BT: ");
	// bitree_merge(bt, bt1, bt2, u[6]);
	// bitree_dump(bt, print);
	// puts("");

	// printf("BST1 len: %d\n", bistree_size(bt1));
	// printf("BST1 len: %d\n", bistree_size(bt2));

	List lst;
	list_init(&lst, NULL, NULL);

	puts("Linearize BST1: ");
	bistree_linearize(bt1, &lst);
	list_dump(&lst, l_print);
	puts("");

	list_destroy(&lst);

	puts("Remove 2-item from BST1: ");
	bistree_remove(bt1, u[2]);
	bistree_dump(bt1, print);
	puts("");

	enddown();
	return 0;
}