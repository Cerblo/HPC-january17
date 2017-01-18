#include <stdio.h>
#include <math.h>
#include <stdlib.h>

__global__ void jacobian(double *OLD, double *NEW, double *f, int size, \
              int max_it, double h);

__host__ void mat_swap(double **A, double **B);
