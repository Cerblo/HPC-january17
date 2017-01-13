#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void gauss_seidel(double **OLD, double **NEW, double **f, int size, double TOL,\
                  int max_it, double h);
