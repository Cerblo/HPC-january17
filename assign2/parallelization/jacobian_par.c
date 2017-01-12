#include "jacobian_par.h"

/* jac_update updates the matrix NEW with values calculated from OLD
   jac_update returns the summed absolute squared error */
double jac_update(double **OLD, double **NEW, double **f, int size, double h) {

  /* loop counters over matrix entries */
  int i, j;
  double err = 0;
  double delta = pow(h,2);

  #pragma collapse(2) reduction(+:err)
  for (i = 1; i < size - 1; i++) {
    for (j = 1; j < size - 1; j++) {
      NEW[i][j] = 0.25*(OLD[i-1][j]+OLD[i+1][j]+OLD[i][j-1]\
                  +OLD[i][j+1]+delta*f[i][j]);

      err += pow(OLD[i][j] - NEW[i][j], 2);
    }
  } /* end pragma collapse(2) */
  return err;
}

void mat_swap(double ***A, double ***B) {
double **temp = *A;
*A = *B;
*B  = temp;
}

void jacobian(double **OLD, double **NEW, double **f, int size, double TOL, int max_it, \
              double h, double *errs) {

  /* initializing iteration variables */
  int k = 0;

  /* stopping criterion is squared; this avoids square root calculation */
  double TOL2 = TOL * TOL;
  double d = TOL2 + 1;

  #pragma omp collapse(2)
  while (d > TOL2 && k < max_it) {
    /* update step */
    	d = jac_update(OLD, NEW, f, size, h);
    /* OLD = NEW */
    	mat_swap(&OLD, &NEW);

	printf("%i  %f\n", k, d);
	k++;
} /* end pragma collapse(2)*/
}
