#include <math.h>
#include <stdio.h>
#include "datatools.h"

/* jac_update updates the matrix NEW with values calculated from OLD
   jac_update returns the summed absolute squared error */
double gauss_update(double **NEW, double **f, int size, double h) {

  /* loop counters over matrix entries */
  int i, j;
  double err = 0;
  double delta = pow(h,2);
	double temp ;  

//disp_2d(size, size, NEW);
  for (i = 1; i < size - 1; i++) {
    for (j = 1; j < size - 1; j++) {
	temp = NEW[i][j];
      NEW[i][j] = 0.25*(NEW[i-1][j]+NEW[i+1][j]+NEW[i][j-1]\
                  +NEW[i][j+1]+delta*f[i][j]);

      err += pow(temp - NEW[i][j], 2);
    }
  }
	err = 1./(size-2) * sqrt(err);
  return err;
}




void gauss_seidel(double **OLD, double **NEW, double **f, int size, double TOL, int max_it, \
              double h) {

  /* initializing iteration variables */
  int k = 1;

  /* stopping criterion is squared; this avoids square root calculation */
 
  double d = TOL + 1;

  while (d > TOL && k < max_it) {
    /* update step */
    d = gauss_update(NEW, f, size, h);

    printf("%i  %f\n", k, d);
    k++;
  }
}
