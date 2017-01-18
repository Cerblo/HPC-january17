int main(int argc, char **argv)
{
 // Allocate memory space on host and device
 h_data = malloc(...);
 cudaMalloc(...);

 // Transfer data from host to device
 cudaMemcpy(...);

 // Kernel launch
 kernel<<<Grid, Block>>>(...);
 cudaDeviceSynchronize();

 // Transfer results from device to host
 cudaMemcpy(...);

 // Free memory
 free(h_data);
 cudaFree(...);
} 
