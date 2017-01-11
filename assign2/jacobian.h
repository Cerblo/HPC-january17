#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void jacobian(double **OLD, double **NEW, size, TOL);
void jac_update();
double f_ij();
