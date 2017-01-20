#include <math.h>
#include <stdio.h>


__host__ void 
mat_swap(double **A, double **B) {
  double *temp = *A;
  *A = *B;
  *B  = temp;
}

__global__ void 
jacobian_0(double *d0_OLD, double *d1_OLD, double *NEW, double *f, int size, int max_it, double h) {

int row = blockIdx.x * blockDim.x + threadIdx.x + 1;
int col = blockIdx.y * blockDim.y + threadIdx.y + 1;
if (row == size/2 - 1 && col < size - 1) {
        NEW[row * size + col] = 0.25 * ( d0_OLD[(row - 1) * size + col] + d1_OLD[0 * size + col] + d0_OLD[row * size + (col-1)]\
                          + d0_OLD[row * size + (col+1)] + h * h * f[row * size + col]);
}
if (row < size/2 - 1 && col < size - 1) {
        NEW[row * size + col] = 0.25 * ( d0_OLD[(row - 1) * size + col] + d0_OLD[(row + 1) * size + col] + d0_OLD[row * size + (col-1)]\
                          + d0_OLD[row * size + (col+1)] + h * h * f[row * size + col]);
    }
}

// Function taking care of the bottom of the matrix
__global__ void 
jacobian_1(double *d0_OLD, double *d1_OLD, double *NEW, double *f, int size, int max_it, \
              double h) {

  /* initializing iteration variables */
// This time row don't start with 1 because there is no boundaries (since it's the bottom
int row = blockIdx.x * blockDim.x + threadIdx.x;
int col = blockIdx.y * blockDim.y + threadIdx.y + 1;

// Separate the case when communicating with the other GPU is necessary
if (row == 0 && col < size - 1) {
        NEW[row * size + col] = 0.25 * ( d0_OLD[(size / 2 - 1)* size + col] + d1_OLD[(row + 1) * size + col] + d1_OLD[row * size + (col-1)]\
                          + d1_OLD[row * size + (col+1)] + h * h * f[row * size + col]);
}
else if (row < size/2 - 1 && col < size - 1) {
        NEW[row * size + col] = 0.25 * ( d1_OLD[(row - 1) * size + col] + d1_OLD[(row + 1) * size + col] + d1_OLD[row * size + (col-1)]\
                          + d1_OLD[row * size + (col+1)] + h * h * f[row * size + col]);
    }
}
