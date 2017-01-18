#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void alloc(double* h_A, double* h_B, double* h_C, double* d_A, double* d_B, double* d_C, int A_no, int B_no, int C_no);
void init(double* h_A, int A_no, double* h_B, int B_no, double* h_C, int C_no);
void transferToDevice(double* h_A, double* h_B, double* h_C, double* d_A, double* d_B, double* d_C, int A_no, int B_no, int C_no);
void transferToHost(double* h_A, double* h_B, double* h_C, double* d_A, double* d_B, double* d_C, int A_no, int B_no, int C_no);
void freeall(double* h_A, double* h_B, double* h_C);
