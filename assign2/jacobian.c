#include jacobian.h

void jacobian(double **OLD, double **NEW, int size, double TOL) {

  /* initializing iteration variables */
  int k = 0;
  int max_it = 1000000;

  while d > TOL && k < max_it {
    OLD = NEW;
    /* update step */
    OLD = jac_update(OLD, NEW, TOL);
    d =
    k++;
  }
}

void jac_update(double **OLD, double **NEW, int size, double h) {
  /* loop counters over matrix entries */
  int i, j;

  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      NEW = 0.25*(OLD[i-1][j]+OLD[i+1][j]+OLD[i][j-1]+OLD[i][j+1]+\
                  pow(h,2)*f_ij(i, j, h))
    }
  }
}

double f_ij(int i, int j, double h) {


  return f
}
