#ifdef BIT_H_
#define BIT_H_

#include <stdlib.h>

extern int bit_get(const unsigned char *data,
					unsigned int index);

extern void bit_set(unsigned char *data,
					unsigned int index,
					unsigned int value);

extern void bit_left_rotate(unsigned char *data,
							unsigned int bytes,
							unsigned int count);

extern void bit_right_rotate(unsigned char *data,
							unsigned int bytes,
							unsigned int count);

extern int bit_highest(const unsigned char *data,
						unsigned int bytes);
#endif