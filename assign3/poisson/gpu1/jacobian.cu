#include <math.h>
#include <stdio.h>


__host__ void 
mat_swap(double **A, double **B) {
  double *temp = *A;
  *A = *B;
  *B  = temp;
}

__global__ void 
jacobian(double *OLD, double *NEW, double *f, int size, int max_it, \
              double h) {

  /* initializing iteration variables */
  int i,j;

    for (i = 1; i < size - 1; i++) {
      for (j = 1; j < size - 1; j++) {
        NEW[i * size + j] = 0.25 * ( OLD[(i-1) * size + j] + OLD[(i+1) * size + j] + OLD[i * size + (j-1)]\
                          + OLD[i * size + (j+1)] + h * h * f[i * size + j]);
//printf("%5.2f ", NEW[i * size + j]);
      }
//printf("\n");
    }
}
