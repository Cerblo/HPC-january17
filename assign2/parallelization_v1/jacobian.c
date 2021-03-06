#include <math.h>
#include <stdio.h>
#include <omp.h>


/* jac_update updates the matrix NEW with values calculated from OLD
   jac_update returns the summed absolute squared error */
double jac_update(double **OLD, double **NEW, double **f, int size, double h) {

  /* loop counters over matrix entries */
  int i, j;
  double err = 0;
  double delta = pow(h,2);

  #pragma omp parallel for default(none) shared(NEW, OLD, f, delta, size) \
	                         private(i, j) reduction(+:err)
  for (i = 1; i < size - 1; i++) {
    for (j = 1; j < size - 1; j++) {
      NEW[i][j] = 0.25*(OLD[i-1][j]+OLD[i+1][j]+OLD[i][j-1]\
                  +OLD[i][j+1]+delta*f[i][j]);

      err += pow(OLD[i][j] - NEW[i][j], 2);
    }
  }
	err = 1/pow(size-2,2) * err;
	err = sqrt(err);
  return err;
}

void mat_swap(double ***A, double ***B) {
  double **temp = *A;
  *A = *B;
  *B  = temp;
}

void jacobian(double **OLD, double **NEW, double **f, int size, double TOL, int max_it, \
              double h) {
  /* initializing iteration variables */
  int k = 0;
  double d = TOL + 1;
  while (d > TOL && k < max_it) {
    	d = jac_update(OLD, NEW, f, size, h);
    	mat_swap(&OLD, &NEW);
	k++;
  }
//printf("%i  %f\n", k, d);
}
