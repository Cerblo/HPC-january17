#include <stdio.h>
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))


void matmult_blk(int m, int nb1, int n, int nb2, int k, int nb3, double **A, double **B, double **C){

	int i,ib,j,jb,l,lb,count;
	count =0;
	printf("Parameters : %d %d %d %d %d %d\n", m,n,k,nb1,nb2,nb3);
	

	for ( i = 0; i < m; i++ ) {
    		for ( j = 0; j < n; j++ ) {
      			C[i][j] = 0;
    	}
  	}


		for (ib=0; ib<m; ib++){

			for (jb=0;jb<n; jb ++){

				for (i=ib;i<MIN(m-ib,nb1);i++){

					for (j=jb;j<MIN(n-jb,nb2);j++){

						for (lb=0; lb<k; lb++){
	
							for (l=lb;l<MIN(k-lb,nb3);l++){

	
								printf("%d %d %d %d %d %d \n",ib,i,jb,j,lb,l);

								C[i+ib][j+jb] += A[i+ib][l+lb]*B[l+lb][j+jb];
								count++;
							}
						}
					}
				}
			}
		}

	printf("\nCount : %d\n",count);
}




