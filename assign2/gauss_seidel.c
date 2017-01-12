#include <math.h>

/* copies values of B into A;
   matrices must be of same dimensions and symmetric */
double mat_copy(double **A, double **B, int size) {
  int m, n;
  for (m = 0; m < size; m++) {
    for (n = 0; n < size; n++) {
      A[i][j] = B[i][j];
    }
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


void gauss_seidel(double **OLD, double **NEW, int size, double TOL, int max_it, \
              double h) {

  /* initializing iteration variables */
  int k = 0;

  /* stopping criterion is squared; this avoids square root calculation */
  double TOL2 = pow(TOL,2);
  double d = TOL2 + 1;

  while d > TOL2 && k < max_it {
    mat_copy(OLD, NEW);
    /* update step */
    d = gauss_update(OLD, NEW, size, h);
    k++;
  }
}


/* jac_update updates the matrix NEW with values calculated from OLD
   jac_update returns the summed absolute squared error */
double gauss_update(double **OLD, double **NEW, int size, double h) {

  /* loop counters over matrix entries */
  int i, j;
  int err = 0;
  double delta = pow(h,2);

  for (i = 1; i < size-1; i++) {
    for (j = 1; j < size-1; j++) {
      NEW[i][j] = 0.25*(NEW[i-1][j]+OLD[i+1][j]+NEW[i][j-1]\
                  +OLD[i][j+1]+delta*f_ij(i, j, size))
      err += pow(abs(OLD[i][j] - NEW[i][j]), 2);
    }
  }
  return err;
}



}
