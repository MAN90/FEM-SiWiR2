#include <iostream>
#include<vector>
#include<assert.h>

#include "ProblemFormulate.hpp"




int main(int argc, char* argv[])
{	
	
	if(argc<3 )
		std::cout<<"Unsufficient number of input parameters"<<std::endl;
	
	
	const real delta = std::stod(argv[1]);
	const real eps = std::stod(argv[2]);	
	
	if(argc==4)
	{
		const size_t reflvl = std::stoi(argv[3]);
		std::cout<<"delta : "<<delta<<"\t epsilon : "<<eps<<"\t refinement level :"<<reflvl<<std::endl;
	}
  	else
		std::cout<<"delta : "<<delta<<"\t epsilon : "<<eps<<std::endl;


	ProblemFormulate waveguide_;
	waveguide_.setUpMesh(delta);

	return 0;
}


