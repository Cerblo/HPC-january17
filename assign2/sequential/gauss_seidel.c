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
double gauss_update(double **NEW, double **f, int size, double h) {

  /* loop counters over matrix entries */
  int i, j;
  double err = 0;
  double delta = pow(h,2);
	double temp ;  

  for (i = 1; i < size - 1; i++) {
    for (j = 1; j < size - 1; j++) {
	temp = NEW[i][j];
      NEW[i][j] = 0.25*(NEW[i-1][j]+NEW[i+1][j]+NEW[i][j-1]\
                  +NEW[i][j+1]+delta*f[i][j]);

      err += pow(temp - NEW[i][j], 2);
    }
  }
	err = 1/pow(size-2,2) * err;
	err = sqrt(err) ;
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
 
  double d = TOL + 1;

  while (d > TOL && k < max_it) {
    /* update step */
    d = gauss_update(NEW, f, size, h);

    printf("%i  %f\n", k, d);
    k++;
  }
}
