/* datatools.h - support functions for the matrix examples
 *
 * Author:  Bernd Dammann, DTU Compute
 * Version: $Revision: 1.1 $ $Date: 2015/11/10 11:01:43 $
 */
#ifndef __DATATOOLS_H
#define __DATATOOLS_H

void init_data (int m, 		/* number of rows of A    */
                int n, 		/* number of columns of B */
                int k,    /* number of columns of A = number of rows of B */
		double **A, 	/* two-dim array of size m-by-n */
		double **B  	/* two-dim array of size m-by-n */
               );

int check_results(double **C, double **D);


double ** malloc_2d(int m, 	/* number of rows          */
                    int n	  /* number of columns       */
		   );

void free_2d(double **A);       /* free data allocated by malloc_2d */
#endif
