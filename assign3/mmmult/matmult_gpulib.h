#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <helper_cuda.h>
#include "alloc.h"

void matmult_gpulib(int m, int n, int k, double* A, double* B, double* C);
