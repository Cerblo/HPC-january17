#include <stdio.h>
#include <stdlib.h>
#include "datatools.h"
#include "func.h"

int
main(int argc, char **argv) {

if (argc != 2) {
	printf("Wrong input\n");
	return 0;
}

int size;
double h = atof(argv[1]);
double **u_old, **u_new;

size = 2/h+1;
u_old = malloc_2d(size, size); 
u_new = malloc_2d(size, size); 

initialize(size, u_old);
printf("Done\n");
return 0;
}
