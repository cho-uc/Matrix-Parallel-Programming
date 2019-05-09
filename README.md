# Matrix related calculation & Parallel Programming

Mostly C++, but also maybe Java, python, matlab
_____________________________________________________________________
ILU.cpp

Conventional ILU Factorization using parallel program of OpenMP.

TODO : Fine-Grained Parallel Incomplete Factorization

TODO : Symmetric Fine-Grained Parallel Incomplete Factorization.

Based on work by :
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
