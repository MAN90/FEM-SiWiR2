#include "Mesh.hpp"

#include<iostream>
#include<fstream> // required for creating ifstream object file_input
#include<string>
#include<cmath>

#include "Colsamm.h"

using namespace :: _COLSAMM_;

void Mesh::readInputFile()
{
	//size_t ctr_V = 0;
	size_t ctr = 0;
	size_t tmp1 = 0;
	real tmp2 = 0.0;
	real tmp3 = 0.0; 	
	std::ifstream file_input;
	std::string wasteLine; // this is used to read the unimportant data from the input file
	
	//opening the input file
	file_input.open("unit_circle.txt");
	
	/*###################################################################
	###############	 First reading the node data	  ###################
	###################################################################*/


	//We don't need to store data from the first two lines
	getline(file_input, wasteLine);

	std::cout<<wasteLine<<std::endl;

	getline(file_input, wasteLine);

	std::cout<<wasteLine<<std::endl;		

	while(file_input.good())
	{
		file_input>> tmp1;
		file_input>> tmp2;
		file_input>> tmp3;
		Vertex tmp(tmp1,tmp2,tmp3);
		nodes_.push_back(tmp);
		nodes_[ctr].n_N_ = ctr;
		//std::cout<<nodes_[ctr].n_N_<<"\t"<<nodes_[ctr].x_<<"\t"<<nodes_[ctr].y_<<"\t ctr :"<< ctr<<std::endl;		
		++ctr;
		
	}
	std::cout<<"ctr is now "<<ctr<<std::endl;
	
	//ktr has now become 1040,+1 due to post-increment and +1 due to reading the additional unwanted entry because it starts with a number but it should be 1038 because actual number of nodes is 1039
	ctr-=2;
	std::cout<<"ctr has been changed to "<<ctr<<std::endl;	
	
	//the additional unwanted entry in the end must be deleted
	std::cout<<"The  size of vector after finishing reading the first part is "<<nodes_.size()<<std::endl;
	nodes_.erase(nodes_.end());

	// setting the value of n_N_Total_	
	n_N_Total_ = nodes_.size();

	std::cout<<"The unwanted entry has been erased"<<std::endl;
	std::cout<<"number of nodes is "<<nodes_.size()<<std::endl;	


	/* 
	//Displaying the node details as stored in nodes_
	for(size_t i=0;i<n_N_Total_;++i)
		std::cout<<i<<"\t"<<nodes_[i].x_<<"\t"<<nodes_[i].y_<<"\t node no.: \t"<< nodes_[i].n_N_<<std::endl;	

	
	*/


	//the stream state becomes invalid after we finish reading the first part and thus must be reset
	if(file_input.is_open())
		std::cout<<"file is still open"<<std::endl;

	if(file_input.good())
		std::cout<<"Stream is in valid state"<<std::endl;
	else
		std::cout<<"Stream is in invalid state & must be reset"<<std::endl;
	
	file_input.clear(); // to reset the stream state 
	
	if(file_input.good())
		std::cout<<"Stream has been reset and is in valid state now"<<std::endl;
	else
		std::cout<<"Some error,...Stream is still in invalid state"<<std::endl;


	/*###################################################################
	###############	 Now reading the element data	  ###################
	###################################################################*/

	wasteLine = "Now trying to get further data";
	std::cout<<wasteLine<<std::endl;
	
	//We don't need to store data from the first two lines
	getline(file_input, wasteLine);

	std::cout<<wasteLine<<std::endl;
	
	getline(file_input, wasteLine);
	
	std::cout<<wasteLine<<std::endl;
	
	
	size_t tmp4=0, tmp5=0;
	size_t ktr=0;	
	while(file_input.good())
	{
		file_input>> tmp1;
		file_input>> tmp4;
		file_input>> tmp5;
		Face tmp(ktr,tmp1,tmp4,tmp5);
		elems_.push_back(tmp);
		//std::cout<<elems_[ktr].n_E_<<"\t"<<elems_[ktr].n_N_1_<<"\t"<<elems_[ktr].n_N_2_<<"\t"<<elems_[ktr].n_N_3_<<"\t ktr \t"<<ktr<<std::endl;		
		++ktr;
		
	}
	std::cout<<"ktr is now "<<ktr<<std::endl;
	
	//ktr has now become 1977, +1 due to post-increment and +1 due to repeatition of last entry but it should be 1975 because actual number of elements is 1976
	ktr-=2;
	std::cout<<"ktr has been changed to "<<ktr<<std::endl;
	
	/* %%%%%%%%%%%%%%%%%%Check for this issue %%%%%%%%%%%%%%%%%%
	the last entry is being repeated and must be deleted
	also checked this in separate file trial1.cpp - this repetition occurs
	*/
	std::cout<<"The  size of vector after finishing reading the file is "<<elems_.size()<<std::endl;
	elems_.erase(elems_.end());
	
	// setting the value of n_E_Total_	
	n_E_Total_ = elems_.size();
	
	std::cout<<"The repeated entry has been erased"<<std::endl;
	std::cout<<"number of elements is "<<elems_.size()<<std::endl;
	
	/*	
	//Displaying the element details as stored in elems_
	for(size_t i=0;i<elems_.size();++i)
		std::cout<<i<<"\t"<<elems_[i].n_E_<<"\t"<<elems_[i].n_N_1_<<"\t"<<elems_[i].n_N_2_<<"\t"<<elems_[i].n_N_3_<<std::endl;	
	*/

	//closing the input file
	file_input.close();


}



