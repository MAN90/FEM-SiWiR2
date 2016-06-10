#include "Matrix.hpp"

Matrix::Matrix(const Mat& m)
{
    std::cout << "Constructor called in Matrix\n";
    this->mat_ = m;
}


Matrix::Matrix()     // Constructor
{
    std::cout << "Matrix default c'tr called" << std::endl;
}

Matrix::~Matrix()
{

}

Vector Matrix::operator* (const Vector &v)
{
    size_t size = this->mat_.size();
    assert(size == v.vec_.size());
    assert(size>0);

    Vector retVec(size, 0.);
    size_t ctr=0;
    std::map<size_t, real> map;

    // iter1 points to first entry in return vector
    // iter2 point to the map provided by iter1
    for(auto iter1= retVec.vec_.begin(); iter1!=retVec.vec_.end(); ++iter1)
    {
        map = this->mat_[ctr];

        for(auto iter2=map.begin(); iter2!=map.end(); ++iter2)
        {
            *iter1 += (iter2->second * v.vec_[iter2->first]);
        }

        ++ctr;
    }

    return retVec;
}


void Matrix::operator= (const Matrix &m)
{
    //std::cout << "operator= (const Matrix &v) called\n";
    size_t size = this->mat_.size();
    assert(m.mat_.size() == size);
    assert(size>0);

    this->mat_ = m.mat_;

}


void Matrix::display()
{
    std::cout << "Display of Matrix:\n";
    size_t size = this->mat_.size();
    assert(size>0);

    std::map<size_t, real> map;

    for(size_t i=0; i<size; ++i)
        {
            map = this->mat_[i];

            std::cout << i  << std::endl;
            for (auto iter=map.begin(); iter!=map.end(); ++iter)
            {
                    //std::cout<<i<<"\t"<<iter->first<<"\t"<<iter->second<<std::endl;
                    std::cout<<"(" << iter->first<<","<<iter->second<< ")"<< "\t";
            }

            std::cout << std::endl;
        }
}
