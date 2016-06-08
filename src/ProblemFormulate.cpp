#include "ProblemFormulate.hpp"

ProblemFormulate::~ProblemFormulate()
{

}


/*
This function is for setting up the FE mesh from the input file, computing the Ksquare values, computing the local stiffness matrices and assembling them to obtain the global A and M matrices
*/
void ProblemFormulate::setUpMesh(const real& delta)
{
	FEMesh2D_.setDelta(delta);
	FEMesh2D_.readInputFile();
	FEMesh2D_.computeWriteKsq();
	FEMesh2D_.findNeighbours();	
	FEMesh2D_.assemblyDriver('A');  // here, A is the flag to denote the computation of Stiffness matrix
	//FEMesh2D_.writeGlobalMatrix(FEMesh2D_.get_globalA());
//	FEMesh2D_.computeLocalK();

}