/*
Setter function to set the value of the data member delta_
*/
void Mesh::setDelta(const real& del)
{
	delta_ = del;
}


/*
this function computes the value of Ksquare at each node, updates in the nodes_ data structure and writes the result to the file "ksq.txt" 
*/
void Mesh::computeWriteKsq()
{
	std::ofstream  file_output;	
	file_output.open("ksq.txt");
	const size_t sizeNodes = nodes_.size();
	real ksq_tmp =0.0;
	
	std::cout<<"Writing Ksquare to the file"<<std::endl;	

	for(size_t i=0; i<sizeNodes; ++i)
	{
		real x = nodes_[i].x_;
		real y = nodes_[i].y_;
		ksq_tmp = ((100.0+delta_)* exp(-50.0*(x*x + y*y))) - 100.0;
		nodes_[i].kSquare_ = ksq_tmp;
		file_output<<x<<"\t"<<y<<"\t"<<ksq_tmp<<"\n";
		//std::cout<<nodes_[i].kSquare_ <<std::endl;
	}
	file_output.close();

}


/*
this function is used to find the neighbours for each node and store it in the neighbours_ data member of class Vertex 
*/
void Mesh::findNeighbours()
{

	size_t tmp_G_n_1,tmp_G_n_2,tmp_G_n_3;
	for (size_t i=0; i<n_E_Total_; ++i)
	{
		tmp_G_n_1 = elems_[i].n_N_1_;
		tmp_G_n_2 = elems_[i].n_N_2_;
		tmp_G_n_3 = elems_[i].n_N_3_;

		nodes_[tmp_G_n_1].neighbours_.insert(tmp_G_n_2);
		nodes_[tmp_G_n_1].neighbours_.insert(tmp_G_n_3);
		
		nodes_[tmp_G_n_2].neighbours_.insert(tmp_G_n_1);
		nodes_[tmp_G_n_2].neighbours_.insert(tmp_G_n_3);

		
		nodes_[tmp_G_n_3].neighbours_.insert(tmp_G_n_1);
		nodes_[tmp_G_n_3].neighbours_.insert(tmp_G_n_2);
		
	}
	
	//Displaying the neighbours of each node
	/*
	std::set<size_t>::iterator itr,itr_beg,itr_end;
	
	for (size_t j =0; j< n_N_Total_; ++j)
	{
		itr_beg = nodes_[j].neighbours_.begin();
		itr_end = nodes_[j].neighbours_.end();		
		
		std::cout<<"Node No: "<<j<<" has neighbours ";
		for(itr=itr_beg; itr !=itr_end; ++itr)
		{
			std::cout<<*itr<<"\t";
		} 
		std::cout<<std::endl;
	} 

	*/
}



/*
This function computes and returns the value of K-square at a given (x,y) position as required by the Colsamm library.
*/
real Mesh::calcKsq(real x, real y)
{
	return ((100.0+delta_)* exp(-50.0*(x*x + y*y))) - 100.0;
}


/*
This function calls the relevant function to compute the local matrix and assembles it to form the Global Matrix
*/
void Mesh::assemblyDriver(const char& flag)
{
	if(flag == 'A')
	{
		assembleGlobalA();	
	}	
	else if(flag == 'M')
	{	
		assembleGlobalM();
	}
}

