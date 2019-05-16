function [U] = incomplete_Cholesky(A)
%Incomplete_Cholesky Decompose matrix to be Lower and Upper Triangular matrix
%   so that A=U'*U*
%   Input = matrix A, Output = [U,L]
% Only works for positive definite matrices.


% Initialization
m=length(A);
[U,L]=LUDecomposition(A); % additional function

n=length(A);
for sweep = 1 : 3
    for i = 1 : n
        for j=1 : n
            sum=0;
            for k=1 : (i-1)
                 sum=sum+U(k,i)*U(k,j);    
            end
            s=A(i,j)-sum;
            if i~=j
                 U(i,j) = s/U(i,i);
            else
                 U(i, i) = sqrt(s);
            end
        end
    end
end