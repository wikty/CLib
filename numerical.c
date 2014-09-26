#include <stdlib.h>

int interpol(const double *x,
			const double *fx,
			unsigned int n,
			const double *z,
			double *pz,
			unsigned int m){
	int j;
	double *table = NULL;
	double *coeff = NULL;
	if((table = (double *)malloc(sizeof(double)*n)) == NULL){
		return -1;
	}
	if((coeff = (double *)malloc(sizeof(double)*n)) == NULL){
		free(table);
		return -1;
	}

	memcpy(table, fx, sizeof(double)*n);

	coeff[0] = table[0];
	for(int r=1; r<n; r++){
		for(int i=0; i<n-r; i++){
			j = i + r;
			table[i] = (table[i+1] - table[i])/(x[j]-x[i]);
		}
		coeff[r] = table[0];
	}
	free(table);

	while(m--){
		pz[m] = coeff[0];
		for(int p=1; p<n; p++){
			double temp = coeff[p];
			for(int q=0; q<p; q++){
				temp *= (z[m]-x[q]);
			}
			pz[m] += temp;
		}
	}
	free(coeff);
	return 0;
}

void lesq(const double *x,
		const double *y,
		unsigned int n,
		double *k,
		double *b){
	double sum[4] = {0.0, };
	for(int i=0; i<n; i++){
		sum[0] += x[i]*y[i];
		sum[1] += x[i];
		sum[2] += y[i];
		sum[3] += x[i]*x[i];
	}
	*k = (n*sum[0]-sum[1]*sum[2])/(n*sum[3]-sum[1]*sum[1]);
	*b = (sum[2]-(*k)*sum[1])/n;
}