#include <stdio.h>



void matmult_blk(int m, int nb1, int n, int nb2, int k, int nb3, double **A, double **B, double **C){


	for ( i = 0; i < m; i++ ) {
    		for ( j = 0; j < n; j++ ) {
      			C[i][j] = 0;
    	}
  	}
	int i,ib,j,jb,l,lb;

	for (ib=0; ib<m; ib+=nb1){
	for (jb=0;jb<n;j+=nb2){
	for (i=ib;i<min(m-ib,nb1);i++){
	for (j=jb;j<min(n-jb,nb2);j++){
	for (lb=0; lb<k; lb+=nb3){
	for (l=lb; l<min(k-lb,nb3),l++){

        		C[i+ib][j+jb] += A[i+ib][l+lb]*B[l+lb][j+jb];

	}}}}}}

	

}



main ( int argc, char *argv[] )   {
	
	printf("Starting my job...\n\n");
	int a;

	int m,n,k,i,j;
	double alpha, beta;
	double **A, **B, **C;

	A = (double **) malloc( m*k*sizeof( double ) );
	B = (double **) malloc( k*n*sizeof( double ) );
	C = (double **) malloc( m*n*sizeof( double ) );
	
	matmult_blk(m,m/2,n,n/4,k,k/3,A,B,C);

	printf("\nDone with my job.\n");
        
}



