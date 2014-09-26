#include <stdio.h>
#include "bit.h"

/*
 *	@function
 *		Time-Performance:	O(n), (when k=2, is O(1))
 *		Space-Performance:	O(1)
 */
int joseph(unsigned int n, int k){
	if(n < 2){
		return n;
	}

	if(k == 2){
		/* O(1) */
		bit_highest_zero(&n, sizeof(int));
		n <<= 1;
		bit_set(&n, 0, 1);
		return n;
	}
	else{
		int r = 0;
		for(int i=2; i<=n; i++){
			r = (r+k) % i;
		}
		return r;
	}
}

int main(){

	printf("%s\n", "k=2");
	for(int i=1; i<9; i++){
		printf("%d\n", joseph(i, 2));
	}

	printf("%s\n", "k=3");
	printf("%d\n", joseph(15, 4));
	

	return 0;
}