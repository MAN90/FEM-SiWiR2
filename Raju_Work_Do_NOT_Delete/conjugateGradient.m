% *********************************************
% * Optimization for Engineers 2016 - Dr. Johannes Hild
% *********************************************

function [x_s] = conjugateGradient(A, b, x_0, eps, k_max)
% *********
% * INPUT *
% *********
% A         : symmetric (positiv definite) nxn-matrix.
% b         : righthand side vector (column vector).
% x_0       : start vector, column vector.
% eps       : tolerance.
% k_max     : maximum number of iterations.
%
% **********
% * OUTPUT *
% **********
% x_s        : solution of A * x_s = b.
%
% ***************
% * DESCRIPTION *
% ***************
% Multi-dimensional minimization of f(x):=1/2*x'*A*x - b'*x + c i.e. solving
% A*x=b

% set default parameters if not all are given
if nargin < 3
    x_0 = b;
end

if nargin < 4
    eps=1.0e-5;
end

if nargin < 5
    k_max = 100; % CG converges after n steps.
end

%check size of b and x_0
if size(x_0) ~= size(b)
    error('Error: x_0 and b must have same dimension!');
end
if(eps <= 0)
	error('Error: eps has to be greater 0');
end


%initialize data
k = 0;

%%%%%%%%%%%%%%%%%%%%%%%%%
% BEGIN OF MISSING CODE
%%%%%%%%%%%%%%%%%%%%%%%%%

x_k = x_0;
r_k = A*x_k - b; % Initial Residual
d_k = -r_k;     %descent direction

% Main loop of CG
while ( norm(r_k) > eps && k < k_max)
    
    %Updation of variables
    rho_k = d_k'*A*d_k;
    t_k = -(r_k'*d_k)/rho_k;
    x_k = x_k + t_k*d_k;
    r_k = r_k + t_k*A*d_k;
    beta_k = (r_k'*A*d_k)/rho_k;
    d_k = -r_k + beta_k*d_k;
    
    %counter increment
    k = k + 1;
end

%final x_k
x_s = x_k;

%%%%%%%%%%%%%%%%%%%%%%%%%
% END OF MISSING CODE
%%%%%%%%%%%%%%%%%%%%%%%%%

end
