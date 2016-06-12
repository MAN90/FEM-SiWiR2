#include "EigenSolver.hpp"

EigenSolver::EigenSolver(const Mat& A, const Mat& M, const real& eps)
{
//    std::cout<< "EigenSolver constructor is called!" << std::endl;

    size_t size = A.size();
//    std::cout << "Size of input Vector: " << size << std::endl;

    this->A_.mat_ = A;
    this->M_.mat_ = M;

    //A_.display();
    errorLimit_ = tol;     std::cout << "errorLimit: " << errorLimit_ << std::endl;


    eps_ = eps;
    lambdaOld_ = 0.;
    lambda_ = 0.;
    factor_ = 1;

    f_.vec_.resize(size, 0.0);
    u_h_.vec_.resize(size, 1.0);

}


void EigenSolver::inverseIteration()
{
     size_t ctr = 0;
     real norm, num, den;
     size_t len;

     std::cout<<"Calculating Eigen value..... "<< std::endl;

//    while(factor_ > errorLimit_ && ctr <5)
     while(factor_ > errorLimit_)
    {
        if(ctr!=0)
        lambdaOld_ = lambda_;

        f_ = M_ * u_h_;

        //std::cout << "u_h before solver\n";
        //u_h_.display();

        //std::cout << "f before solver\n";
        //f_.display();

        u_h_ = LSESolver::Solver<Matrix, Vector>::cgSolve(A_, f_, u_h_, eps_); // CG solver solved in Solver.hpp
//         std::cout << "u_h after solver\n";
        //u_h_.display();
        norm = LSESolver::Solver<Matrix, Vector>::norm(u_h_); // norm function used from Solver.hpp

        len = u_h_.vec_.size();
        for(size_t i=0; i<len; ++i)
        {
            u_h_.vec_[i] /= norm;    //normalizing
        }

        norm = LSESolver::Solver<Matrix, Vector>::norm(u_h_);

        assert(norm >0.9 && norm <1.1);

        num = u_h_ * (A_ * u_h_);
        den = u_h_ * (M_ * u_h_);

        lambda_ = num / den;
//        std::cout<<std::setprecision(11)<<"lambdaOld is :"<< lambdaOld_ << std::endl;
//        std::cout<<std::setprecision(11)<<"lambda is :"<< lambda_ << std::endl;

        if (ctr != 0)
            factor_ = std::fabs((lambda_-lambdaOld_)/lambdaOld_);


        //std::cout << "ctr: " << ctr << std::endl;
        //u_h_.display();

        ctr++;
//        std::cout<<"factor is :"<< factor_ << std::endl;


    }
     std::cout<<std::setprecision(11)<<"Eigen Value is : "<< lambda_ << std::endl;


}


Vector& EigenSolver::getEigenVector()
{
    return u_h_;
}


EigenSolver::~EigenSolver()
{
// std::cout << "Destructor called\n"  ;
}
