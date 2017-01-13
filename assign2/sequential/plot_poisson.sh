#!/bin/bash

N=100
MAX=100000
TOL=0.0000001

poisson gau $N $MAX $TOL > results_gauss.txt
poisson jac $N $MAX $TOL > results_jac.txt

python plot.py

