#include <math.h>
#include <stdio.h>
#include <time.h>
#include "datatools.h"

#define mytimer clock
#define delta_t(a,b) (1e3 * (b - a) / CLOCKS_PER_SEC)


/* gauss_update updates the grid matrix;
   gauss_update returns the summed absolute squared error */
double gauss_update(double **NEW, double **f, int size, double h) {

  /* variable and timer declaration */
  int i, j;
  double err = 0;
  double delta = pow(h,2);
	double temp ;
	double iter_time;
	clock_t t1,t2;
//	t1 = mytimer();

  /* looping through inner grid and updating grid points */
  for (i = 1; i < size - 1; i++) {
    for (j = 1; j < size - 1; j++) {
      temp = NEW[i][j];
      NEW[i][j] = 0.25*(NEW[i-1][j]+NEW[i+1][j]+NEW[i][j-1]\
                  +NEW[i][j+1]+delta*f[i][j]);
      err += pow(temp - NEW[i][j], 2);
    }
  }

//	t2 = mytimer();
//	iter_time = delta_t(t1,t2);
//	printf("Gau %d %f %f \n", size -2 , iter_time, 4*pow(size,2)/iter_time);

  /* error calculation */
  err = 1/pow(size-2,2) * err;
	err = sqrt(err) ;

  return err;
}


void gauss_seidel(double **OLD, double **NEW, double **f, int size, double TOL, int max_it, \
              double h) {

  /* initializing iteration variables */
  int k = 1;
  double d = TOL + 1;

  while (d > TOL && k < max_it) {
    /* update step */
    d = gauss_update(NEW, f, size, h);

    printf("%i  %5.10f\n", k, d);
    k++;
  }
}
