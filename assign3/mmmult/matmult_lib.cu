
#include "alloc.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <helper_cuda.h>

extern "C" {
#include <cblas.h>
#include <omp.h>
void matmult_lib(int m, int n, int k, double* A, double* B, double* C) {

	/*Declaring matrices (as arrays)	
	  matrix A: m, k
	  matrix B: k, n
	  matrix C: m, n		 */
	
	//Number of entries or matrix size
	int A_no = m*k*sizeof(double);
	int B_no = k*n*sizeof(double);
	int C_no = m*n*sizeof(double);


	//Allocation of memory for matrices
	//alloc(h_A, h_B, h_C, d_A, d_B, d_C, A_no, B_no, C_no);

	//Initialize matrix entries to one
	//init(h_A, A_no, h_B, B_no, h_C, C_no);

	//Transfer matrix to device
	//transferToDevice(h_A, h_B, h_C, d_A, d_B, d_C, A_no, B_no, C_no);

	//Kernel function call
	//kernel_gpu1<<<1, 1>>>(m, n, k, d_A, d_B, d_C);
	
	//Transfer results from device to host
	//transferToHost(h_A, h_B, h_C, d_A, d_B, d_C, A_no, B_no, C_no);

	//Device Synchronization (and Cuda Error Check)
	//checkCudaErrors(cudaDeviceSynchronize());

	//Freeing allocated memory
	
	int alpha = 1;
        int beta =0;
	double time = omp_get_wtime();
	
	
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, \
		      m, n, k, alpha, A, k, B, n, beta, C, n);

	double elapsed = omp_get_wtime()-time;
	//printf("%5.10f\n", elapsed);

}

}
