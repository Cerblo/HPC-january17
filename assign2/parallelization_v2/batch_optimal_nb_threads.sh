#!/bin/bash
# 02614 - High-Performance Computing, January 2017
#
# batch script to run collect on a decidated server in the hpcintro
# queue
#
# Author: Bernd Dammann <bd@cc.dtu.dk>
#
#PBS -N collector
#PBS -q hpcintro
#PBS -l nodes=1:ppn=20
#PBS -l walltime=10:00

cd $PBS_O_WORKDIR

module load studio

# define the driver name to use
# poisson
#
EXECUTABLE=poisson

# define the N, max_iter, tol values as inputs of the executable
#
IN="10000 1000000 0.001"

# define the max no. of iterations the driver should use - adjust to
# get a reasonable run time.  You can get an estimate by trying this
# on the command line, i.e. "MFLOPS_MAX_IT=10 ./matmult_...." for the
# problem size you want to analyze.
#
MFLOPS_MAX_IT=5

# experiment name
#
JID=`echo ${PBS_JOBID%.*}`
EXPOUT="$PBS_JOBNAME.${JID}.er"


# uncomment the HWCOUNT line, if you want to use hardware counters
# define an option string for the harwdware counters (see output of
# 'collect -h' for valid values.  The format is:
# -h cnt1,on,cnt2,on,...  (up to four counters at a time)
#
# the example below is for L1 hits, L1 misses, L2 hits, L2 misses
#
HWCOUNT="-h dch,on,dcm,on,l2h,on,l2m,on"

# start the collect command with the above settings
# we iterate on the number of threads we use
for NUM in {1..20}
do
	#OMP_NUM_THREADS=$NUM collect -o $EXPOUT $HWCOUNT ./$EXECUTABLE $IN
	time OMP_NUM_THREADS=$NUM ./$EXECUTABLE $IN
done
