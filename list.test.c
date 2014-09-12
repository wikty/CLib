#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

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
	puts(((UserInfo *)data)->username);
}
// int match_int(const void *data1, const void *data2){
// 	if(*((int *)data1) == *((int *)data2)){
// 		return 1;
// 	}
// 	return 0;
// }

int main(){
	List *lst;
	if((lst = (List *)malloc(sizeof(List))) == NULL){
		return -1;
	}
	list_init(lst, destroy, match);

	/* User manage data */
	UserInfo *u[5];
	for(int i=0; i<5; i++){
		if((u[i] = (UserInfo *)malloc(sizeof(UserInfo))) == NULL){
			for(int j=i-1; j>=0; j--){
				free(u[j]);
			}
			free(lst);
			return -1;
		}
		u[i]->seq = 20*i;
		sprintf(u[i]->username, "xiao-%d", i);
		list_push(lst, u[i]);
	}

	puts("init list");
	list_dump(lst, print);
	puts("");

	UserInfo *p;

	puts("pop last item");
	list_pop(lst, &p);
	/* must free the removed node's data, because list_destroy just
	 * destroy the node's data still in list
	 */
	free(p);
	list_dump(lst, print);
	puts("");

	puts("shift first item");
	list_shift(lst, &p);
	free(p);
	list_dump(lst, print);
	puts("");

	if((p = (UserInfo *)malloc(sizeof(UserInfo))) == NULL){
		list_destroy(lst);
		free(lst);
		return -1;
	}
	p->seq = -1;
	strcpy(p->username, "xiao-new-node");
	puts("unshift new item");
	list_unshift(lst, p);
	list_dump(lst, print);
	puts("");

	puts("remove new item");
	Node *pNode = list_search(lst, p);
	list_remove(lst, pNode, &p);
	free(p);
	list_dump(lst, print);
	puts("");

	puts("remove 1 position item");
	pNode = list_get(lst, 1);
	list_remove(lst, pNode, &p);
	free(p);
	list_dump(lst, print);
	puts("");

	puts("remove 0's next node");
	pNode = list_get(lst, 0);
	list_remove_next(lst, pNode, &p);
	free(p);
	list_dump(lst, print);
	puts("");

	if((p = (UserInfo *)malloc(sizeof(UserInfo))) == NULL){
		list_destroy(lst);
		free(lst);
		return -1;
	}
	p->seq = -1;
	strcpy(p->username, "xiao-new-node");
	puts("append new after 0 node");
	pNode = list_get(lst, 0);
	list_append(lst, pNode, p);
	list_dump(lst, print);
	puts("");

	list_destroy(lst);
	free(lst);
	return 0;
}