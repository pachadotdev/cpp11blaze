#!/bin/bash
#SBATCH --job-name=cpp11blaze
#SBATCH --output=cpp11blaze_output.txt
#SBATCH --nodes=1
#SBATCH --ntasks=40
#SBATCH --time=12:00:00
#SBATCH --account=def-shirimb

# Load necessary modules
module load gcc/8.3.0
module load r/4.2.2-batteries-included
module load fftw

export MKLROOT=/gpfs/fs1/scinet/intel/2019u4/compilers_and_libraries_2019.4.243/linux/mkl
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$MKLROOT/lib/intel64_lin
export R_LIBS_USER=/scratch/s/shirimb/msep/cpp11blaze/Rlib
export OMP_NUM_THREADS=40
export MKL_NUM_THREADS=40

# Run the R script
Rscript dev/01-bench-matrix-calculation.r
Rscript dev/02-bench-matrix-functions.r
Rscript dev/03-bench-programmation.r
