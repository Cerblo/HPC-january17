#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void jacobian(double **OLD, double **NEW, double **f, int size, double TOL, int max_it, \
              double h, double *errs);
