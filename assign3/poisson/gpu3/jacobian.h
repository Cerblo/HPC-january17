#include <stdio.h>
#include <math.h>
#include <stdlib.h>

__global__ void jacobian_0(double *d0_OLD, double *d1_OLD, double *NEW, double *f, int size, \
              int max_it, double h);

__host__ void mat_swap(double **A, double **B);

__global__ void jacobian_1(double *d0_OLD, double *d1_OLD, double *NEW, double *f, int size, \
              int max_it, double h);
