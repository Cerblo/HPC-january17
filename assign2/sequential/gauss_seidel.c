#include <math.h>
#include <stdio.h>
<<<<<<< HEAD
#include <time.h>

#define mytimer clock
#define delta_t(a,b) (1e3 * (b - a) / CLOCKS_PER_SEC)

/* f_ij returns the value of the function for the respective coordinates */
double f_ij_gauss(int i, int j, int N) {
  /* relation between indexes and position in the square */
  double x = ((2*(double) i)/((double)N+1)) - 1;
  double y = ((2*(double) j)/((double)N+1)) - 1;

  if (x>=0. && x<=1./3. && y<=-1./3. && y>=-2./3.) {
  	return (double)200;
  }
  else {
  	return (double)0;
  }
}

=======
#include "datatools.h"
>>>>>>> 4845ef154d382050836f441733db89e61ca2167b

/* jac_update updates the matrix NEW with values calculated from OLD
   jac_update returns the summed absolute squared error */
double gauss_update(double **NEW, double **f, int size, double h) {

  /* loop counters over matrix entries */
  int i, j;
  double err = 0;
  double delta = pow(h,2);
	double temp ;  
	double iter_time;
	clock_t t1,t2;
	t1 = mytimer();

//disp_2d(size, size, NEW);
  for (i = 1; i < size - 1; i++) {
    for (j = 1; j < size - 1; j++) {

	temp = NEW[i][j];
      NEW[i][j] = 0.25*(NEW[i-1][j]+NEW[i+1][j]+NEW[i][j-1]\
                  +NEW[i][j+1]+delta*f[i][j]);

      err += pow(temp - NEW[i][j], 2);
    }
  }


	t2 = mytimer();
	iter_time = delta_t(t1,t2);
	printf("Gau %d %f %f \n", size -2 , iter_time, 4*pow(size,2)/iter_time);
	err = 1/pow(size-2,2) * err;
	err = sqrt(err) ;

  return err;
}




void gauss_seidel(double **OLD, double **NEW, double **f, int size, double TOL, int max_it, \
              double h) {

  /* initializing iteration variables */
  int k = 1;

  /* stopping criterion is squared; this avoids square root calculation */
 
  double d = TOL + 1;

  while (d > TOL && k < 5) {
    /* update step */
    d = gauss_update(NEW, f, size, h);

    //printf("%i  %f\n", k, d);
    k++;
  }
}
