#include "alloc.h"

void alloc(double** d_A, double** d_B, double** d_C, int A_no, int B_no, int C_no) {
	//Allocation in global GPU memory
	cudaMalloc((void **)d_A, A_no);
	cudaMalloc((void **)d_B, B_no);
	cudaMalloc((void **)d_C, C_no);
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

void freeall(double* d_A, double* d_B, double* d_C) {
	cudaFree(d_A);
	cudaFree(d_B);
	cudaFree(d_C);
}

