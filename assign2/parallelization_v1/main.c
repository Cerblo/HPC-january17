#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datatools.h"
#include "init.h"
#include "jacobian.h"

int main(int argc, char **argv) {

int size, N, max_it;
double h, guess,tol;
double **u_old, **u_new, **f;

if (argc < 4) {
	printf("Wrong input\n");
	return 0;
}

N = atoi(argv[1]);
guess = 15;

tol = atof(argv[3]);
max_it = atoi(argv[2]);

size = N + 2;
h = 2.0 / (N + 1);
u_old = malloc_2d(size, size);
u_new = malloc_2d(size, size);
f = malloc_2d(size, size);

init_u(size, u_old, guess);
init_u(size, u_new, guess);
init_f(N, f);

jacobian(u_old, u_new, f, size, tol, max_it, h);

return 0;
}
