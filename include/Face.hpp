/*
This class provides the facility to store the node numbers for an element 
*/

#include <cstddef>

#ifndef Face_HPP
#define Face_HPP

class Face
{
	public:
		//Face();
		Face(const size_t&, const size_t&, const size_t&, const size_t&);
		~Face();
		inline void set_Face(const size_t&, const size_t&, const size_t&, const size_t&);		
		


	//private:
		size_t n_E_; // element number 
		size_t n_N_1_; // global number of node-1
		size_t n_N_2_; // global number of node-2
		size_t n_N_3_; // global number of node-3
};	


#endif
