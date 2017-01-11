#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void jacobian(double **OLD, double **NEW, int size, double TOL, int max_it);
void jac_update(double **OLD, double **NEW, int size, double h);
double f_ij(int i, int j, int size, double h);
