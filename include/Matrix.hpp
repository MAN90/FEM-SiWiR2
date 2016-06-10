#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "Vector.hpp"

//template <class T>
class Matrix 
{
    public :
    Mat mat_; // Mat is defined in Type.hpp which is included in Vector.h

    ~Matrix();                  // Destructor
    Matrix(const Mat& );		// Copy Constructor
    Matrix();

    Vector operator* (const Vector& v);
    void operator= (const Matrix& );
    void display();

};

#endif


