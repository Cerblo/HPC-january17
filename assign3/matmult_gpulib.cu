
#include "alloc.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <helper_cuda.h>

#include "cublas_v2.h"

extern "C" {


void matmult_gpulib(int m, int n, int k, double* A, double* B, double* C) {

	int A_no = m*k*sizeof(double);
	int B_no = k*n*sizeof(double);
	int C_no = m*n*sizeof(double);
	

	double* d_A; 
	double* d_B; 
	double* d_C;
	int i; int j;

	/*for (i=0;i<m;i++){
	for (j=0;j<n;j++){
	printf("%f ", C[i*n + j]);
	}printf("\n");}printf("\n");*/

	//Allocation of memory for matrices

	alloc(&d_A, &d_B, &d_C, A_no, B_no, C_no);

	//Initialize matrix entries to one
	//init(h_A, A_no, h_B, B_no, h_C, C_no);

	//Transfer matrix to device 	
	transferToDevice(A, B, C, d_A, d_B, d_C, A_no, B_no, C_no);

 	//kernel_gpulib<<<dimgrid, dimblock>>>(m,n,k,d_A,d_B,d_C);
	
	

	const double alf = 1;
	const double bet = 0;
	const double *alpha = &alf;
	const double *beta = &bet;

	// Create a handle for CUBLAS
	cublasHandle_t handle;
	cublasCreate(&handle);

	// Column major -> leading dimensions of A B C change

	cublasDgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N, n, m, k, alpha, d_B, n, d_A, k, beta, d_C,n);
	
	//checkCudaErrors(cudaDeviceSynchronize());
	//Transfer results from device to host
	transferToHost(A, B, C, d_A, d_B, d_C, A_no, B_no, C_no);

	//Device Synchronization (and Cuda Error Check)
//	checkCudaErrors(cudaDeviceSynchronize());
	
	//Freeing allocated memory
	freeall(d_A, d_B, d_C);
	/*Declaring matrices (as arrays)	
	  matrix A: m, k
	  matrix B: k, n
	  matrix C: m, n		 */
	
	
	

}

}
