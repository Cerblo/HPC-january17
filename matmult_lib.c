void
matmult_lib(int m, int n, int k, double **A, double **B, double **C) {
  int alpha = 1;
  int beta =0;
  cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, \
              m, n, k, alpha, *A, k, *B, n, beta, *C, n);
}
