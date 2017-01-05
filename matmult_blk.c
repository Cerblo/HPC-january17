#include <stdio.h>
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))


void matmult_blk(int m, int nb1, int n, int nb2, int k, int nb3, double **A, double **B, double **C){
	int i,ib,j,jb,l,lb;

	for ( i = 0; i < m; i++ ) {
    		for ( j = 0; j < n; j++ ) {
      			C[i][j] = 0;
    	}
  	}
	

	for (ib=0; ib<m; ib+=nb1){printf("loop 1\n");
	for (jb=0;jb<n;j+=nb2){printf("loop 2\n");
	for (i=ib;i<MIN(m-ib,nb1);i++){printf("loop 3\n");
	for (j=jb;j<MIN(n-jb,nb2);j++){printf("loop 4\n");
	for (lb=0; lb<k; lb+=nb3){printf("loop 5\n");
	for (l=lb; l<MIN(k-lb,nb3);l++){printf("loop 6\n");

        		C[i+ib][j+jb] += A[i+ib][l+lb]*B[l+lb][j+jb];

	}}}}}}

	

}




