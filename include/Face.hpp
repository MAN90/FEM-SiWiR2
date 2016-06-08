/*
This class provides the facility to store the node numbers for an element 
*/

#include <cstddef>

#ifndef Face_HPP
#define Face_HPP

class Face
{
	public:
		Face(const size_t&, const size_t&, const size_t&); //constructor to intialize the vertex
		~Face();
		
	//private: 
		size_t n_N_1_; // global number of local node 1
		size_t n_N_2_; // global number of local node 2
		size_t n_N_3_; // global number of local node 3
};	


#endif
