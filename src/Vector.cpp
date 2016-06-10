#include "Vector.hpp"

Vector::Vector(const size_t& size, real val)
{
    //std::cout << "Vector constructed with size "<< size << " and value " << val << std::endl;
    this->vec_.resize(size, val);
}

real Vector::operator* (const Vector& v)
{
    //std::cout << "operator* (const Vector& v) called\n";
    size_t size = this->vec_.size();
    assert(v.vec_.size() == size);
    assert(size>0);


    real sum = 0.;
    for(size_t i=0; i<size; ++i)
    {
        sum += (this->vec_[i] * v.vec_[i]);
    }


    return sum;

}

Vector Vector::operator* (const real& val)
{
    //std::cout << "operator* (const real& val) called\n";
    size_t size = this->vec_.size();
    assert(size>0);

    Vector temp(size);

    for(size_t i=0; i<size; ++i)
    {
        temp.vec_[i] = (this->vec_[i] * val);
    }

    return temp;

}

Vector Vector::operator+ (const Vector &v)
{
    //std::cout << "operator+ (const Vector &v) called\n";
    size_t size = this->vec_.size();
    assert(v.vec_.size() == size);
    assert(size>0);

    Vector temp(size);

    for(size_t i=0; i<size; ++i)
    {
        temp.vec_[i] = (this->vec_[i] + v.vec_[i]);
    }

    return temp;

}

Vector Vector::operator- (const Vector &v)
{
    //std::cout << "operator- (const Vector &v) called\n";
    size_t size = this->vec_.size();
    assert(v.vec_.size() == size);
    assert(size>0);

    Vector temp(size);

    for(size_t i=0; i<size; ++i)
    {
        temp.vec_[i] = (this->vec_[i] - v.vec_[i]);
    }

    return temp;

}

Vector Vector::operator- ()
{
    //std::cout << "operator-  called\n";
    size_t size = this->vec_.size();
    assert(size>0);

    Vector temp(size);

    for(size_t i=0; i<size; ++i)
    {
        temp.vec_[i] = -this->vec_[i];
    }

    return temp;
}

void Vector::operator= (const Vector &v)
{
    //std::cout << "operator= (const Vector &v) called\n";
    size_t size = this->vec_.size();
    assert(v.vec_.size() == size);
    assert(size>0);

    this->vec_ = v.vec_;

}

void Vector::display()
{
    std::cout << "Display of vector\n";

    for(size_t i=0; i< (this->vec_.size()); ++i)
    {
        std::cout << this->vec_[i] << "\t";
    }

    std::cout << "\n\n";

}

Vector::~Vector(){;}








