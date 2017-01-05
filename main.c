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
    int    i, j, m, n, k, N = NREPEAT;
    double **A, **B, **C, **D, **E;
    double tcpu1, tcpu2, tcpu3;

    clock_t t1, t2;

    for (m = 10; m <= 10; m += 10) {
      n = m - 2;
      k = m + 2;


    	/* allocate memory for matrices */
    	A = malloc_2d(m, k);
    	B = malloc_2d(k, n);
    	C = malloc_2d(m, n); // Result for matmultlib
      	D = malloc_2d(m, n); // Result for matmultnat
	E = malloc_2d(m, n); // Result for matmultblk

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

	/* timings for Blocking method */
	t1 = mytimer();
	fprintf(stderr, "Matmult_blk - Starting timer...\n");
    	for (i = 0; i < 1; i++) {
        matmult_blk(m, (int) m/5 ,n, (int) m/5, k, (int) m/5, A, B, E);
      }
    	t2 = mytimer();
    	tcpu3 = delta_t(t1, t2) / N;

    	/* print n and results  */
      /*int dissimilarity = check_results(m, n, C, D);
	fprintf(stderr, "Checking results for matmult_nat");
    	printf("%4d %4d %8.3f %8.3f %d\n", m, n, tcpu1, tcpu2, dissimilarity);*/


      int dissimilarity2 = check_results(m, n, E, D);
	fprintf(stderr, "Checking results for matmult_blk\n");

	for (i=0;i<m;i++){
	for (j=0;j<k;j++){
	printf("%f ",A[i][j]);}printf("\n");}printf("\n");

	for (i=0;i<k;i++){
	for (j=0;j<n;j++){
	printf("%f ",B[i][j]);}printf("\n");}printf("\n");

	for (i=0;i<m;i++){
	for (j=0;j<n;j++){
	printf("%f ",E[i][j]);}printf("\n");}printf("\n");

	for (i=0;i<m;i++){
	for (j=0;j<n;j++){
	printf("%f ",D[i][j]);}printf("\n");}

    	printf("%4d %4d %8.3f %8.3f %d\n", m, n, tcpu3, tcpu2, dissimilarity2);	

    	/* free memory */
    	free_2d(A);
    	free_2d(B);
    	free_2d(C);
      	free_2d(D);
	free_2d(E);
    }

    return EXIT_SUCCESS;
}
