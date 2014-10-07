#include <stdio.h>

#include "rotate_vector.h"

void show(int a[], int n){
	for(int i=0; i<n-1; i++){
		printf("%d, ", a[i]);
	}
	printf("%d\n", a[n-1]);
}

int main(){
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	puts("Original Data");
	show(a, 9);
	
	puts("Left Rotate");
	left_rotate(a, sizeof(int), 9, 5);
	show(a, 9);

	puts("Reverse");
	left_rotate(a, sizeof(int), 9, 0);
	show(a, 9);

	puts("Right Rotate");
	right_rotate(a, sizeof(int), 9, 3);
	show(a, 9);

	return 0;
}