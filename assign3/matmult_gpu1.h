#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <helper_cuda.h>
#include "alloc.h"

extern "C" {
void matmult_gpu1(int m, int n, int k, double** A, double** B, double** C);
}
