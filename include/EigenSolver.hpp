#ifndef EIGENSOLVER_H
#define EIGENSOLVER_H

#include "Solver.hpp"
#include <fstream>

#define tol 10^(-10)

class EigenSolver
{
private:
    size_t lambda_,lambdaOld_;
    real factor_,errorLimit_, eps_;
    Vector f_,u_h_;
    Matrix A_, M_;


public:
    EigenSolver(const Mat&, const Mat&, const real&);
    ~EigenSolver();

    void inverseIteration();
    void writeEigenMode();

};

#endif // EIGENSOLVER_H
