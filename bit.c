#include "bit.h"
#define BITS 8
/*
int bit_is_bigend(){
	unsigned int i = 0x01;
	char *p = (char *)&i;
	return (p[0] == 1 ? 1 : 0);
}
*/

int bit_get(const unsigned char *data,
			unsigned int index){
	unsigned char mask = 0x01;
	mask <<= index % (sizeof(char)*BITS);

	// if(bit_is_bigend()){
	// 	pos = index / sizeof(char);
	// }
	// else{
	// 	pos = bytes - 1 - index / sizeof(char);
	// }

	return ((data[index/(sizeof(char)*BITS)]&mask) == mask ? 1 : 0);
}

void bit_set(unsigned char *data,
			unsigned int index,
			unsigned int value){
	unsigned char mask = 0x01;
	mask <<= index % (sizeof(char)*BITS);

	if(value){
		data[index/(sizeof(char)*BITS)] |= mask;
	}
	else{
		data[index/(sizeof(char)*BITS)] &= ~mask;
	}
}

void bit_left_rotate(unsigned char *data,
						unsigned int bytes,
						unsigned int count){
	count %= bytes*BITS;
	for(int c=0; c<count; c++){
		int ffbit = bit_get(&data[0], 0);
		
		for(int i=0; i<bytes-1; i++){
			int fbit = bit_get(&data[i+1], 0);
			data[i] >>= 1;
			bit_set(&data[i], BITS-1, fbit);
		}
		
		data[bytes-1] >>= 1;
		bit_set(&data[bytes-1], BITS-1, ffbit);
	}
}

void bit_right_rotate(unsigned char *data,
						unsigned int bytes,
						unsigned int count){
	count %= bytes*BITS;
	for(int c=0; c<count; c++){
		int llbit = bit_get(&data[bytes-1], BITS-1);

		for(int i=bytes-1; i>0; i--){
			int lbit = bit_get(&data[i-1], BITS-1);
			data[i] <<= 1;
			bit_set(&data[i], 0, lbit);
		}

		data[0] <<= 1;
		bit_set(&data[0], 0, llbit);
	}
}

int bit_highest(const unsigned char *data,
				unsigned int bytes){
	for(int i=bytes-1; i>=0; i--){
		for(int j=BITS-1; j>=0; j--){
			if(bit_get(&data[i], j)){
				return i*BITS+j;
			}
		}
	}
	return -1;
}

int bit_highest_zero(unsigned char *data,
					unsigned int bytes){
	for(int i=bytes-1; i>=0; i--){
		for(int j=BITS-1; j>=0; j--){
			if(bit_get(&data[i], j)){
				bit_set(&data[i],j, 0);
				return 0;
			}
		}
	}
	return -1;
}

int bit_lowest(const unsigned char *data,
				unsigned int bytes){
	for(int i=0; i<bytes; i++){
		for(int j=0; j<BITS; j++){
			if(bit_get(&data[i], j)){
				return i*BITS+j;
			}
		}
	}
	return -1;
}

int bit_lowest_zero(unsigned char *data,
					unsigned int bytes){
	for(int i=0; i<bytes; i++){
		for(int j=0; j<BITS; j++){
			if(bit_get(&data[i], j)){
				bit_set(&data[i], j, 0);
				return 0;
			}
		}
	}
	return -1;
}