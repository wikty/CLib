#ifndef NUMBERICAL_H_
#define NUMBERICAL_H_
/*
 *	@function
 *		Name:			Polynomial interpolation
 */
extern int interpol(const double *x,
				const double *fx,
				unsigned int n,
				const double *z,
				double *pz,
				unsigned int m);
/*
 *	@function
 *		Name:			The least square method
 */
extern void lesq(const double *x,
				const double *y,
				unsigned int n,
				double *k,
				double *b);

#endif