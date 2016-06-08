#include "Vertex.hpp"


/*
Vertex::Vertex()
{

}
*/


Vertex::Vertex(const size_t & n, const real& xval, const real& yval)
{
	n_N_ = n;
	x_ = xval;
	y_ = yval;
	
}

inline void Vertex::set_Vertex(const size_t & n, const real& xval, const real& yval)
{
	n_N_ = n;
	x_ = xval;
	y_ = yval;
	
}

Vertex::~Vertex()
{

}
