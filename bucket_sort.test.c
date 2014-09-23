#include <stdio.h>
#include "list.h"
#include "bucket_sort.h"

typedef struct Point_{
	int x;
	int y;
}Point;

int compare(const Point *data1, const Point *data2){
	if(data1->x > data2->x){
		return 1;
	}
	else if(data1->x < data2->x){
		return -1;
	}
	else{
		return 0;
	}
}

int hash(const Point *pt){
	return pt->x;
}

void print(const Point *pt){
	printf("(%d, %d) ", pt->x, pt->y);
}

Point ps[6] = {{5, 6}, {3, 7}, {0, 3}, {3, 5}, {3, 4}, {2, 3}};

int main(){
	Bucket bk;
	List lst;
	bucket_init(&bk, NULL, compare, hash, 6);
	list_init(&lst, NULL, NULL);

	for(int i=0; i<6; i++){
		bucket_insert(&bk, &ps[i]);
	}

	bucket_sort(&bk, &lst);
	list_dump(&lst, print);
	printf("\n");

	bucket_destroy(&bk);
	list_destroy(&lst);
	return 0;
}