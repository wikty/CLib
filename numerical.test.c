#include <stdio.h>
#include "numerical.h"

void show(const double *lst, unsigned int n){
	int i=n;
	while(i>1){
		printf("%f, ", lst[n-i]);
		i--;
	}
	printf("%f\n", lst[n-1]);
}

int main(){
	puts("Polynomial interpolation ");
	double x[4] = {-3.0, -2.0, 2.0, 3.0};
	double fx[4] = {-5.0, -1.1, 1.9, 4.8};
	double z[4] = {-2.5, 0.0, 1.0, 2.5};
	double pz[4];
	interpol(x, fx, 4, z, pz, 4);
	show(pz, 4);

	puts("The least square method");
	double x1[9] = {-4.0, -3.0, -2.0, -1.5, -0.5, 1.0, 2.0, 3.5, 4.0};
	double y1[9] = {-3.0, -1.0, -2.0, -0.5, 1.0, 0.0, 1.5, 1.0, 2.5};
	double k = 0.0;
	double b = 0.0;
	lesq(x1, y1, 9, &k, &b);
	printf("%f, %f\n", k, b);

	return 0;
}