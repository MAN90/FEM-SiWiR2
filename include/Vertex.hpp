/*
This class provides the facility to store the vertex number, x-y coordinates of grid point 
*/

#include <cstddef>
#include<set>
#include<map>

typedef double real;

#ifndef Vertex_HPP 
#define Vertex_HPP 

class Vertex
{
	public:
		//Vertex();		
		Vertex(const size_t&, const real&, const real&);
		~Vertex();
		inline void set_Vertex(const size_t&, const real&, const real&);
		//std::operator<<(std::ostream&, const Vertex&);
			
	
	//private:
		size_t n_N_;
		real x_;
		real y_;
		real kSquare_;
		std::set<size_t> neighbours_;
		std::map<size_t,double> nodal_K_Matrix_;
};


#endif
