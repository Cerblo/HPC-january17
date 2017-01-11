#include "datatools.h"
#include "func.h"

int
main(int argc, char **argv) {
int size;
double h = 0.01;
double **u_old, **u_new;

size = 2/h+1;
u_old = malloc_2d(size, size); 
u_new = malloc_2d(size, size); 
}
