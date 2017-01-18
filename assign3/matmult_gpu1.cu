#include "matmult_gpu1.h" 

extern "C" {

__global__ void kernel_gpu1(int m, int n, int k, double* A, double* B, double* C) {
	int i, j, l;
	for ( i = 0; i < m; i++ ) {
		for ( j = 0; j < n; j++ ) {
			for ( l = 0; l < k; l++) {
				C[i*n+j] += A[i*k+l]*B[l*n+j];
			}
		}
	}
}


void matmult_gpu1(int m, int n, int k) { 

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

	//Kernel function call
	//kernel_gpu1<<<1, 1>>>(m, n, k, d_A, d_B, d_C);
	
	//Transfer results from device to host
	transferToHost(h_A, h_B, h_C, d_A, d_B, d_C, A_no, B_no, C_no);

	//Device Synchronization (and Cuda Error Check)
	//checkCudaErrors(cudaDeviceSynchronize());
	cudaDeviceSynchronize();

	//Freeing allocated memory
	freeall(h_A, h_B, h_C, d_A, d_B, d_C);
}
} /* end extern */
