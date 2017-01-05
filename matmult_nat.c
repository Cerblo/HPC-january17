// native function
void
matmult_nat(int m, int n, int k, double **A, double **B, double **C) {
  int i, j, l;

  /* initializing C to be zero */
  for ( i = 0; i < m; i++ ) {
    for ( j = 0; j < n; j++ ) {
      C[i][j] = 0;
    }
  }

  /* matrix multiplication */
  for ( i = 0; i < m; i++ ) {
    for ( j = 0; j < n; j++ ) {
      for ( l = 0; l < k; l++) {
        C[i][j] += A[i][l]*B[l][j];
      }
    }
  }
}

//mnk version of the function is also the same one as the natural fucntion
void
matmult_mnk(int m, int n, int k, double **A, double **B, double **C) {
  int i, j, l;

  /* initializing C to be zero */
  for ( i = 0; i < m; i++ ) {
    for ( j = 0; j < n; j++ ) {
      C[i][j] = 0;
    }
  }

  /* matrix multiplication */
  for ( i = 0; i < m; i++ ) {
    for ( j = 0; j < n; j++ ) {
      for ( l = 0; l < k; l++) {
        C[i][j] += A[i][l]*B[l][j];
      }
    }
  }
}

void
matmult_mkn(int m, int n, int k, double **A, double **B, double **C) {
  int i, j, l;

  /* initializing C to be zero */
  for ( i = 0; i < m; i++ ) {
    for ( j = 0; j < n; j++ ) {
      C[i][j] = 0;
    }
  }

  /* matrix multiplication */
  	for ( i = 0; i < m; i++ ) {
      for ( l = 0; l < k; l++) {
    for ( j = 0; j < n; j++ ) {
        C[i][j] += A[i][l]*B[l][j];
      }
    }
  }
}

void
matmult_kmn(int m, int n, int k, double **A, double **B, double **C) {
  int i, j, l;

  /* initializing C to be zero */
  for ( i = 0; i < m; i++ ) {
    for ( j = 0; j < n; j++ ) {
      C[i][j] = 0;
    }
  }

  /* matrix multiplication */
      for ( l = 0; l < k; l++) {
  	for ( i = 0; i < m; i++ ) {
    	for ( j = 0; j < n; j++ ) {
        C[i][j] += A[i][l]*B[l][j];
      }
    }
  }
}

void
matmult_knm(int m, int n, int k, double **A, double **B, double **C) {
  int i, j, l;

  /* initializing C to be zero */
  for ( i = 0; i < m; i++ ) {
    for ( j = 0; j < n; j++ ) {
      C[i][j] = 0;
    }
  }

  /* matrix multiplication */
      for ( l = 0; l < k; l++) {
    	for ( j = 0; j < n; j++ ) {
  	for ( i = 0; i < m; i++ ) {
        C[i][j] += A[i][l]*B[l][j];
      }
    }
  }
}

void
matmult_nkm(int m, int n, int k, double **A, double **B, double **C) {
  int i, j, l;

  /* initializing C to be zero */
  for ( i = 0; i < m; i++ ) {
    for ( j = 0; j < n; j++ ) {
      C[i][j] = 0;
    }
  }

  /* matrix multiplication */
    	for ( j = 0; j < n; j++ ) {
      for ( l = 0; l < k; l++) {
  	for ( i = 0; i < m; i++ ) {
        C[i][j] += A[i][l]*B[l][j];
      }
    }
  }
}

void
matmult_nmk(int m, int n, int k, double **A, double **B, double **C) {
  int i, j, l;

  /* initializing C to be zero */
  for ( i = 0; i < m; i++ ) {
    for ( j = 0; j < n; j++ ) {
      C[i][j] = 0;
    }
  }

  /* matrix multiplication */
    	for ( j = 0; j < n; j++ ) {
  	for ( i = 0; i < m; i++ ) {
      for ( l = 0; l < k; l++) {
        C[i][j] += A[i][l]*B[l][j];
      }
    }
  }
}
