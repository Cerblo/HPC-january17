#include <math.h>
#include <stdio.h>
#include <omp.h>


void mat_swap(double ***A, double ***B) {
  double **temp = *A;
  *A = *B;
  *B  = temp;
}

void jacobian(double **OLD, double **NEW, double **f, int size, int max_it, \
              double h) {

  /* initializing iteration variables */
  int k = 0;
  int i,j;

  #pragma omp parallel default(none) \
              shared(OLD, NEW, f, size, h, k, max_it) \
              private(i, j)
  {
  while (k < max_it) {
    #pragma omp for 
    for (i = 1; i < size - 1; i++) {
      for (j = 1; j < size - 1; j++) {
        NEW[i][j] = 0.25*(OLD[i-1][j]+OLD[i+1][j]+OLD[i][j-1]\
                          +OLD[i][j+1]+h * h * f[i][j]);
      }
    }
    #pragma omp master
    {
    mat_swap(&OLD, &NEW);
	  k++;
  } /* end pragma omp master */
    #pragma omp barrier
  }
} /* end pragma omp parallel */
}
