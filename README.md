# Matrix related calculation & Parallel Programming

Language : C++ Java, python, matlab

_____________________________________________________________________
buffer_creation_test.cpp

OpenCl:
Using CL_MEM_COPY_HOST_PTR when creating buffer will result in slower execution
However this is only applied to kernel method with large arguments (>4)
_____________________________________________________________________
ILU.cpp & ILU_pointer.cpp

Conventional ILU Factorization using parallel program of OpenMP.
Data structure : std :: vector and pointer arrays

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
_______________________________________________________
performance_change_order_code.cpp

Three-four times faster if the order of part I & part II in the code is switched.
https://stackoverflow.com/questions/56308339/is-position-of-code-affect-performance-in-c/56308654#56308654

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
