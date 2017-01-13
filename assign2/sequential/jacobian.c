#include <math.h>
#include <stdio.h>
#include <time.h>

#define mytimer clock
#define delta_t(a,b) (1e3 * (b - a) / CLOCKS_PER_SEC)


/* jac_update updates the matrix NEW with values calculated from OLD
   jac_update returns the summed absolute squared error */
double jac_update(double **OLD, double **NEW, double **f, int size, double h) {

  /* loop counters over matrix entries */
  int i, j;
  double err = 0;
  double delta = pow(h,2);
	double iter_time;

	clock_t t1,t2;
	t1 = mytimer();
  for (i = 1; i < size - 1; i++) {
    for (j = 1; j < size - 1; j++) {

	
      NEW[i][j] = 0.25*(OLD[i-1][j]+OLD[i+1][j]+OLD[i][j-1]\
                  +OLD[i][j+1]+delta*f[i][j]);

      err += pow(OLD[i][j] - NEW[i][j], 2);
	
    }
  }

	//t2 = mytimer();
	//iter_time = delta_t(t1,t2);
	//printf("Jac %d %f %f \n", size - 2, iter_time, 4*pow(size,2)/iter_time);



	err = 1/pow(size-2,2) * err;
	err = sqrt(err);

  return err;
}

void mat_swap(double ***A, double ***B) {
double **temp = *A;
*A = *B;
*B  = temp;
}

void jacobian(double **OLD, double **NEW, double **f, int size, double TOL, int max_it, \
              double h) {

  /* initializing iteration variables */
  int k = 1;

  /* stopping criterion is squared; this avoids square root calculation */
  
  double d = TOL + 1;

  while (d > TOL && k < max_it) {
    /* update step */
    	d = jac_update(OLD, NEW, f, size, h);
	//OLD = NEW;
    	mat_swap(&OLD, &NEW);


	printf("%i  %f\n", k, d);
	k++;
  }


}
