#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void jacobian(double **OLD, double **NEW, double **f, int size, double TOL, \
              int max_it, double h, double *errs);
double jac_update(double **OLD, double **NEW, double **f, int size, double h);
void mat_swap(double ***A, double ***B);
