#include "EigenSolver.hpp"

EigenSolver::EigenSolver(const Mat& A, const Mat& M, const real& eps)
{
    std::cout<< "EigenSolver constructor is called!" << std::endl;

    size_t size = A.size();
    std::cout << "size of vector: " << size << std::endl;

    this->A_.mat_ = A;
    this->M_.mat_ = M;

    //A_.display();
    errorLimit_ = tol;
    eps_ = eps;
    lambda_ = 0.;
    factor_ = 1;

    std::cout<<"Size of Vector is :  "<< size << std::endl;
    f_.vec_.resize(size, 0.0);
    u_h_.vec_.resize(size, 1.0);

}


void EigenSolver::inverseIteration()
{
     size_t ctr = 0;
     real norm, num, den;
     size_t len;

    while(factor_ > errorLimit_ && ctr <2)
    {
        if(ctr!=0)
        lambdaOld_ = lambda_;

        f_ = M_ * u_h_;

        //std::cout << "u_h before solver\n";
        //u_h_.display();

        //std::cout << "f before solver\n";
        //f_.display();

        u_h_ = LSESolver::Solver<Matrix, Vector>::cgSolve(A_, f_, u_h_, eps_); // CG solver solved in Solver.hpp
         std::cout << "u_h after solver\n";
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


        if (ctr != 0)
            factor_ = std::fabs((lambda_-lambdaOld_)/lambdaOld_);


        //std::cout << "ctr: " << ctr << std::endl;
        //u_h_.display();

        ctr++;

    }


}

void EigenSolver::writeEigenMode()
{
    std::ofstream  file_U_output;
    file_U_output.open("eigenmode.txt");

    std::cout<<"Writing Eigenmode to the text file"<<std::endl;

    size_t len = A_.mat_.size();
    for(size_t i=0; i<len; ++i)
    {
        file_U_output << i <<"\t" << u_h_.vec_[i];    // Incomplete --- y-axis missing
    }

    file_U_output.close();
}


EigenSolver::~EigenSolver()
{
 std::cout << "Destructor called\n"  ;
}
