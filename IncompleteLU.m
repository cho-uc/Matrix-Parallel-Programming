function [B] = LUFactorization(A)
%Incomplete LU Factorization Decompose matrix to be Lower and Upper Triangular matrix
%   so that A=L*U
%   Input = matrix A, Output = [B] where B=U+L+I


% Initialization
n=length(A);
B=A;

for i = 2 : n
    for k = 1 : i-1
        B(i,k)=B(i,k)/B(k,k);
        for j=k+1:n
            B(i,j)=B(i,j)-B(i,k)*B(k,j);
        end
    end
end
