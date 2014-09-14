#include <stdio.h>
#include <stdlib.h>

#include "sort.h"

#define MAX_ITEM 20

int *nums[MAX_ITEM];

int compare(const void *data1, const void *data2){
	int m = *((int *)data1);
	int n = *((int *)data2);

	return (m > n ? 1 : (m < n ? -1 : 0));
}

void setup(){
	for(int i=0; i<MAX_ITEM; i++){
		if((nums[i] = (int *)malloc(sizeof(int))) == NULL){
			for(int j=i-1; j>=0; j--){
				free(nums[j]);
			}
			return;
		}
		*(nums[i]) = rand() % 100;
	}
}

void enddown(){
	for(int i=0; i<MAX_ITEM; i++){
		free(nums[i]);
	}
}

void show(int *data[], unsigned int n){
	for(int i=0; i<n; i++){
		printf("%7d\n", *(data[i]));
	}
	printf("\n");
}

void reset(int *data[], unsigned int n){
	for(int i=0; i<n; i++){
		*(data[i]) = rand() % 100;
	}
}

int main(){
	setup();

	puts("Before ")
	show(nums, MAX_ITEM);

	puts("Sorted");
	issort()

	enddown();
	return 0;
}