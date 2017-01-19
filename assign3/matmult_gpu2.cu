#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <helper_cuda.h>
#include "alloc.h"

extern "C" {

__global__ void kernel_gpu2(int m, int n, int k, double *A, double *B, double *C){

// 2D thread indices defining row and col of element
 	int j = blockIdx.x * blockDim.x + threadIdx.x;
 	int i = blockIdx.y * blockDim.y + threadIdx.y; 
	
	int l;
	
	
	if (i<m && j<n){
		C[i*n + j] = 0;
		for(l=0;l<k;l++){
			
			C[i*n+j] += A[i*k+l]*B[l*n+j];

		}
	}
	 
}

void matmult_gpu2(int m, int n, int k, double* A, double* B, double* C){


/*Declaring matrices (as arrays)	
	  matrix A: m, k
	  matrix B: k, n
	  matrix C: m, n		 */
	
	//Number of entries or matrix size
	int A_no = m*k*sizeof(double);
	int B_no = k*n*sizeof(double);
	int C_no = m*n*sizeof(double);
	int i;int j;

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
	 int K = 16; //Size of the block
	dim3 dimgrid(ceil((double) m/K), ceil((double) n/K));
	dim3 dimblock(K,K);
 	 kernel_gpu2<<<dimgrid, dimblock>>>(m,n,k,d_A,d_B,d_C);
	cudaDeviceSynchronize();
	
	//Transfer results from device to host

	transferToHost(A, B, C, d_A, d_B, d_C, A_no, B_no, C_no);
	

	//Device Synchronization (and Cuda Error Check)
	//checkCudaErrors(cudaDeviceSynchronize());
	
	/*for (i=0;i<m;i++){
	for (j=0;j<n;j++){
	printf("%f ", C[i*n + j]);
	}printf("\n");}printf("\n");*/
	//Freeing allocated memory
	freeall(d_A, d_B, d_C);
}
}

