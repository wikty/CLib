#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ohtable.h"

/* prime number */
#define POSITIONS 53

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

int hash1(const void *data){
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
	return value;
}

int hash2(const void *data){
	const char *p = ((UserInfo *)data)->username;
	unsigned long value = 5381;
	while(*p != '\0'){
		/* value*33 + *p */
		value = ((value << 5) + value) + *p;
	}
	return (value % (POSITIONS-1)) + 1;
}

int main(){
	OHTable *ohtb;
	if((ohtb = (OHTable *)malloc(sizeof(OHTable))) == NULL){
		return -1;
	}
	ohtable_init(ohtb, POSITIONS, hash1, hash2, destroy, match);

	UserInfo *u;
	if((u = (UserInfo *)malloc(sizeof(UserInfo))) == NULL){
		ohtable_destroy(ohtb);
		free(ohtb);
		return -1;
	}
	u->seq = 0;
	sprintf(u->username, "%d-item", u->seq);
	puts("Insert 0-item into OHTable: ");
	ohtable_insert(ohtb, u);
	ohtable_dump(ohtb, print);
	puts("");

	puts("Insert 0-item into OHTable: ");
	ohtable_insert(ohtb, u);
	ohtable_dump(ohtb, print);
	puts("");

	puts("Remove 0-item from OHTable: ");
	ohtable_remove(ohtb, u);
	ohtable_dump(ohtb, print);
	puts("");

	puts("Insert 0-item into OHTable: ");
	ohtable_insert(ohtb, u);
	ohtable_dump(ohtb, print);
	puts("");

	puts("OHTable has 0-item ?");
	if(ohtable_has_data(ohtb, u)){
		puts("Yes!");
	}
	else{
		puts("No!");
	}

	ohtable_destroy(ohtb);
	free(ohtb);
	return 0;
}