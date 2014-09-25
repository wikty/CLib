#include <stdio.h>
#include "bit.h"

int main(){

	unsigned int m = 0x11223344;
	printf("%s : %x\n", "Original Data", m);
	printf("%s : ", "Bit get");
	for(int i=sizeof(int)*8-1; i>=0; i--){
		printf("%d", bit_get(&m, i));
	}
	printf("\n");

	unsigned int n = 0x87654321;
	printf("%s\n", "Bit Set as 0x87654321");
	for(int i=sizeof(int)*8-1; i>=0; i--){
		bit_set(&m, i, bit_get(&n, i));
	}
	printf("%x\n", m);


	m = 0x10000000;	
	printf("%s\n", "Rotate Bit");
	printf("%s : %x\n", "Original Data", m);
	bit_left_rotate(&m, sizeof(m), 2);
	printf("%s : %x\n", "After rotate left 2", m);

	bit_right_rotate(&m, sizeof(m), 2);
	printf("%s : %x\n", "After rotate right 2", m);

	n = 0x33123410;
	printf("%s : %x\n", "Original Data", n);
	printf("%s\n", "Highest 1 index");
	printf("%d\n", bit_highest(&n, sizeof(int)));
	printf("%s\n", "Lowest 1 index");
	printf("%d\n", bit_lowest(&n, sizeof(int)));

	printf("%s : %x\n", "Original Data", n);
	printf("%s\n", "Highest zero");
	bit_highest_zero(&n, sizeof(int));
	printf("%x\n", n);
	printf("%s\n", "Lowest zero");
	bit_lowest_zero(&n, sizeof(int));
	printf("%x\n", n);


	return 0;
}