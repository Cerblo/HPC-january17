#include <stdio.h>
#include <stdlib.h>
#include "datatools.h"
#include "init.h"
#include "jacobian.h"

int
main(int argc, char **argv) {

int size, N, max_it;
double h, guess,tol;
double **u_old, **u_new;

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

initialize(size, u_old, guess);
printf("\nh value: %f\n", h);
jacobian(u_old, u_new, size, tol, max_it, h);
disp_2d(size, size, u_old);
return 0;
}
