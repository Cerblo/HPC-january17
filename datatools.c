/* datatools.c - support functions for the matrix examples
 *
 * Author:  Bernd Dammann, DTU Compute
 * Version: $Revision: 1.2 $ $Date: 2015/11/10 11:03:12 $
 */
#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <math.h>

#include "datatools.h"

void
init_data (int m, int n, int k, double **A, double **B ) {
   int i, j, l;

   for ( i = 0; i < m; i++ ) {
    for ( j = 0; j < n; j++ ) {
      for ( l = 0; l < k; l++ ) {
        A[i][l] = 1.0;
        B[l][j] = 2.0;
      }
    }
  }
}

/* Routine for allocating two-dimensional array */
double **
malloc_2d(int m, int n) {
  int i;

  if (m <= 0 || n <= 0)
    return NULL;

  double **A = malloc(m * sizeof(double *));
  if (A == NULL)
    return NULL;

  A[0] = malloc(m*n*sizeof(double));
  if (A[0] == NULL) {
    free(A);
    return NULL;
  }
  for (i = 1; i < m; i++)
	  A[i] = A[0] + i * n;

  return A;
}

/* Routine for freeing space allocated to array */
void
free_2d(double **A) {
  free(A[0]);
  free(A);
}
