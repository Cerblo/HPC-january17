#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <helper_cuda.h>
#include "alloc.h"

extern "C" {
__global__ void kernel_gpu3(int m, int n, int k,double *A, double *B, double *C){

// 2D thread indices defining row and col of element
 	int j = blockIdx.x * blockDim.x + threadIdx.x;
 	int i = 2*(blockIdx.y * blockDim.y + threadIdx.y); //i goes from 1 out of 2 regarding lines of the matrix
	
	int l;

	if (i<m && j<n){

		for(l=0;l<k;l++){

			// 2 elements computed at the same time
			double b=B[l*n+j];

			C[i*n + j] += A[i*k+l]*b;
			C[(i+1)*n + j] += A[(i+1)*k+l]*b;

		}
	}
	 
}

void matmult_gpu3(int m, int n, int k){


/*Declaring matrices (as arrays)	
	  matrix A: m, k
	  matrix B: k, n
	  matrix C: m, n		 */

	//Number of entries or matrix size
	int A_no = m*k*sizeof(double);
	int B_no = k*n*sizeof(double);
	int C_no = m*n*sizeof(double);
	
	double h_A[A_no];
	double h_B[B_no];
	double h_C[C_no];
	double d_A[A_no];
	double d_B[B_no];
	double d_C[C_no];

	//Allocation of memory for matrices
	alloc(h_A, h_B, h_C, d_A, d_B, d_C, A_no, B_no, C_no);

	//Initialize matrix entries to one
	init(h_A, A_no, h_B, B_no, h_C, C_no);

	//Transfer matrix to device
	transferToDevice(h_A, h_B, h_C, d_A, d_B, d_C, A_no, B_no, C_no);

	 // Kernel launch
	 int K = 16; //Size of the block
 	 kernel_gpu3<<<dim3(m/(2*K),n/K), dim3(K,K)>>>(m,n,k,d_A,d_B,d_C);
	 checkCudaErrors(cudaDeviceSynchronize());
	
	//Transfer results from device to host
	transferToHost(h_A, h_B, h_C, d_A, d_B, d_C, A_no, B_no, C_no);

	//Device Synchronization (and Cuda Error Check)
	checkCudaErrors(cudaDeviceSynchronize());
	
	//Freeing allocated memory
	freeall(h_A, h_B, h_C,d_A, d_B, d_C);
}
}

