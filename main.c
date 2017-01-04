#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "datatools.h"    /* helper functions */
#include "matmult_nat.h"  /* my matrix multiplication function */
#include "matmult_lib.h"  /* CBLAS matrix multiplication function */

#define NREPEAT 100	      /* repeat count for the experiment loop */
#define mytimer clock
#define delta_t(a,b) (1e3 * (b - a) / CLOCKS_PER_SEC)

int
main(int argc, char *argv[]) {

    /* Initializing variables */
    int    i, m, n, k, N = NREPEAT;
    double **A, **B, **C, **D;
    double tcpu1, tcpu2;

    clock_t t1, t2;

    for (m = 100; m <= 1000; m += 100) {
      n = m - 20;
      k = m + 20;

    	/* allocate memory for matrices */
    	A = malloc_2d(m, k);
    	B = malloc_2d(k, n);
    	C = malloc_2d(m, n);
      	D = malloc_2d(m, n);
    	if (A == NULL || B == NULL | C == NULL) {
        fprintf(stderr, "Memory allocation error...\n");
        exit(EXIT_FAILURE);
    	}
      else {
        fprintf(stderr, "Memory allocation successful.\n");
      }

    	/* initialize with useful data; last argument is reference */
      fprintf(stderr, "Matrix initialization...\n");
      init_data(m, n, k, A, B);

    	/* timings for matmult */
    	t1 = mytimer();
      fprintf(stderr, "Matmult_nat - Starting timer...\n");
    	for (i = 0; i < N; i++) {
        matmult_nat(m, n, k, A, B, C);
      }
    	t2 = mytimer();
    	tcpu1 = delta_t(t1, t2) / N;

      /* timings for CBLAS routine */
      t1 = mytimer();
      fprintf(stderr, "Matmult_lib - Starting timer...\n");
    	for (i = 0; i < N; i++) {
        matmult_lib(m, n, k, A, B, D);
      }
    	t2 = mytimer();
    	tcpu2 = delta_t(t1, t2) / N;

    	/* print n and results  */
      int dissimilarity = check_results(C, D);
    	printf("%4d %4d %8.3f %8.3f %d\n", m, n, tcpu1, tcpu2, dissimilarity);

    	/* free memory */
    	free_2d(A);
    	free_2d(B);
    	free_2d(C);
      free_2d(D);
    }

    return EXIT_SUCCESS;
}
