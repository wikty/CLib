#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "bitree.h"

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

UserInfo *u[10];
BiTree *bt, *bt1, *bt2;

int setup(){
	if((bt = (BiTree *)malloc(sizeof(BiTree))) == NULL){
		return -1;
	}
	if((bt1 = (BiTree *)malloc(sizeof(BiTree))) == NULL){
		free(bt);
		return -1;
	}
	if((bt2 = (BiTree *)malloc(sizeof(BiTree))) == NULL){
		free(bt);
		free(bt1);
		return -1;
	}
	bitree_init(bt, destroy, compare);
	bitree_init(bt1, destroy, compare);
	bitree_init(bt2, destroy, compare);

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
	bitree_destroy(bt);
	bitree_destroy(bt1);
	bitree_destroy(bt2);
	free(bt);
	free(bt1);
	free(bt2);

	for(int i=0; i<10; i++){
		free(u[i]);
	}
}

int main(){
	setup();

	puts("Add 0-item as BT1's root, BT1: ");
	bitree_add_left(bt1, NULL, u[0]);
	bitree_dump(bt1, print);
	puts("");

	puts("Add 1-item as BT2's root, BT2: ");
	bitree_add_left(bt2, NULL, u[1]);
	bitree_dump(bt2, print);
	puts("");

	puts("Add 2-item as BT1's root's left child ");
	bitree_add_left(bt1, bitree_root(bt1), u[2]);
	puts("Add 3-item as BT1's root's right child ");
	bitree_add_right(bt1, bitree_root(bt1), u[3]);
	puts("BT1: ");
	bitree_dump(bt1, print);
	puts("");

	puts("Add 4-item as BT2's root's left child ");
	bitree_add_left(bt2, bitree_root(bt2), u[4]);
	puts("Add 5-item as BT2's root's right child ");
	bitree_add_right(bt2, bitree_root(bt2), u[5]);
	puts("BT2: ");
	bitree_dump(bt2, print);
	puts("");

	printf("BT1 len: %d\n", bitree_size(bt1));
	printf("BT2 len: %d\n", bitree_size(bt2));
	printf("BT len: %d\n", bitree_size(bt));
	puts("Merge BT1 and BT2 to BT: ");
	bitree_merge(bt, bt1, bt2, u[6]);
	bitree_dump(bt, print);
	puts("");

	printf("BT len: %d\n", bitree_size(bt));
	puts("BT remove left child,  BT: ");
	bitree_remove_left(bt, bitree_root(bt));
	bitree_dump(bt, print);
	puts("");

	enddown();
	return 0;
}