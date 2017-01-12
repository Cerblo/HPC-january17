#include "jacobian_par.h"


void jacobian(double **OLD, double **NEW, double **f, int size, double TOL,
              int max_it, double h) {

  /* initializing iteration variables */
  int k = 0;

  /* stopping criterion is squared; this avoids square root calculation */
  double TOL2 = TOL * TOL;
  double d = TOL2 + 1;

  while (d > TOL2 && k < max_it) {
    /* update step */
    d = jac_update(OLD, NEW, f, size, h);
    mat_copy(OLD, NEW, size);
    k++;
  }
}


/* jac_update updates the matrix NEW with values calculated from OLD
   jac_update returns the summed absolute squared error */
double jac_update(double **OLD, double **NEW, double **f, int size, double h) {

  /* loop counters over matrix entries */
  int i, j;
  double err = 0;
  double delta = pow(h,2);

  #pragma omp collapse(2) reduction(+:err) default(none) \
              shared(OLD, NEW, f) \
              private(i, j, size, delta, err)
  /* OPTIMIZATION BY DRAGGING ERR OUT? SEE SLIDES;
     MAYBE NOWAIT IN ABOVE PRAGMA */
  for (i = 1; i < size - 1; i++) {
    for (j = 1; j < size - 1; j++) {
      NEW[i][j] = 0.25*(OLD[i-1][j]+OLD[i+1][j]+OLD[i][j-1]\
                  +OLD[i][j+1]+delta*f[i][j]);
      err += pow(abs(OLD[i][j] - NEW[i][j]), 2);
    }
  } /* pragma omp collapse(2) end */
  return err;
}


/* copies values of B into A;
   matrices must be of same dimensions and symmetric */
void mat_copy(double **A, double **B, int size) {
  int i, j;

  #pragma omp collapse(2) default(none) shared(A, B) private(i, j)
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      A[i][j] = B[i][j];
    }
  } /* pragma omp collapse(2) end */
}


/* f_ij returns the value of the function for the respective coordinates */
double f_ij(int i, int j, int N) {
  /* relation between indexes and position in the square */
  double x = ((2*(double)i)/((double)N+1)) - 1;
  double y = ((2*(double)j)/((double)N+1)) - 1;

  if (x>=0. && x<=1./3. && y<=-1./3. && y>=-2./3.) {
  	return (double)200;
  }
  else {
  	return (double)0;
  }
}
