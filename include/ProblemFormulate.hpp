#ifndef ProblemFormulate_HPP
#define ProblemFormulate_HPP

#include "Mesh.hpp"

class ProblemFormulate
{
	public:
		//ProblemFormulate();
		~ProblemFormulate();
		void setUpMesh(const real&);
		
	private:
		Mesh FEMesh2D_;
	
	
};


#endif

