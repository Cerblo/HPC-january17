#include "alloc.h"

void alloc(double* h_A, double* h_B, double* h_C, double* d_A, double* d_B, double* d_C, int A_no, int B_no, int C_no) {
	//Dynamic allocation of matrices with malloc() on CPU-side
	cudaMallocHost((void **)&h_A, A_no);
	cudaMallocHost((void **)&h_B, B_no);
	cudaMallocHost((void **)&h_C, C_no);
	//Allocation in global GPU memory
	cudaMalloc((void **)&d_A, A_no);
	cudaMalloc((void **)&d_B, B_no);
	cudaMalloc((void **)&d_C, C_no);
}

void init(double* h_A, int A_no, double* h_B, int B_no, double* h_C, int C_no) {
	//Initialize matrix entries to one
	int i;
	for(i=0; i<A_no; i++) {
		h_A[i] = 1;	
	}
	for(i=0; i<B_no; i++) {
		h_B[i] = 1;
	}
	for(i=0; i<C_no; i++) {
		h_C[i] = 0;
	}
}

void transferToDevice(double* h_A, double* h_B, double* h_C, double* d_A, double* d_B, double* d_C, int A_no, int B_no, int C_no) {
	cudaMemcpy(d_A, h_A, A_no, cudaMemcpyHostToDevice);
	cudaMemcpy(d_B, h_B, B_no, cudaMemcpyHostToDevice);
	cudaMemcpy(d_C, h_C, C_no, cudaMemcpyHostToDevice);
}

void transferToHost(double* h_A, double* h_B, double* h_C, double* d_A, double* d_B, double* d_C, int A_no, int B_no, int C_no) {
	cudaMemcpy(h_A, d_A, A_no, cudaMemcpyDeviceToHost);
	cudaMemcpy(h_B, d_B, B_no, cudaMemcpyDeviceToHost);
	cudaMemcpy(h_C, d_C, C_no, cudaMemcpyDeviceToHost);
}

void freeall(double* h_A, double* h_B, double* h_C, double* d_A, double* d_B, double* d_C) {
	cudaFreeHost(h_A);
	cudaFreeHost(h_B);
	cudaFreeHost(h_C);
	cudaFree(d_A);
	cudaFree(d_B);
	cudaFree(d_C);
}

