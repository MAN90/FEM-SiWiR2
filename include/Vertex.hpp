/*
This class provides the facility to store the vertex number, x-y coordinates of grid point 
*/
#ifndef Vertex_HPP
#define Vertex_HPP

#include <cstddef>
#include<set>
#include<map>
//#include "Type.hpp"

typedef double real;



class Vertex
{
	public:
		Vertex(const real&, const real&); //constructor to intialize the vertex
		~Vertex();
			
	//private:
		real x_;// x-coordinate of the vertex 
		real y_;// y-coordinate of the vertex
		std::set<size_t> neighbours_;// data structure to store the global numbers of neighbouring nodes
};


#endif
