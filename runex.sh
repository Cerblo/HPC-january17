#!/bin/sh

# Compiling anew
./make realclean
./make -f Makefile.gcc

# Running experiment 15x and save results

#1
./matmult_c.gcc per mnk >> results_perm.dat
cat mnk >> results_perm.dat
#2
./matmult_c.gcc per mnk >> results_perm.dat
cat mnk >> results_perm.dat
#3
./matmult_c.gcc per mnk >> results_perm.dat
cat mnk >> results_perm.dat
#4
./matmult_c.gcc per mnk >> results_perm.dat
cat mnk >> results_perm.dat
#5
./matmult_c.gcc per mnk >> results_perm.dat
cat mnk >> results_perm.dat

#1
./matmult_c.gcc per mnk >> results_perm.dat
cat mnk >> results_perm.dat
#2
./matmult_c.gcc per mnk >> results_perm.dat
cat mnk >> results_perm.dat
#3
./matmult_c.gcc per mnk >> results_perm.dat
cat mnk >> results_perm.dat
#4
./matmult_c.gcc per mnk >> results_perm.dat
cat mnk >> results_perm.dat
#5
./matmult_c.gcc per mnk >> results_perm.dat
cat mnk >> results_perm.dat

#1
./matmult_c.gcc per mnk >> results_perm.dat
cat mnk >> results_perm.dat
#2
./matmult_c.gcc per mnk >> results_perm.dat
cat mnk >> results_perm.dat
#3
./matmult_c.gcc per mnk >> results_perm.dat
cat mnk >> results_perm.dat
#4
./matmult_c.gcc per mnk >> results_perm.dat
cat mnk >> results_perm.dat
#5
./matmult_c.gcc per mnk >> results_perm.dat
cat mnk >> results_perm.dat

exit 0
