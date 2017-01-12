#!/bin/bash

N=1000
MAX=100000
TOL=0.001

poisson gau $N $MAX $TOL > results_gauss.txt
poisson jac $N $MAX $TOL > results_jac.txt

python plot.py

