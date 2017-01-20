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
printf("jac 0 input - %i,%i: %f\n", row, col, d1_OLD[0 * size + col]);
        NEW[row * size + col] = 0.25 * ( d0_OLD[(row - 1) * size + col] + d1_OLD[0 * size + col] + d0_OLD[row * size + (col-1)]\
                          + d0_OLD[row * size + (col+1)] + h * h * f[row * size + col]);
}
else if (row < size/2 - 1 && col < size - 1) {
printf("jac 0 input - %i,%i: %f\n", row, col, d0_OLD[row * size + col]);
        NEW[row * size + col] = 0.25 * ( d0_OLD[(row - 1) * size + col] + d0_OLD[(row + 1) * size + col] + d0_OLD[row * size + (col-1)]\
                          + d0_OLD[row * size + (col+1)] + h * h * f[row * size + col]);
//printf("jac 0 output- %i,%i: %f\n", row, col, NEW[row * size + col]);
    }
}


__global__ void 
jacobian_1(double *d0_OLD, double *d1_OLD, double *NEW, double *f, int size, int max_it, \
              double h) {

  /* initializing iteration variables */
// 1 is added to row and column because the boundaries are not to be changed
int row = blockIdx.x * blockDim.x + threadIdx.x;
int col = blockIdx.y * blockDim.y + threadIdx.y + 1;

if (row == 0 && col < size - 1) {
printf("input jac 1 - %i,%i: %f\n", row + size/2, col, d0_OLD[(size / 2 - 2) * size + col]);
        NEW[row * size + col] = 0.25 * ( d0_OLD[(size / 2 - 1)* size + col] + d1_OLD[(row + 1) * size + col] + d1_OLD[row * size + (col-1)]\
                          + d1_OLD[row * size + (col+1)] + h * h * f[row * size + col]);
//printf("jac 1 - %i,%i: %f\n", row + size/2, col, NEW[row * size + col]);
}
else if (row < size/2 - 1 && col < size - 1) {
printf("input jac 1 - %i,%i: %f\n", row + size/2, col, d1_OLD[row * size + col]);
        NEW[row * size + col] = 0.25 * ( d1_OLD[(row - 1) * size + col] + d1_OLD[(row + 1) * size + col] + d1_OLD[row * size + (col-1)]\
                          + d1_OLD[row * size + (col+1)] + h * h * f[row * size + col]);
    }
}
