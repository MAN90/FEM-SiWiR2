#include "Face.hpp"

/*

Face::Face()
{

}

*/

Face::Face(const size_t& n, const size_t& n1, const size_t& n2, const size_t& n3)
{
	n_E_ = n;
	n_N_1_ = n1;
	n_N_2_ = n2;
	n_N_3_ = n3;	

}



inline void Face::set_Face(const size_t& n, const size_t& n1, const size_t& n2, const size_t& n3)
{
	n_E_ = n;
	n_N_1_ = n1;
	n_N_2_ = n2;
	n_N_3_ = n3;
}

Face::~Face()
{

}
