#include <stdio.h>
#include <stdlib.h>
#include "datatools.h"
#include "init.h"

int
main(int argc, char **argv) {

int size, N;
double h, guess;
double **u_old, **u_new;

if (argc != 2) {
	printf("Wrong input\n");
	return 0;
}

N = atoi(argv[1]);
if ((N+1) % 6 != 0) {
	printf("N + 1 has to be divisible by 6");
	return 0;
}
guess = 15;

size = N + 2;
h = 2.0 / (N + 1);
u_old = malloc_2d(size, size); 
u_new = malloc_2d(size, size); 

initialize(size, u_old, guess);
disp_2d(size, size, u_old);
printf("\nh value: %f\n", h);
return 0;
}
