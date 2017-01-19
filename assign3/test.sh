m=30
n=20
k=20

matmult_f.nvcc2 lib $1 $2 $3
matmult_f.nvcc2 gpu1 $1 $2 $3
matmult_f.nvcc2 gpu2 $1 $2 $3
matmult_f.nvcc2 gpu3 $1 $2 $3
matmult_f.nvcc2 gpu4 $1 $2 $3
