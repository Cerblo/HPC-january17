#include <stdio.h>
#include <stdlib.h>
#include "datatools.h"
#include "init.h"
#include "jacobian.h"
#include "gauss_seidel.h"

int
main(int argc, char **argv) {

int size, N, max_it;
double h, guess,tol;
double **u_old, **u_new, **f;

if (argc < 2) {
	printf("Wrong input\n");
	return 0;
}

// To get more precise results it is better to take 
// either N large or N+1 divisible by 6
N = atoi(argv[1]);
guess = 15;
tol = 10;
max_it = 10000;

size = N + 2;
h = 2.0 / (N + 1);
u_old = malloc_2d(size, size); 
u_new = malloc_2d(size, size); 
f = malloc_2d(size, size); 

init_u(size, u_old, guess);
init_u(size, u_new, guess);
init_f(N, f);
//disp_2d(size, size, f);
//printf("\nh value: %f\n", h);
gauss_seidel(u_old, u_new, f, size, tol, max_it, h);
disp_2d(size, size, u_new);
return 0;
}
