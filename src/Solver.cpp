#include "Solver.hpp"


namespace LSESolver {

    // Compute the norm of a vector of type VectorType which is Vector in our assignment
    /*template <class MatrixType, class VectorType>
    //real  Solver<MatrixType, VectorType> :: norm(const VectorType& v)
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

    }*/
}
