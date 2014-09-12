#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "set.h"

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

// void destroy(void* data){
// 	free(data);
// }

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
Set *st, *st1, *st2;
UserInfo *u[3];

int create_set(){
	if((st = (Set *)malloc(sizeof(Set))) == NULL){
		return -1;
	}
	if((st1 = (Set *)malloc(sizeof(Set))) == NULL){
		free(st);
		return -1;
	}
	if((st2 = (Set *)malloc(sizeof(Set))) == NULL){
		free(st);
		free(st1);
		return -1;
	}
	set_init(st, NULL, match);
	set_init(st1, NULL, match);
	set_init(st2, NULL, match);

	for(int i=0; i<3; i++){
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

void destroy_set(){
	set_destroy(st);
	set_destroy(st1);
	set_destroy(st2);
	free(st);
	free(st1);
	free(st2);

	for(int i=0; i<3; i++){
		free(u[i]);
	}
}


int main(){
	
	if(create_set() == -1){
		return -1;
	}

	puts("Add 0-item into Set1: ");
	set_insert(st1, u[0]);
	set_dump(st1, print);
	puts("");

	puts("Add 1-item into Set1: ");
	set_insert(st1, u[1]);
	set_dump(st1, print);
	puts("");

	puts("Add 0-item into Set2: ");
	set_insert(st2, u[0]);
	set_dump(st2, print);
	puts("");

	puts("Set1 intersection with Set2 is: ");
	set_intersection(st, st1, st2);
	set_dump(st, print);
	puts("");

	puts("Set is equal to Set2: ");
	if(set_is_equal(st, st2)){
		puts("Yes!");
	}
	else{
		puts("No!");
	}
	puts("");

	puts("Set1 difference with Set2 is: ");
	set_difference(st, st1, st2);
	set_dump(st, print);
	puts("");

	puts("Set1 union with Set2 is: ");
	set_union(st, st1, st2);
	set_dump(st, print);
	puts("");

	puts("Set2 in Set1: ");
	if(set_is_subset(st1, st2)){
		puts("Yes!");
	}
	else{
		puts("No!");
	}
	puts("");

	puts("Remove 1-item from Set1: ");
	set_remove(st1, u[1]);
	set_dump(st1, print);
	puts("");
	puts("Set1 now equal to Set2: ");
	if(set_is_equal(st1, st2)){
		puts("Yes!");
	}
	else{
		puts("No!");
	}
	puts("");

	destroy_set();
	return 0;
}