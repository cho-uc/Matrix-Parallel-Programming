# Matrix related calculation & Parallel Programming

Language : C++ Java, python, matlab
_____________________________________________________________________
ILU.cpp
Conventional ILU Factorization using parallel program of OpenMP.

fine_grained_incomplete_factorization.m
Decompose matrix to be Lower and Upper Triangular matrix so that L*U=A
Only works for positive definite matrices.

incomplete_Cholesky.m
Decompose matrix to be Lower and Upper Triangular matrix so that U'*U=A
Only works for positive definite matrices.

Based on research paper by :
FINE - GRAINED PARALLEL INCOMPLETE LU FACTORIZATION 
by EDMOND CHOW AND AFTAB PATEL
____________________________________________________________________
Speed.cpp

Compare speed of function with reference argument & without reference argument.

Without optimization (-O3):

  reference argument & function is slower
  
With optimization (-O3):

  reference argument & function is faster

But the difference between compiling with -O3 and not is huge.

So stuck with compiling with -O3
_____________________________________________________
createBMatrix.m

Function to create B matrix from a given matrix in Finite Element Methods

__________________________________
LUDecomposition.m

Function to create LU Decomposition
____________________________________
IncompleteLU.m

Incomplete LU Factorization

_______________________________________
LUFactorization

Function to create LU Factorization
__________________________________________________

Steepest_descent

Calculating inverse matrix using a Steepest descent algorithm.
____________________________________________________
