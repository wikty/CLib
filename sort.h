#ifndef SORT_H_
#define SORT_H_

/*
 *	@function
 *		Name:				Bubble Sort
 *		Stability:			true
 *		Time-Performance:	O(n*n)
 *		In-Position:		true
 *		Comparision:		true
 *		Description:		If the input is a sorted, O(n*n)
 *  @param: size
 *		the byte number of the element
 *	@param: n
 *		the number of element in the array
 *	@param: compare
 *		a compare function, return -1 if data1 < data2, 
 *		return 0 if data1 = data2, return 1 if data1 > data2
 */
extern int busort(void *data,
					unsigned int size,
					unsigned int n,
					int (*compare)(const void *data1, const void *data2));

/*
 *	@function
 *		Name:				Cocktail Sort
 *		Stability:			true
 *		Comparision:		true
 *		Time-Performance:	O(n*n)
 *		In-Position:		true
 *		Description:		The improved version of Bubble Sort, if the input is a sorted, O(n)
 */
extern int cosort(void *data,
					unsigned int size,
					unsigned int n,
					int (*compare)(const void *data1, const void *data2));


/*
 *	@function
 *		Name:				Selection Sort
 *		Stability:			false
 *		Comparision:		true
 *		Time-Performance:	O(n*n)
 *		In-Position:		true
 */
extern int slsort(void *data,
					unsigned int size,
					unsigned int n,
					int (*compare)(const void *data1, const void *data2));

/*
 *	@function
 *		Name:				Stability Selection Sort
 *		Stability:			true
 *		Comparision:		true
 *		Time-Performance:	O(n*n)
 *		In-Position:		true
 *		Description:		the stability version selection sort
 */
extern int slssort(void *data,
					unsigned int size,
					unsigned int n,
					int (*compare)(const void *data1, const void *data2));

/*
 *	@function 
 *		Name: 				Insertion Sort
 *		Stability: 			true
 *		Comparision:		true
 *		Time-Performance: 	O(n*n)
 *		In-Position: 		true
 *		
 */
extern int issort(void *data,
					unsigned int size,
					unsigned int n,
					int (*compare)(const void *data1, const void *data2));


/*
 *	@param: start, end
 *			the part of array to sort, [start, end)
 *			So if you want to sort the whole array
 *			pass 0 to start, pass n to end
 */
extern int qksort(void *data,
				  unsigned int size,
				  unsigned int n,
				  unsigned int start,
				  unsigned int end,
				  int (*compare)(const void *data1, const void *data2));

/*
 *  @function: get indexth element in the array
 *	@param: index
 *		start from 0, [0, n-1]
 */
extern int ordinal(void *data,
				   unsigned int size,
				   unsigned int n,
				   int (*compare)(const void *data1, const void *data2),
				   unsigned int index,
				   void **element);

extern int mgsort(void *data,
				   unsigned int size,
				   unsigned int n,
				   unsigned int start,
				   unsigned int end,
				   void *rtn,
				   int (*compare)(const void *data1, const void *data2));

/*
 *  @param: data
 *		a int array(element >= 0)
 *	@param: max
 *		max number in the array
 */
extern int ctsort(int *data, unsigned int n, unsigned int max);

/*
 *	@param: base
 *		e.g, decimal system base is 10, binary system base is 2
 *	@param: w
 *		element's number width, e.g, 200's w is 2, 30's w is 2
 */
extern int bssort(int *data, unsigned int n, unsigned int w, unsigned int base);

/*
 *  @function: return target element's index, if not in
 *		array return -1
 */
extern int bisearch(const void *data, 
					const void *target,
					unsigned int n,
					unsigned int size,
					int (*compare)(const void *data1, const void *data2));

#endif