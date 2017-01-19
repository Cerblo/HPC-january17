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
// 1 is added to row and column because the boundaries are not to be changed
int row = blockIdx.x * blockDim.x + threadIdx.x + 1;
int col = blockIdx.y * blockDim.y + threadIdx.y + 1;

if (row < size - 1 && col < size - 1) {
        NEW[row * size + col] = 0.25 * ( OLD[(row - 1) * size + col] + OLD[(row + 1) * size + col] + OLD[row * size + (col-1)]\
                          + OLD[row * size + (col+1)] + h * h * f[row * size + col]);
    }
}
