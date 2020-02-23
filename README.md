# Matrix related calculation & Parallel Programming

Language : C++, Java, python, matlab

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
____________________________________________________________________
locality_of_reference.cpp

Changing the order of index looping resulted in much faster execution due to cache penalty.
With -O3 flags, the speed up is around 5X faster for n = 1500
____________________________________________________________________
assignment_operator_test.cu

Performance testing for assignment operator '+='

Comparison between '+=' and '='

Result :	 assignment operator '=' is faster than '+='

____________________________________________________________________

performance_change_order_code.cpp

Three-four times faster if the order of part I & part II in the code is switched.
https://stackoverflow.com/questions/56308339/is-position-of-code-affect-performance-in-c/56308654#56308654

_____________________________________________________

vector_push_test.cpp

Comparing performance between push back vector with C-style array
for discretization of 3D block
Related Stackoverflow issue : 
https://stackoverflow.com/questions/20168051/why-push-back-is-slower-than-operator-for-a-previously-allocated-vector/20168172#20168172

_____________________________________________________

max_args_test.cu

Test max argument's size (256 Byte) for Cuda kernel.
Passing struct to kernel arguments to overcome limitation of number of args in kernel
But regular kernel turns out working properly with 70 args 
https://devtalk.nvidia.com/default/topic/458705/is-there-any-limit-on-of-arguments-in-cuda-kernel-/

_______________________________________________________
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
