#!/bin/sh

# Compiling anew
make realclean
make -f Makefile.gcc

# Running experiment 15x and save results

cat 1 >> per_results.dat
matmult_c.gcc per 4 5 9 >> per_results.dat
cat 2 >> per_results.dat
matmult_c.gcc per 8 8 9 >> per_results.dat
cat 3 >> per_results.dat
matmult_c.gcc per 13 13 13 >> per_results.dat
cat 4 >> per_results.dat
matmult_c.gcc per 17 17 21 >> per_results.dat
cat 5 >> per_results.dat
matmult_c.gcc per 23 26 29 >> per_results.dat
cat 6 >> per_results.dat
matmult_c.gcc per 50 35 39 >> per_results.dat
cat 7 >> per_results.dat
matmult_c.gcc per 60 40 46 >> per_results.dat
cat 8 >> per_results.dat
matmult_c.gcc per 80 40 57 >> per_results.dat
cat 9 >> per_results.dat
matmult_c.gcc per 100 70 77 >> per_results.dat
cat 10 >> per_results.dat
matmult_c.gcc per 120 100 82 >> per_results.dat
cat 11 >> per_results.dat
matmult_c.gcc per 150 100 140 >> per_results.dat
cat 12 >> per_results.dat
matmult_c.gcc per 150 200 200 >> per_results.dat
cat 13 >> per_results.dat
matmult_c.gcc per 300 200 280 >> per_results.dat
cat 14 >> per_results.dat
matmult_c.gcc per 500 300 438 >> per_results.dat
cat 15 >> per_results.dat
matmult_c.gcc per 600 500 637 >> per_results.dat

exit 0
