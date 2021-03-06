#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datatools.h"
#include "init.h"
#include "jacobian.h"
#include <omp.h>

int main(int argc, char **argv) {

  int size, N, max_it;
  double h, guess;
  double **u_old, **u_new, **f;

  if (argc < 3) {
  	printf("Wrong input\n");
  	return 0;
  }

  N = atoi(argv[1]);
  guess = 15;

  max_it = atoi(argv[2]);

  size = N + 2;
  h = 2.0 / (N + 1);

  u_old = malloc_2d(size, size);
  u_new = malloc_2d(size, size);
  f = malloc_2d(size, size);

  init_u(size, u_old, guess);
  init_u(size, u_new, guess);
  init_f(N, f);

  jacobian(u_old, u_new, f, size, max_it, h);

free_2d(u_old);
free_2d(u_new);
free_2d(f);
  return 0;
}
