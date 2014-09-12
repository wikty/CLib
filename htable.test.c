#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "htable.h"

#define BUCKETS 30

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

int hash(const void *data){
	const char *p = ((UserInfo *)data)->username;
	unsigned int value = 0;

	while(*p != '\0'){
		unsigned int temp;
		value = (value << 4) + (*p);

		if(temp =( value & 0xf0000000 )){
			value = value ^ (temp >> 24);
			value = value ^ temp;
		}
		p++;
	}
	return value % BUCKETS;
}

int main(){
	HTable *htb;
	if((htb = (HTable *)malloc(sizeof(HTable))) == NULL){
		return -1;
	}

	htable_init(htb, BUCKETS, hash, destroy, match);

	UserInfo *u;
	if((u = (UserInfo *)malloc(sizeof(UserInfo))) == NULL){
		htable_destroy(htb);
		free(htb);
		return -1;
	}
	u->seq = 0;
	sprintf(u->username, "%d-item", u->seq);
	puts("Insert 0-item into HTable: ");
	htable_insert(htb, u);
	htable_dump(htb, print);
	puts("");

	puts("Insert 0-item into HTable: ");
	htable_insert(htb, u);
	htable_dump(htb, print);
	puts("");

	puts("Remove 0-item from HTable: ");
	htable_remove(htb, u);
	htable_dump(htb, print);
	puts("");

	puts("Insert 0-item into HTable: ");
	htable_insert(htb, u);
	htable_dump(htb, print);
	puts("");

	puts("HTable has 0-item ?");
	if(htable_has_data(htb, u)){
		puts("Yes!");
	}
	else{
		puts("No!");
	}

	htable_destroy(htb);
	free(htb);
	return 0;
}