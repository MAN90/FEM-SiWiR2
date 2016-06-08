#include "Face.hpp"

/*
This is the constructor and is used to set the node numbers for the local nodes of an element
*/
Face::Face(const size_t& n1, const size_t& n2, const size_t& n3)
{
	n_N_1_ = n1;
	n_N_2_ = n2;
	n_N_3_ = n3;	

}

Face::~Face()
{

}
