#ifndef ProblemFormulate_HPP
#define ProblemFormulate_HPP

#include "Mesh.hpp"

#include<map>

extern real delta; //this is a global variable defined in the file main.cpp and intialied in th main() function


class ProblemFormulate
{
	public:
		
		void setUpMesh();// to setup the FE Mesh
		void computeWriteKsq(); // computes and writes K-square to a file
		void resize_A_M(); //to resize the global_A_ and global_M_ data structures
		void computeAssembleGlobalMatrices(); //computes and assembles the A and M matrices
		void assemblerA(const size_t&, const size_t&, const real&); //adds local values into global A matrix
		void assemblerM(const size_t&, const size_t&, const real&); //adds local values into global M matrix
		void writeGlobalAMatrix(); // writes the Global A matrix to a text file 
		void writeGlobalMMatrix(); // writes the Global M matrix to a text file 
		
	private:
		Mesh FEMesh2D_; //Data structure holding the node and element data
		std::vector<std::map<size_t,double>> global_A_; //Data Structure to hold the Global Stiffness Matrix
		std::vector<std::map<size_t,double>> global_M_; //Data Structure to hold the Global Mass Matrix
	
};


#endif

