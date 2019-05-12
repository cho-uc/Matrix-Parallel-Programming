function [U,L] = LUDecomposition(A)
%LUDecomposition Decompose matrix to be Lower and Upper Triangular matrix
%   It is a widely used direct solution technique for linear system
%   Input = matrix A, Output = [L,U]


% get upper decomposition
U=A;
for i=2:length(A)
    for j=1:(i-1)
        U(i,j)=0;
    end
end

% get lower decomposition
L=A;
for i=1:length(A)
    for j=i:length(A)
        L(i,j)=0;
    end
end

end

