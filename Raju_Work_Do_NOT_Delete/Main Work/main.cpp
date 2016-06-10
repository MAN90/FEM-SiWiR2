#include "Solver.hpp"
#include "EigenSolver.hpp"

int main()
{
    Vector b(4,1);
    Vector x(4);

    /*//v1.display();
    //v2.display();
    

    Vector v3(5);
    //v3.display();

    //v3 = v1 + v2;
    //v3 = v3*2;

    //v3.display();

    //v1.display();
    //v2.display();

    real sum = v1*v2;
    std::cout << "Sum ? 15: " << sum << std::endl;*/
    
    
    Mat m(4);
    m[0].insert(std::pair<size_t, real> (0,2));
    m[0].insert(std::pair<size_t, real> (1,-1));
    m[1].insert(std::pair<size_t, real> (0,-1));
    m[1].insert(std::pair<size_t, real> (1,2));
    m[1].insert(std::pair<size_t, real> (2,-1));
    m[2].insert(std::pair<size_t, real> (1,-1));
    m[2].insert(std::pair<size_t, real> (2,2));
    m[2].insert(std::pair<size_t, real> (3,-1));
    m[3].insert(std::pair<size_t, real> (2,-1));
    m[3].insert(std::pair<size_t, real> (3,2));

    Mat n = m;
    n[0][1]  = 5;
    n[1][2] = 1.5;
    //n[0].insert(std::pair<size_t, real> (0,8));
    //n[0].insert(std::pair<size_t, real> (1,-7.));

    /*m[2].insert(std::pair<size_t, real> (0,2));
    m[2].insert(std::pair<size_t, real> (2,8));
    m[3].insert(std::pair<size_t, real> (0,7));
    m[3].insert(std::pair<size_t, real> (2,9));
    m[3].insert(std::pair<size_t, real> (3,1));*/



    const real eps = 0.0001;
    EigenSolver  eigen(m, n, eps);
    eigen.inverseIteration();
    /*v2 = mat*v1;
    
    std::cout << "Matrix before:\n";
    mat.display();
    
    std::cout << "Vector after:\n";
    v2.display();*/
    
//    real norm = LSESolver::Solver<Matrix, Vector>::norm(b);
//    std::cout << "norm? sqrt(5) " << norm << std::endl;


    /*std::cout << "Before calling CG\n";
    x.display();
    x =  LSESolver::Solver<Matrix, Vector>::cgSolve(A,b,x,0.00001);

    std::cout << "After calling CG\n";
    x.display();
    */
}
