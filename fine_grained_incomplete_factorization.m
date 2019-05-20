function [U,L] = fine_grained_incomplete_factorization(A)
%Fine_grained_incomplete_factorization Decompose matrix to be Lower and Upper Triangular matrix
%   so that A=L*U
%   Input = matrix A, Output = [U,L]
% Only works for positive definite matrices.


% Initialization
m=length(A);
[U,L]=LUDecomposition(A); % additional function

n=length(A);

n=length(A);
for sweep = 1 : 3
    for i = 1 : n
        for j=1 : n
            sum1=0;
            for k=1 : (j-1)
                sum1=sum1+L(i,k)*U(k,j);
            end
            sum2=0;
            for k=1 : (i-1)
                 sum2=sum2+L(i,k)*U(k,j);             
            end
            if i>j
                L(i,j) = (A(i,j)-sum1)/U(j,j);
            else
                U(i, j) = A(i,j)-sum2;
            end
                       
        end
    end
end