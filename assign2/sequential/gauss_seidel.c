#include <math.h>

/* f_ij returns the value of the function for the respective coordinates */
double f_ij_gauss(int i, int j, int N) {
  /* relation between indexes and position in the square */
  double x = ((2*(double) i)/((double)N+1)) - 1;
  double y = ((2*(double) j)/((double)N+1)) - 1;

  if (x>=0. && x<=1./3. && y<=-1./3. && y>=-2./3.) {
  	return (double)200;
  }
  else {
  	return (double)0;
  }
}


/* jac_update updates the matrix NEW with values calculated from OLD
   jac_update returns the summed absolute squared error */
double gauss_update(double **OLD, double **NEW, double **f, int size, double h) {

  /* loop counters over matrix entries */
  int i, j;
  double err = 0;
  double delta = pow(h,2);

  for (i = 1; i < size - 1; i++) {
    for (j = 1; j < size - 1; j++) {
      NEW[i][j] = 0.25*(NEW[i-1][j]+OLD[i+1][j]+NEW[i][j-1]\
                  +OLD[i][j+1]+delta*f[i][j]);
      err += pow(OLD[i][j] - NEW[i][j], 2);
    }
  }
  return err;
}




/* copies values of B into A;
   matrices must be of same dimensions and symmetric */
void mat_copy_gauss(double **A, double **B, int size) {
  int i, j;
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      A[i][j] = B[i][j];
    }
  }
}

void gauss_seidel(double **OLD, double **NEW, double **f, int size, double TOL, int max_it, \
              double h) {

  /* initializing iteration variables */
  int k = 0;

  /* stopping criterion is squared; this avoids square root calculation */
  double TOL2 = TOL * TOL;
  double d = TOL2 + 1;

  while (d > TOL2 && k < max_it) {
    /* update step */
    d = gauss_update(OLD, NEW, f, size, h);
    mat_copy_gauss(OLD, NEW,size);
    printf("\n\n%i  %f\n", k, d);
    k++;
  }
}