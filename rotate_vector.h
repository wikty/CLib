#ifndef ROTATE_VECTOR_H_
#define ROTATE_VECTOR_H_

/*
 *	@param: k
 *		if k is 0, will reverse vector
 */
int left_rotate(void *data, unsigned int size, unsigned int n, unsigned int k);

/*
 *	@param: k
 *		if k is 0, will reverse vector
 */
int right_rotate(void *data, unsigned int size, unsigned int n, unsigned int k);

#endif