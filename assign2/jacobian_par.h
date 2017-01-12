#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void jacobian_par(double **OLD, double **NEW, double **f, int size, double TOL,
                  int max_it, double h);
double f_ij(int i, int j, int N);
double jac_update(double **OLD, double **NEW, double **f, int size, double h);
void mat_copy(double **A, double **B, int size);
