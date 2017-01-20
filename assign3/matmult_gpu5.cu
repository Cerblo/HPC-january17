#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <helper_cuda.h>
#include "alloc.h"

#define BLOCK_SIZE 16

extern "C" {

__global__ void kernel_gpu5(int m, int n, int k, double *A, double *B, double *C) {
	
	// Block rows and columns
	int blockRow = blockIdx.y;
	int blockCol = blockIdx.x;

	// Thread rows and columns within Block
    	int row = threadIdx.y;
    	int col = threadIdx.x;

	double cbuffer = 0;
	
	__shared__ double a[BLOCK_SIZE][BLOCK_SIZE];
        __shared__ double b[BLOCK_SIZE][BLOCK_SIZE];

	// Loop over sub-matrices A and B that are required to compute block
	int l_matrices = k/BLOCK_SIZE; 	// number of sub-matrices along
	int l; 			 	// iteration variable
	for (l = 0; l<l_matrices; l++) {
		
		// Load sub-matrices A and B into shared memory
		a[row][col] = A[row*k + col + l*BLOCK_SIZE + k*BLOCK_SIZE*blockCol];
		b[row][col] = B[row*n + col + l*BLOCK_SIZE*n + blockRow*n*BLOCK_SIZE];
		// Synchronize to make sure the sub-matrices are loaded
        	__syncthreads();

		// Multiply submatrices A and B together
		int count;
		for (count = 0; count<BLOCK_SIZE; count++) {
			cbuffer += a[row][count]*b[count][col];
		}
		// Sync before moving on to new submatrices
        	__syncthreads();
	}
	// each thread writes its result to matrix
	// alternatively, 
	C[row*n + col + blockRow*n + blockCol] = cbuffer; 
}


void matmult_gpu5(int m, int n, int k, double* A, double* B, double* C){

/*Declaring matrices (as arrays)	
	  matrix A: m, k
	  matrix B: k, n
	  matrix C: m, n		 */
	
	//Number of entries or matrix size
	int A_no = m*k*sizeof(double);
	int B_no = k*n*sizeof(double);
	int C_no = m*n*sizeof(double);

	double* d_A; 
	double* d_B; 
	double* d_C;
	

	//Allocation of memory for matrices
	alloc(&d_A, &d_B, &d_C, A_no, B_no, C_no);

	//Initialize matrix entries to one
	//init(h_A, A_no, h_B, B_no, h_C, C_no);

	//Transfer matrix to device
	transferToDevice(A, B, C, d_A, d_B, d_C, A_no, B_no, C_no);

	// Kernel launch
	int K = BLOCK_SIZE; //Size of the block
	dim3 dimgrid(ceil((double) m/K), ceil((double) n/K));
	dim3 dimblock(K,K);
 	kernel_gpu5<<<dimgrid, dimblock>>>(m,n,k,d_A,d_B,d_C);
	
	//Device Synchronization (and Cuda Error Check)
	//checkCudaErrors(cudaDeviceSynchronize());
	cudaDeviceSynchronize();
	
	//Transfer results from device to host
	transferToHost(A, B, C, d_A, d_B, d_C, A_no, B_no, C_no);
	
	/*int i, j;
	for (i=0;i<m;i++){
	for (j=0;j<n;j++){
	printf("%f ", C[i*n + j]);
	}printf("\n");}printf("\n");*/

	//Freeing allocated memory
	freeall(d_A, d_B, d_C);
}
}

