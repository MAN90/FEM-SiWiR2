#ifndef EIGENSOLVER_H
#define EIGENSOLVER_H

#include "Solver.hpp"
#include "ProblemFormulate.hpp"
#include <iomanip>


#define tol 1e-10

class EigenSolver
{
private:
    real lambda_,lambdaOld_;
    real factor_,errorLimit_, eps_;
    Vector f_,u_h_;
    Matrix A_, M_;


public:
    EigenSolver(const Mat&, const Mat&, const real&);
    ~EigenSolver();

    void inverseIteration();
    Vector& getEigenVector();

};

#endif // EIGENSOLVER_H
