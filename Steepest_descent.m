%% 2 x 2 matrix
clear all, close all, clc
A=[2 1;1 1]; % 2x2
x(:,1)=[2 ;1 ]; 
b=[3;4]; % 2x1
N=33; % number of iteration

for i=2:N
nablaE(:,i-1)=A*x(:,i-1)-b; % 2x1
t(i)=((nablaE(:,i-1))'*nablaE(:,i-1))  / ((nablaE(:,i-1))'*A*nablaE(:,i-1));
x(:,i)=x(:,i-1)-t(i)*nablaE(:,i-1);
end

x_iterative=x(:,N)

%Actual result 
x_actual=inv(A)*b

%% 3 x 3 matrix (still not working)
clear all, close all, clc
A=[2 1 5 ;1 1 4; 3 7 6]; % 3x3
x(:,1)=[2 ;1 ;8];  % 3x1
b=[3;4;9];  % 3x1
N=30; % number of iteration

for i=2:N
nablaE(:,i-1)=A*x(:,i-1)-b;
t(i)=((nablaE(:, i-1))'*nablaE(:,i-1))  / ((nablaE(:,i-1))'*A*nablaE(:,i-1));
x(:,i)=x(:,i-1)-t(i)*nablaE(:,i-1);
end

x_iterative=x(:,N)

%Actual result 
x_actual=inv(A)*b