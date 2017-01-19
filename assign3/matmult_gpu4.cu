#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <helper_cuda.h>
#include "alloc.h"

extern "C" {
__global__ void kernel_gpu4(int m, int n, int k,double *A, double *B, double *C){

// 2D thread indices defining row and col of element
 	int j = blockIdx.x * blockDim.x + threadIdx.x;
 	int i = blockIdx.y * blockDim.y + threadIdx.y; //i goes from 1 out of 2 regarding lines of the matrix
	
	int l;

	if ((2*i)<m && (2*j)<n){
		C[2*i*n + 2*j]=0;
		C[(2*i+1)*n + 2*j]=0;
		C[2*i*n + 2*j+1]=0;
		C[(2*i+1)*n + 2*j+1]=0;

		for(l=0;l<k;l++){

			// 2 elements computed at the same time
			double a1=A[(2*i)*k +l];
			double a2=A[(2*i+1)*k + l];
			double b1=B[l*n+2*j];
			double b2=B[l*n+2*j+1];
			
			C[2*i*n + 2*j] += a1*b1;
			C[(2*i+1)*n + 2*j] += a2*b1;
			C[2*i*n + 2*j+1] += a1*b2;
			C[(2*i+1)*n + 2*j+1] += a2*b2;

		}
	}
	 
}

void matmult_gpu4(int m, int n, int k, double* A, double* B, double* C){


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
	transferToDevice(A, B,C, d_A, d_B, d_C, A_no, B_no, C_no);

	 // Kernel launch
	 int K = 16; //Size of the block
	dim3 dimgrid(ceil((double) n/K), ceil((double) m/K));
	dim3 dimblock(K/2,K/2);

	//printf("%f %f\n", ceil((double) m/(2*K)),ceil((double) n/K));
 	 kernel_gpu4<<<dimgrid, dimblock>>>(m,n,k,d_A,d_B,d_C);
	checkCudaErrors(cudaDeviceSynchronize());
	
	//Transfer results from device to host
	transferToHost(A, B, C, d_A, d_B, d_C, A_no, B_no, C_no);

	//Device Synchronization (and Cuda Error Check)
//	checkCudaErrors(cudaDeviceSynchronize());
	
	//Freeing allocated memory
	freeall(d_A, d_B, d_C);
}
}

