#include <stdlib.h>
static int lrotate(void *data, unsigned int size, unsigned int n);
static int rrotate(void *data, unsigned int size, unsigned int n);
static int reverse(void *data, unsigned int size, unsigned int n);
static int left_rotate1(void *data, unsigned int size, unsigned int n, unsigned int k);
static int left_rotate2(void *data, unsigned int size, unsigned int n, unsigned int k);
static int left_rotate3(void *data, unsigned int size, unsigned int n, unsigned int k);
static int right_rotate1(void *data, unsigned int size, unsigned int n, unsigned int k);
static int right_rotate2(void *data, unsigned int size, unsigned int n, unsigned int k);
static int right_rotate3(void *data, unsigned int size, unsigned int n, unsigned int k);

int left_rotate(void *data, unsigned int size, unsigned int n, unsigned int k){
	if(data == NULL || size < 1 || n < 1){
		return -1;
	}

	if(k == 0){
		return reverse(data, size, n);	
	}

	if(k > n/2){
		return right_rotate(data, size, n, n-k);
	}

	return left_rotate1(data, size, n, k);
}

int right_rotate(void *data, unsigned int size, unsigned int n, unsigned int k){
	if(data == NULL || size < 1 || n < 1){
		return -1;
	}

	if(k == 0){
		return reverse(data, size, n);
	}

	if(k > n/2){
		return left_rotate(data, size, n, n-k);
	}

	return right_rotate1(data, size, n, k);
}


/*
 *	Internal Interface
 */
static int lrotate(void *data, unsigned int size, unsigned int n){
	char *p = (char *)data;
	char *temp = NULL;
	if((temp = (char *)malloc(size)) == NULL){
		return -1;
	}

	memcpy(temp, &p[0], size);
	for(int i=0; i<n-1; i++){
		memcpy(&p[size*i], &p[size*(i+1)], size);
	}
	memcpy(&p[size*(n-1)], temp, size);
	
	free(temp);
	return 0;
}

static int rrotate(void *data, unsigned int size, unsigned int n){
	char *p = (char *)data;
	char *temp = NULL;
	if((temp = (char *)malloc(size)) == NULL){
		return -1;
	}

	memcpy(temp, &p[size*(n-1)], size);
	for(int i=n-2; i>=0; i--){
		memcpy(&p[size*i], &p[size*(i+1)], size);
	}
	memcpy(&p[0], temp, size);
	
	free(temp);
	return 0;
}

static int reverse(void *data, unsigned int size, unsigned int n){
	char *p = (char *)data;
	char *temp = NULL;
	if((temp = (char *)malloc(size)) == NULL){
		return -1;
	}

	int mid = (int)(n/2);
	for(int i=0; i<mid; i++){
		memcpy(temp, &p[size*i], size);
		memcpy(&p[size*i], &p[size*(n-1-i)], size);
		memcpy(&p[size*(n-1-i)], temp, size);
	}
	free(temp);
	return 0;
}

static int left_rotate1(void *data, unsigned int size, unsigned int n, unsigned int k){
	char *p = (char *)data;
	char *temp = NULL;
	if((temp = (char *)malloc(size)) == NULL){
		return -1;
	}

	for(int i=0; i<k; i++){
		memcpy(temp, &p[size*i], size);
		int j = i + k;	/* start+step */
		while(j<n){
			memcpy(&p[size*(j-k)], &p[size*j], size);
			j += k;
		}
		memcpy(&p[size*(j-k)], temp, size);
	}

	if(n % k){
		left_rotate1(&p[size*(n-k)], size, k, k-n%k);
	}
	free(temp);
	return 0;
}

static int right_rotate1(void *data, unsigned int size, unsigned int n, unsigned int k){
	char *p = (char *)data;
	char *temp = NULL;
	if((temp = (char *)malloc(size)) == NULL){
		return -1;
	}

	for(int i=n-1; i>n-1-k; i--){
		memcpy(temp, &p[size*i], size);
		int j = i - k;	/* start+step */
		while(j>=0){
			memcpy(&p[size*(j+k)], &p[size*j], size);
			j -= k;
		}
		memcpy(&p[size*(j+k)], temp, size);
	}

	if(n % k){
		right_rotate1(&p[0], size, k, k-n%k);
	}
	free(temp);
	return 0;
}

static int left_rotate2(void *data, unsigned int size, unsigned int n, unsigned int k){
	if(k > n/2){
		return right_rotate2(data, size, n, n-k);
	}

	char *temp = NULL;
	if((temp = (char *)malloc(size*k)) == NULL){
		return -1;
	}
	char *p = (char *)data;
	memcpy(temp, &p[0], size*k);
	memcpy(&p[0], &p[size*(n-k)], size*k);
	memcpy(&p[size*(n-k)], temp, size*k);
	if(n-2*k != 0){
		return left_rotate2(&p[0], size, n-k, k);
	}
	return 0;
}

static int right_rotate2(void *data, unsigned int size, unsigned int n, unsigned int k){
	if(k > n/2){
		return left_rotate2(data, size, n, n-k);
	}

	char *temp = NULL;
	if((temp = (char *)malloc(size*k)) == NULL){
		return -1;
	}
	char *p = (char *)data;
	memcpy(temp, &p[size*(n-k)], size*k);
	memcpy(&p[size*(n-k)], &p[0], size*k);
	memcpy(&p[0], temp, size*k);
	if(n-2*k != 0){
		return right_rotate2(&p[size*k], size, n-k, k);
	}
	return 0;
}

static int left_rotate3(void *data, unsigned int size, unsigned int n, unsigned int k){
	char *p = (char *)data;
	if(reverse(&p[0], size, k) !=0){
		return -1;
	}
	if(reverse(&p[size*k], size, n-k) != 0){
		return -1;
	}
	if(reverse(&p[0], size, n) != 0){
		return -1;
	}
	return 0;
}

static int right_rotate3(void *data, unsigned int size, unsigned int n, unsigned int k){
	char *p = (char *)data;
	if(reverse(&p[0], size, n-k) !=0){
		return -1;
	}
	if(reverse(&p[size*(n-k)], size, k) != 0){
		return -1;
	}
	if(reverse(&p[0], size, n) != 0){
		return -1;
	}
	return 0;
}