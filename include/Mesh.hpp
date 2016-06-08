#ifndef Mesh_HPP
#define Mesh_HPP


#include<vector>
#include<map>

#include"Vertex.hpp"
#include"Face.hpp"


class Mesh{

	public:
		void readInputFile();	//this function reads input from the file and initializes the nodes_ and elems_ data structures
		void computeWriteKsq(); // computes and writes K-square to a file
		void findNeighbours();		
		void assemblyDriver(const char&);// takes the flag and does the assembly of that particular matrix

	
		real calcKsq(real ,real); // computes Ksq as reuired for Colsamm 
		
		void assembleGlobalA();
		void assembleGlobalM();
		void writeGlobalMatrix(std::vector<std::map<size_t,double>> & );
		void computeLocalK(const size_t&); // here, the arguement is the element 	
		

		void setDelta(const real&); //setter function to set the value of Delta
		std::vector<std::map<size_t,double>>& get_globalA();


	private:
		size_t n_N_Total_;
		size_t n_E_Total_;
		std::vector<Vertex> nodes_;
		std::vector<Face> elems_;
		real delta_; // it is better to make delta a data member of mesh class as it is required in calcKsq function, which is an input to Colsamm functions.
		std::vector<std::map<size_t,double>> global_A_;		
		


};

#endif
