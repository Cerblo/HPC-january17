#include <stdio.h>
#include "datatools.h"
#include "init.h"
#include "jacobian.h"
#include <math.h>

int main(int argc, char **argv) {

  int size, N, max_it, total_size, k;
  double h, guess;
  double *h_Uold, *h_Unew, *h_f;
  double *d_Uold, *d_Unew, *d_f;

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

cudaMalloc((void**)&d_Uold, total_size);
cudaMalloc((void**)&d_Unew, total_size);
cudaMalloc((void**)&d_f, total_size);

  init_u(size, h_Uold, guess);
  init_u(size, h_Unew, guess);
  init_f(N, h_f);

cudaMemcpy(d_Uold, h_Uold, total_size, cudaMemcpyHostToDevice);
cudaMemcpy(d_Unew, h_Unew, total_size, cudaMemcpyHostToDevice); 
cudaMemcpy(d_f, h_f, total_size, cudaMemcpyHostToDevice); 


dim3 threadsPerBlock(16, 16);
dim3 numBlocks(ceil(N/16.0), ceil(N/16.0));
k = 0;
while(k < max_it) {

mat_swap(&d_Uold, &d_Unew);

  jacobian<<<numBlocks, threadsPerBlock>>>(d_Uold, d_Unew, d_f, size, max_it, h);
cudaDeviceSynchronize();

k++;
}

cudaMemcpy(h_Unew, d_Unew, total_size, cudaMemcpyDeviceToHost);


cudaFreeHost(h_Uold);
cudaFreeHost(h_Unew);
cudaFreeHost(h_f);

cudaFree(d_Uold);
cudaFree(d_Unew);
cudaFree(d_f);

  return 0;
}
