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


void matmult_gpu1(int m, int n, int k, double** A, double** B, double** C) { 
	
	//Number of entries or matrix size
	int A_no = m*k*sizeof(double);
	int B_no = k*n*sizeof(double);
	int C_no = m*n*sizeof(double);

	/*Initializing matrices (as arrays)	
	  matrix A: m, k
	  matrix B: k, n
	  matrix C: m, n		 */
	double* d_A; double* d_B; double* d_C;

	//Allocation of memory for matrices
	alloc(&d_A, &d_B, &d_C, A_no, B_no, C_no);

	//Transfer matrix to device
	transferToDevice(*A, *B, *C, d_A, d_B, d_C, A_no, B_no, C_no);

	//Kernel function call
	kernel_gpu1<<<1, 1>>>(m, n, k, d_A, d_B, d_C);

	//Device Synchronization (and Cuda Error Check)
	//checkCudaErrors(cudaDeviceSynchronize());
	cudaDeviceSynchronize();
	
	//Transfer results from device to host
	transferToHost(*A, *B, *C, d_A, d_B, d_C, A_no, B_no, C_no);

	//Freeing allocated memory
	freeall(d_A, d_B, d_C);
}
} /* end extern */
