#include <stdio.h>
#include "datatools.h"
#include "init.h"
#include "jacobian.h"
//#include <helper_cuda.h>
#include <math.h>

int main(int argc, char **argv) {

  int size, N, max_it, total_size, k;
  double h, guess;
  double *h_Uold, *h_Unew, *h_f;
  double *d0_Uold, *d0_Unew, *d0_f;
  double *d1_Uold, *d1_Unew, *d1_f;

  if (argc < 3) {
  	printf("Wrong input\n");
  	return 0;
  }

  N = atoi(argv[1]);
  guess = 15;

  max_it = atoi(argv[2]);

  size = N + 2;
  h = 2.0 / (N + 1);
total_size = size * size * sizeof(double);

  cudaMallocHost((void**)&h_Uold, total_size);
  cudaMallocHost((void**)&h_Unew, total_size);
  cudaMallocHost((void**)&h_f, total_size);

  init_u(size, h_Uold, guess);
  init_u(size, h_Unew, guess);
  init_f(N, h_f);

cudaSetDevice(6);

cudaMalloc((void**)&d0_Uold, total_size / 2);
cudaMalloc((void**)&d0_Unew, total_size / 2);
cudaMalloc((void**)&d0_f, total_size / 2);

cudaMemcpy(d0_Uold, h_Uold, total_size / 2, cudaMemcpyHostToDevice);
cudaMemcpy(d0_Unew, h_Unew, total_size / 2, cudaMemcpyHostToDevice); 
cudaMemcpy(d0_f, h_f, total_size / 2, cudaMemcpyHostToDevice); 

cudaSetDevice(7);

cudaMalloc((void**)&d1_Uold, total_size / 2);
cudaMalloc((void**)&d1_Unew, total_size / 2 );
cudaMalloc((void**)&d1_f, total_size / 2);

cudaMemcpy(d1_Uold, h_Uold + size * size / 2, total_size / 2, cudaMemcpyHostToDevice);
cudaMemcpy(d1_Unew, h_Unew + size * size / 2, total_size / 2, cudaMemcpyHostToDevice); 
cudaMemcpy(d1_f, h_f + size * size / 2, total_size / 2, cudaMemcpyHostToDevice); 

cudaDeviceEnablePeerAccess(7, 6);

dim3 threadsPerBlock(16, 16);
dim3 numBlocks(ceil(N/16.0/2), ceil(N/16.0));
k = 0;
while(k < max_it) {

cudaSetDevice(6);
mat_swap(&d0_Uold, &d0_Unew);
mat_swap(&d1_Uold, &d1_Unew);

  jacobian_0<<<numBlocks, threadsPerBlock>>>(d0_Uold, d1_Uold, d0_Unew, d0_f, size, max_it, h);
cudaDeviceSynchronize();



cudaSetDevice(7);
  jacobian_1<<<numBlocks, threadsPerBlock>>>(d0_Uold, d1_Uold, d1_Unew, d1_f, size, max_it, h);
cudaDeviceSynchronize();

k++;
}

cudaSetDevice(6);
cudaMemcpy(h_Unew, d0_Unew, total_size / 2, cudaMemcpyDeviceToHost);

cudaSetDevice(7);
cudaMemcpy(h_Unew + size * size / 2, d1_Unew, total_size / 2, cudaMemcpyDeviceToHost);

int i;
for (i = 0; i < size * size; i++) {
if (i % size == 0)
printf("\n");
printf("%5.1f ", h_Unew[i]);}
printf("\n");


cudaFreeHost(h_Uold);
cudaFreeHost(h_Unew);
cudaFreeHost(h_f);

cudaSetDevice(6);
cudaFree(d0_Uold);
cudaFree(d0_Unew);
cudaFree(d0_f);


cudaSetDevice(7);
cudaFree(d1_Uold);
cudaFree(d1_Unew);
cudaFree(d1_f);
  return 0;
}
