#include <iostream>
#include<vector>
#include<assert.h>

#include "ProblemFormulate.hpp"
#include "EigenSolver.hpp"

real delta; //global variable


int main(int argc, char* argv[])
{	
	
	if(argc<3 )
		std::cout<<"Unsufficient number of input parameters"<<std::endl;
	
	
	delta = std::stod(argv[1]); //intializing the global variable
	
	const real eps = std::stod(argv[2]);	
	
	if(argc==4)
	{
		const size_t reflvl = std::stoi(argv[3]);
		std::cout<<"delta : "<<delta<<"\t epsilon : "<<eps<<"\t refinement level :"<<reflvl<<std::endl;
	}
  	else
	{
		//std::cout<<"delta : "<<delta<<"\t epsilon : "<<eps<<std::endl;
	}

	ProblemFormulate waveguide;
	waveguide.setUpMesh();
	waveguide.computeWriteKsq();
	waveguide.resize_A_M();
	waveguide.computeAssembleGlobalMatrices();
	waveguide.writeGlobalAMatrix();
	waveguide.writeGlobalMMatrix();
	
    EigenSolver  eigen(waveguide.getAMat(), waveguide.getMMat(), eps);
    eigen.inverseIteration();

	return 0;
}


