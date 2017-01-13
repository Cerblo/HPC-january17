#include <math.h>
#include <stdio.h>
#include <omp.h>


void mat_swap(double ***A, double ***B) {
  double **temp = *A;
  *A = *B;
  *B  = temp;
}

void jacobian(double **OLD, double **NEW, double **f, int size, double TOL, int max_it, \
              double h) {

  /* initializing iteration variables */
  int k = 0;
  int i,j;
  double err;
  double d = TOL + 1;

  #pragma omp parallel default(none) \
              shared(OLD, NEW, f, size, h,d, k, TOL, max_it, err) \
              private(i, j)
  {
  while (d > TOL && k < max_it) {
    err = 0;
    #pragma omp for reduction(+:err)
    for (i = 1; i < size - 1; i++) {
      for (j = 1; j < size - 1; j++) {
        NEW[i][j] = 0.25*(OLD[i-1][j]+OLD[i+1][j]+OLD[i][j-1]\
                          +OLD[i][j+1]+h * h * f[i][j]);
        err += pow(OLD[i][j] - NEW[i][j], 2);
      }
    }
    d = 1./(size-2) * sqrt(err);
    #pragma omp master
    {
    mat_swap(&OLD, &NEW);
	  k++;
  } /* end pragma omp master */
    #pragma omp barrier
  }
} /* end pragma omp parallel */
printf("%i  %f\n", k, d);
}