void Mesh::assembleGlobalA()
{
	for(size_t i =0; i<n_E_Total_; ++i)
	{
		//computeLocalK(i); //also possible to use this function to avoid code repitition


		ELEMENTS::Triangle shellElem;
		std::vector< std::vector< double > > local_A_Matrix;
		std::vector<double> corners(6, 0.0);
	
		size_t tmp_n1 = elems_[i].n_N_1_;
		size_t tmp_n2 = elems_[i].n_N_2_;
		size_t tmp_n3 = elems_[i].n_N_3_;

		corners[0] = nodes_[tmp_n1].x_; 	corners[1] = nodes_[tmp_n1].y_;
		corners[2] = nodes_[tmp_n2].x_; 	corners[3] = nodes_[tmp_n2].y_;
		corners[4] = nodes_[tmp_n3].x_; 	corners[5] = nodes_[tmp_n3].y_;

		//generating an element by providing the nodal information in the corners vector
		shellElem(corners);
			
		//generating the local stiffness matrix using the intehgrate function from COlsamm
		local_A_Matrix = shellElem.integrate((grad(v_()) * grad(w_())) - (func<double>(calcKsq) * v_() * w_()));	
		
/*
		//Assembling into the Gobal Stiffness Matrix 
		global_A_[tmp_n1][tmp_n1] = local_A_Matrix[0][0];
		global_A_[tmp_n1][tmp_n2] = local_A_Matrix[0][1];
		global_A_[tmp_n1][tmp_n3] = local_A_Matrix[0][2];

		global_A_[tmp_n2][tmp_n1] = local_A_Matrix[1][0];
		global_A_[tmp_n2][tmp_n2] = local_A_Matrix[1][1];
		global_A_[tmp_n2][tmp_n3] = local_A_Matrix[1][2];

		global_A_[tmp_n3][tmp_n1] = local_A_Matrix[2][0];
		global_A_[tmp_n3][tmp_n2] = local_A_Matrix[2][1];
		global_A_[tmp_n3][tmp_n2] = local_A_Matrix[2][2];

		std::cout<<std::endl;
		std::cout<<"the contribution of "<<tmp_n1<<" , "<<tmp_n2<<" is "<< global_A_[tmp_n1][tmp_n2]<<std::endl;
*/
		
		
	//displaying the local matrix
	for(size_t j =0; j<3; ++j)
	{
		for(size_t k=0; k<3; ++k)
		{
			std::cout<<local_A_Matrix[j][k]<<"\t";
		}
		std::cout<<std::endl;
	}

	}
}











void Mesh::assembleGlobalM()
{

}



void Mesh::writeGlobalMatrix(std::vector<std::map<size_t,double>>& A)
{
	for(size_t i=0; i<n_N_Total_; ++i)
	{
		std::set<size_t>::iterator itr,itr_beg,itr_end;

	}

} 





void Mesh::computeLocalK(const size_t& n_e)
{

	ELEMENTS::Triangle shellElem;
	std::vector< std::vector< double > > local_K_Matrix;
	std::vector<double> corners(6, 0.0);
	
	size_t tmp_n1 = elems_[n_e].n_N_1_;
	size_t tmp_n2 = elems_[n_e].n_N_2_;
	size_t tmp_n3 = elems_[n_e].n_N_3_;

	corners[0] = nodes_[tmp_n1].x_; 	corners[1] = nodes_[tmp_n1].y_;
	corners[2] = nodes_[tmp_n2].x_; 	corners[3] = nodes_[tmp_n2].y_;
	corners[4] = nodes_[tmp_n3].x_; 	corners[5] = nodes_[tmp_n3].y_;
	
	//generating an element by providing the nodal information in the corners vector
	shellElem(corners);
	
	local_K_Matrix = shellElem.integrate(grad(v_()) * grad(w_()));	
	
/*
	global_A_[tmp_n1][tmp_n1] = local_K_Matrix[0][0];
	global_A_[tmp_n1][tmp_n2] = local_K_Matrix[0][1];
	global_A_[tmp_n1][tmp_n3] = local_K_Matrix[0][2];

	global_A_[tmp_n2][tmp_n1] = local_K_Matrix[1][0];
	global_A_[tmp_n2][tmp_n2] = local_K_Matrix[1][1];
	global_A_[tmp_n2][tmp_n3] = local_K_Matrix[1][2];

	global_A_[tmp_n3][tmp_n1] = local_K_Matrix[2][0];
	global_A_[tmp_n3][tmp_n2] = local_K_Matrix[2][1];
	global_A_[tmp_n3][tmp_n2] = local_K_Matrix[2][2];
*/



/*
	//writing the info for the vertex object
	nodes_[tmp_n1].nodal_K_Matrix_[tmp_n1] = local_K_Matrix[0][0];
	nodes_[tmp_n1].nodal_K_Matrix_[tmp_n2] = local_K_Matrix[0][1];
	nodes_[tmp_n1].nodal_K_Matrix_[tmp_n3] = local_K_Matrix[0][2];

	nodes_[tmp_n2].nodal_K_Matrix_[tmp_n1] = local_K_Matrix[1][0];
	nodes_[tmp_n2].nodal_K_Matrix_[tmp_n2] = local_K_Matrix[1][1];
	nodes_[tmp_n2].nodal_K_Matrix_[tmp_n3] = local_K_Matrix[1][2];

	nodes_[tmp_n3].nodal_K_Matrix_[tmp_n1] = local_K_Matrix[2][0];
	nodes_[tmp_n3].nodal_K_Matrix_[tmp_n2] = local_K_Matrix[2][1];
	nodes_[tmp_n3].nodal_K_Matrix_[tmp_n3] = local_K_Matrix[2][2];

*/



	//displaying the local matrix
	for(size_t i =0; i<3; ++i)
	{
		for(size_t j=0; j<3; ++j)
		{
			std::cout<<local_K_Matrix[i][j]<<"\t";
		}
		std::cout<<std::endl;
	}			


}



std::vector<std::map<size_t,double>>& Mesh::get_globalA()
{
	return global_A_;
}

