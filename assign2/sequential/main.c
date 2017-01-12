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

if (argc < 3 || (strcmp(argv[1],"jac") != 0 && strcmp(argv[1],"gau") != 0)) {
	printf("Wrong input\n");
	return 0;
}

N = atoi(argv[2]);
guess = 16;
tol = 1;
max_it = 1000;

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

if (strcmp(argv[1],"jac") == 0){


	jacobian(u_old, u_new, f, size, tol, max_it, h);


}
else{

	gauss_seidel(u_old, u_new, f, size, tol, max_it, h);}
//disp_2d(size, size, u_new);
return 0;
}
