#ifndef Mesh_HPP
#define Mesh_HPP


#include<vector>
#include<map>

#include"Vertex.hpp"
#include"Face.hpp"


class Mesh{

	public:
		void readInputFile();// to read input from the file and initialize the nodes_ and elems_
		void findNeighbours();//to find the neighbours of each node				
		size_t returnSizeNodes(); //to get the size of the nodes_ vector
		size_t returnSizeElems(); //to get the size of the elems_ vector
		real& returnXvertex(const size_t &); //to get the x-coordinate of a vertex 
		real& returnYvertex(const size_t &); //to get the Y-coordinate of a vertex 
		size_t returnN1element(const size_t &); //to get global number of 1st node of an element
		size_t returnN2element(const size_t &); //to get global number of 2nd node of an element
		size_t returnN3element(const size_t &); //to get global number of 3rd node of an element

	private:
		size_t n_N_Total_;
		size_t n_E_Total_;
		std::vector<Vertex> nodes_;
		std::vector<Face> elems_;
};

#endif
