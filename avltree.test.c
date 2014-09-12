#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "avltree.h"

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
AvlTree *alt;

int setup(){
	if((alt = (AvlTree *)malloc(sizeof(AvlTree))) == NULL){
		return -1;
	}
	avltree_init(alt, destroy, compare);

	for(int i=0; i<10; i++){
		if((u[i] = (UserInfo *)malloc(sizeof(UserInfo))) == NULL){
			free(alt);
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
	avltree_destroy(alt);
	free(alt);

	for(int i=0; i<10; i++){
		free(u[i]);
	}
}

int main(){
	setup();

	puts("Add 5-item");
	avltree_insert(alt, u[5]);
	
	puts("Add 3-item");
	avltree_insert(alt, u[3]);
	puts("Add 4-item");
	avltree_insert(alt, u[4]);
	puts("Add 2-item");
	avltree_insert(alt, u[2]);
	puts("Add 0-item");
	avltree_insert(alt, u[0]);
	puts("Add 1-item");
	avltree_insert(alt, u[1]);

	puts("Add 8-item");
	avltree_insert(alt, u[8]);
	puts("Add 6-item");
	avltree_insert(alt, u[6]);
	puts("Add 9-item");
	avltree_insert(alt, u[9]);
	
	

	puts("AvlTree root node: ");
	print(avltree_root_data(alt));
	puts("AvlTree: ");
	avltree_dump(alt, print);
	puts("");

	List lst;
	list_init(&lst, NULL, NULL);

	puts("Linearize AvlTree: ");
	avltree_linearize(alt, &lst);
	list_dump(&lst, print);
	puts("");

	list_destroy(&lst);

	puts("Remove 2-item from AvlTree: ");
	avltree_remove(alt, u[2]);
	avltree_dump(alt, print);
	puts("");

	enddown();
	return 0;
}