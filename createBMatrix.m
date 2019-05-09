function [B] = createBMatrix(J,N)
%createBMatrix Create B Matrix for rectangular planar element
% input = (J,N), J=2x2; N=2xn  
% Not applied to triangular element

n= length(N); % no of columns 
B_temp=(inv(J))*N;
B=zeros(3,2*n);
for i=1:n
   B(1,2*i-1)=B_temp(1,i);
    B(2,2*i)=B_temp(2,i);
    B(3,2*i-1)=B_temp(2,i);
    B(3,2*i)=B_temp(1,i);
end
