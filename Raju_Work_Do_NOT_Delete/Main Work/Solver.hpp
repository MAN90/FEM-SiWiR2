#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "Matrix.hpp"
#include <cmath>   // for std::sqrt

namespace LSESolver {

    template <class MatrixType, class VectorType>  //Template parameters: in this assignment MatrixType=Matrix and VectorType is Vector
    class Solver{

    public:

         static VectorType& cgSolve(MatrixType& A, const VectorType& b, VectorType& x, const real& eps);
//        % *********
//        % * INPUT *
//        % *********
//        % A         : symmetric (positiv definite) nxn-matrix.
//        % b         : righthand side vector (column vector).
//        % x         : start vector, column vector.
//        % eps       : tolerance.
//        % numIter     : maximum number of iterations.
//        %
//        % **********
//        % * OUTPUT *
//        % **********
//        % x        : solution of A * x = b.
//        %
//        % ***************
//        % * DESCRIPTION *
//        % ***************
//        % Solves A*x = b.

        static real norm(const VectorType& v);


    };

    // Compute the norm of a vector of type VectorType which is Vector in our assignment
    template <class MatrixType, class VectorType>
    real  Solver<MatrixType, VectorType> :: norm(const VectorType& v)
    {
        real sum=0.;

        // The code has been written assuming v=Vector, It won't compile if v is std::vector, we need to use type traits for that.
        size_t len = v.vec_.size();
        for(size_t i=0; i<len; ++i)
        {
            sum += (v.vec_[i]*v.vec_[i]);
        }

        return std::sqrt(sum);

    }

    template <class MatrixType, class VectorType>
    VectorType&  Solver<MatrixType, VectorType> :: cgSolve(MatrixType& A, const VectorType& b, VectorType& x, const real& eps)
    {
        size_t len = A.mat_.size();
        assert(len == b.vec_.size() && b.vec_.size() == x.vec_.size());
        assert(eps>0.);

        const size_t numIter = len ;   // cg converges in at most n steps
        //std::cout << "numIter is: " << numIter << std::endl;
        size_t k=0;
        real rho_k, t_k, beta_k;
        Vector r_k(len), d_k(len);

        // Initialisation
        r_k = A*x - b;       //Initial Residual
        d_k = r_k*(-1);      //descent direction

        // Main loop of CG
        while ( norm(r_k) > eps && k < numIter)
        {
            //Updation of variables
            rho_k = d_k*(A*d_k);
            t_k = -(r_k*d_k)/rho_k;
            x = x + d_k*t_k;
            r_k = r_k + (A*d_k)*t_k;
            beta_k = (r_k*(A*d_k))/rho_k;
            d_k = -r_k + d_k*beta_k;


            //std::cout << "k: " << k  <<"  residual is:  " << norm(r_k)<< "\nx is: \n";
            //x.display();

            //counter increment
            k += 1;
        }

        return x;
    }

}

#endif
