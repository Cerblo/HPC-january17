#include <stdio.h>
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))


void matmult_blk(int m, int n, int k, int nb, double **A, double **B, double **C){

	int i,ib,j,jb,l,lb,count, lim_row, lim_col, lim_k;



	for ( i = 0; i < m; i++ ) {
    		for ( j = 0; j < n; j++ ) {
      			C[i][j] = 0;
    	}
  	}


		for (ib=0; ib<m; ib+=nb){
			lim_row = MIN(m-ib,nb);
			for (jb=0;jb<n; jb+=nb){	
				lim_col = MIN(n-jb,nb);
				for (i=0;i<lim_row;i++){

					for (j=0;j<lim_col;j++){

						for (lb=0; lb<k; lb+=nb){
							lim_k = MIN(k-lb,nb);
							for (l=0;l<lim_k;l++){

	

								C[i+ib][j+jb] += A[i+ib][l+lb]*B[l+lb][j+jb];
									
							}
						}
					}
				}
			}
		}


}




