__global__ void kernel_gpu1(int m, int n, int k, double* A, double* B, double* C) {
	int i, j, l;
	for ( i = 0; i < m; i++ ) {
		for ( j = 0; j < n; j++ ) {
			for ( l = 0; l < k; l++) {
				C[i*j+i] += A[i*l+i]*B[l*j+l];
			}
		}
	}
};


void matmult_gpu1(int m, int n, int k) { 

	/*Declaring matrices (as arrays)	
	  matrix A: m, k
	  matrix B: k, n
	  matrix C: m, n		 */
	double *h_A, *h_B, *h_C; //host adress
	double *d_A, *d_B, *d_C; //device address
	//Number of entries or matrix size
	int A_no = m*k*sizeof(double);
	int B_no = k*n*sizeof(double);
	int C_no = m*n*sizeof(double);

	//Allocation of memory for matrices
	alloc(h_A, h_B, h_C, d_A, d_B, d_C, A_no, B_no, C_no);

	//Initialize matrix entries to one
	init(h_A, A_no, h_B, B_no, h_C, C_no);

	//Transfer matrix to device
	transferToDevice(h_A, h_B, h_C, d_A, d_B, d_C, A_no, B_no, C_no);

	//Kernel function call
	kernel_gpu1<<<1, 1>>>(m, n, k, d_A, d_B, d_C);
	
	//Transfer results from device to host
	transferToHost(h_A, h_B, h_C, d_A, d_B, d_C, A_no, B_no, C_no);

	//Device Synchronization (and Cuda Error Check)
	checkCudaErrors(cudaDeviceSynchronize());

	//Freeing allocated memory
	freeall(h_A, h_B, h_C);
}

