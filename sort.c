#include "sort.h"

#include <stdlib.h>

static void merge(void *data1,
				void *data2,
				unsigned int n1,
				unsigned int n2,
				unsigned int size,
				void *rtn,
				int (*compare)(const void *key1, const void *key2));

 static int partition(void *data,
					 unsigned int size,
					 unsigned int start,
					 unsigned int end,
					 int (*compare)(const void *data1, const void *data2));

int busort(void *data,
			unsigned int size,
			unsigned int n,
			int (*compare)(const void *data1, const void *data2)){
	if(size < 1 || n < 1 || data == NULL || compare == NULL){
		return -1;
	}

	char *p = (char *)data;
	char *temp = NULL;
	if((temp = (char *)malloc(size) == NULL){
		return -1;
	}

	for(int i=n-2; i>=0; i--){
		/* [i+1,,,n-1] had been sorted */
		for(int j=0; j<=i; j++){
			if(compare(&(data[j*size], &(data[(j+1)*size]))) > 0){
				memcpy(temp, &(data[j*size]), size);
				memcpy(&(data[j*size]), &(data[(j+1)*size]), size);
				memcpy(&(data[(j+1)*size]), temp, size);
			}
		}
	}

	free(temp);
	return 0;
}

int cosort(void *data,
			unsigned int size,
			unsigned int n,
			int (*compare)(const void *data1, const void *data2)){
	if(size < 1 || n < 1 || data == NULL || compare == NULL){
		return -1;
	}

	char *p = (char *)data;
	char *temp = NULL;
	if((temp = (char *)malloc(size) == NULL){
		return -1;
	}

	int left = 0;
	int right = n-1;
	int swapped = 1;

	while(swapped){
		swapped = 0;

		/* scan [left, right-1] to bubble the max to [right] */
		for(int i=left; i<right; i++){
			if(compare(&(data[i*size]), &(data[(i+1)*size])) > 0){
				memcpy(temp, &(data[i*size]), size);
				memcpy(&(data[i*size]), &(data[(i+1)*size]), size);
				memcpy(&(data[(i+1)*size]), temp, size);
				swapped = 1;
			}
		}
		right--;

		/* scan [left-1, right] to bubble the min to [left] */
		for(int j=right; j>left; j--){
			if(compare(&(data[j*size]), &(data[(j-1)*size])) < 0){
				memcpy(temp, &(data[j*size]), size);
				memcpy(&(data[j*size]), &(data[(j-1)*size]), size);
				memcpy(&(data[(j-1)*size]), temp, size);
				swapped = 1;
			}
		}
		left++;
	}

	free(temp);
	return 0;
}

int slsort(void *data,
		   unsigned int size,
		   unsigned int n,
		   int (*compare)(const void *data1, const void *data2)){
	if(size < 1 || n < 1 || data == NULL || compare == NULL){
		return -1;
	}

	char *p = (char *)data;
	char *temp = NULL;
	if((temp = (char *)malloc(size)) == NULL){
		return -1;
	}

	for(int i=0; i<n-1; i++){

		/* find the min in [i,,,n-1] */
		int pos = i;
		for(int j=i; j<n; j++){
			if(compare(&(data[j*size]), &(data[i*size])) < 0){
				pos = j;
			}
		}

		if(pos != i){
			memcpy(temp, &(data[pos*size]), size);
			memcpy(&(data[pos*size]), &(data[i*size]), size);
			memcpy(&(data[i*size]), temp, size);
		}
	}

	free(temp);
	return 0;
}

int slssort(void *data,
		   unsigned int size,
		   unsigned int n,
		   int (*compare)(const void *data1, const void *data2)){
	if(size < 1 || n < 1 || data == NULL || compare == NULL){
		return -1;
	}

	char *p = (char *)data;
	char *temp = NULL;
	if((temp = (char *)malloc(size)) == NULL){
		return -1;
	}

	for(int i=0; i<n-1; i++){

		/* find the min in [i,,,n-1] */
		int pos = i;
		memcpy(temp, &(data[i*size]));
		for(int j=i; j<n; j++){
			if(compare(&(data[j*size]), temp) < 0){
				memcpy(temp, &(data[j*size]), size);
				pos = j;
			}
		}

		if(pos != i){
			int m = pos-1;
			for(; m>i; m--){
				if(compare(&(data[m*size]), &(data[i*size])) == 0){
					memcpy(&(data[pos*size]), &(data[m*size]), size);
					pos = m;
				}
			}
			memcpy(&(data[pos*size]), &(data[i*size]), size);
			memcpy(&(data[i*size]), temp, size);
		}
	}

	free(temp);
	return 0;
}

int issort(void *data,
		   unsigned int size,
		   unsigned int n,
		   int (*compare)(const void *data1, const void *data2)){
	if(size < 1 || n < 1 || data == NULL || compare == NULL){
		return -1;
	}

	char *p = (char *)data;
	char *temp = NULL;
	if((temp = (char *)malloc(size)) == NULL){
		return -1;
	}

	for(int i=1; i<n; i++){
		memcpy(temp, &data[i*size], size);
		/* [0,,,i-1] had been sorted */
		int j=i-1;
		for(; j>=0; j--){
			if(compare(temp, &data[j*size]) < 0){
				memcpy(&data[(j+1)*size], &data[j*size], size);
			}
			else{
				break;
			}
		}
		memcpy(&data[(j+1)*size], temp, size);
	}

	free(temp);
	return 0;
}


// to debug
int ordinal(void *data,
		    unsigned int size,
		    unsigned int n,
		    int (*compare)(const void *data1, const void *data2),
		    unsigned int index,
		    void **element){
	if(index > n-1){
		return -1;
	}
	int pos, start, end;
	start = 0;
	end = n;
	while(1){
		if((pos = partition(data, size, start, end, compare)) < 0){
			return -1;
		}
		if(pos==index){
			break;
		}
		else if(pos < index){
			start = pos + 1;
		}
		else{
			end = pos;
		}
	}
	*element = &(((char *)data)[pos*size]);
	return 0;
}


int qksort(void *data,
		   unsigned int size,
		   unsigned int n,
		   unsigned int start,
		   unsigned int end,
		   int (*compare)(const void *data1, const void *data2)){
	int pos;
	while(start < end-1){
		if((pos = partition(data, size, start, end, compare)) < 0){
			return -1;
		}
		/* now data[pos] is in correctly position */

		/* recursively sort left parition */
		if(qksort(data, size, n, start, pos, compare) < 0){
			return -1;
		}

		/* next loop will recursively sort right partition */
		start = pos + 1;
	}
	return 0;
}

// to debug
int mgsort(void *data,
		   unsigned int size,
		   unsigned int n,
		   unsigned int start,
		   unsigned int end,
		   void *rtn,
		   int (*compare)(const void *data1, const void *data2)){
	if(size < 1 || end > n-1){
		return -1;
	}
	if(start >= end){
		/* divide work is over */
		return 0;
	}
	else{
		int mid = ((int)((end-start+1)/2)) + start;
		void *lpart, *rpart;
		if((lpart = (void *)malloc((mid-start+1)*size)) == NULL){
			return -1;
		}
		if((rpart = (void *)malloc((end-mid)*size)) == NULL){
			free(lpart);
			return -1;
		}
		mgsort(data, size, mid-start+1, start, end, lpart, compare);
		mgsort(data, size, end-mid, mid+1, end, rpart, compare);
		merge(lpart, rpart, mid-start+1, end-mid, size, rtn, compare);
		free(lpart);
		free(rpart);
		return 0;
	}
}

int ctsort(int *data, unsigned int n, unsigned int max){
	/* max must larger than n */
	if(max < n){
		return -1;
	}
	max = max+1;
	
	int *p, *temp;
	if((p = (int *)malloc(sizeof(int)*max)) == NULL){
		return -1;
	}
	if((temp = (int *)malloc(sizeof(int)*n)) == NULL){
		free(p);
		return -1;
	}

	/* initial space, 0 means not in data */
	memset(p, 0, sizeof(int)*max);
	/* count the occurrences of each element */
	int i = 0;
	for(; i<n; i++){
		p[data[i]]++;
	}
	/* calucate element's position(start from 1) */
	i = 1;
	for(; i<max; i++){
		p[i] += p[i-1];
	}

	/* insert elment into temp */
	for(int j=n-1; j>=0; j--){
		temp[p[data[j]]-1] = data[j];
		/* make sure sort stability */
		p[data[j]]--;
	}

	memcpy(data, temp, n*sizeof(int));
	free(temp);
	free(p);
	return 0;
}

///////////////////////to debug
int bssort(int *data, unsigned int n, unsigned int w, unsigned int base){
	int *counts, *temp;
	if((counts = (int *)malloc(sizeof(int)*base)) == NULL){
		return -1;
	}
	if((temp = (int *)malloc(sizeof(int)*n)) == NULL){
		free(counts);
		return -1;
	}

	for(int i=0; i<w; i++){
		/* bit weight */
		int j, weight;
		j = i;
		weight = 1;
		while(j!=0){
			weight *= base;
			j--;
		}
		/* initial counts */
		memset(counts, 0, sizeof(int)*base);

		/* record element occurences */
		j = 0;
		for(; j<n; j++){
			counts[((int)(data[j]/weight)) % base]++;
		}
		/* calucate element position (start from 1) */
		j = 1;
		for(; j<base; j++){
			counts[j] += counts[j-1];
		}
		j = n - 1;
		for(; j>=0; j--){
			temp[counts[((int)(data[j]/weight)) % base] - 1] = data[j];
			counts[((int)(data[j]/weight)) % base]--;
		}
	}
	memcpy(data, temp, sizeof(int)*n);

	free(counts);
	free(temp);
	return 0;
}

// to debug
int bisearch(const void *data,
			const void *target,
			unsigned int n,
			unsigned int size,
			int (*compare)(const void *data1, const void *data2)){
	int left = 0;
	int right = n - 1;
	data = (char *)data;
	while(left<=right){
		int mid = (int)((left+right)/2);
		int retval = compare(&data[mid*size], target);
		if(retval < 0){
			left = mid + 1;
		}
		else if(retval > 0){
			right = mid - 1;
		}
		else{
			return mid;
		}
	}
	return -1;
}


/*
 * Internal Functions
 */

int partition(void *data,
			unsigned int size,
			unsigned int start,
			unsigned int end,
			int (*compare)(const void *data1, const void *data2)){
	char *p = (char *)data;
	char *base, *swap;
	if((base = (char *)malloc(sizeof(size))) == NULL){
		return -1;
	}
	if((swap = (char *)malloc(sizeof(size))) == NULL){
		free(base);
		return -1;
	}

	/* pick a position */
	int a[3], temp;
	a[0] = (rand() % (end-start)) + start;
	a[1] = (rand() % (end-start)) + start;
	a[2] = (rand() % (end-start)) + start;
	for(int i=1; i<3; i++){
		temp = a[i];
		int j=i-1;
		for(; j>=0; j++){
			if(a[j+1] < a[j]){
				a[j+1] = a[j];
			}
			else{
				break;
			}
		}
		a[j+1] = temp;
	}
	memcpy(base, &data[a[1]*size], size);

	while(1){
		while(compare(&data[start*size], base) < 0){
			start++;
		}

		while(compare(&data[(end-1)*size], base) >= 0){
			end--;
		}

		if(start >= end-1){
			break;
		}
		else{
			memcpy(swap, &data[start*size], size);
			memcpy(&data[start*size], &data[(end-1)*size], size);
			memcpy(&data[(end-1)*size], swap, size);
		}
	}
	free(base);
	free(swap);
	return end-1;
}

/* data1(lenth is n1) and data2(length is n2) is sorted array */
void merge(void *data1,
			void *data2,
			unsigned int n1,
			unsigned int n2,
			unsigned int size,
			void *rtn,
			int (*compare)(const void *key1, const void *key2)){
	rtn = (char *)rtn;
	char *p1 = (char *)data1;
	char *p2 = (char *)data2;
	int i=0, j=0, index=0;
	while(i<n1 && j<n2){
		int retval = compare(&p1[i*size], &p2[j*size]);
		if(retval < 0){
			memcpy(&rtn[index*size], &p1[i*size], size);
			i++;
		}
		else{
			memcpy(&rtn[index*size], &p2[i*size], size);
			j++;
		}
		index++;
	}

	if(i<n1){
		memcpy(&rtn[index*size], &p1[i*size], size*(n1-i));
	}
	else if(j<n2){
		memcpy(&rtn[index*size], &p2[j*size], size*(n2-j));
	}
	return;
}