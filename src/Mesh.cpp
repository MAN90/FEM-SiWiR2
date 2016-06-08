#include "Mesh.hpp"

#include<iostream>
#include<fstream> // required for creating ifstream object file_input
#include<string>
#include<cmath>

/*
This function reads the input from the file "unit_circle.txt" and intializes the nodes_ and elems_ data structures
*/
void Mesh::readInputFile()
{
	size_t ctr = 0;
	size_t tmpwaste = 0;
	real tmp1 = 0.0;
	real tmp2 = 0.0; 	
	std::ifstream file_input;
	std::string wasteLine; // this is used to read the unimportant data from the input file
	
//opening the input file
	file_input.open("unit_circle.txt");
	
	/*###################################################################
	###############	 First reading the node data	  ###################
	###################################################################*/


//We don't need to store data from the first two lines
	getline(file_input, wasteLine);
	//std::cout<<wasteLine<<std::endl;

	getline(file_input, wasteLine);
	//std::cout<<wasteLine<<std::endl;		

	while(file_input.good())
	{
		file_input>> tmpwaste;
		file_input>> tmp1;
		file_input>> tmp2;
		Vertex tmp(tmp1,tmp2);
		nodes_.push_back(tmp);
		//std::cout<<"Node No. \t"<<ctr<<"\t x-value : \t"<<nodes_[ctr].x_<<"\t y-vlaue: \t"<<nodes_[ctr].y_<<std::endl;		
		++ctr;
		
	}
	//std::cout<<"ctr is now "<<ctr<<std::endl;
	
//ctr has now become 1040,+1 due to post-increment and +1 due to reading the additional unwanted entry because it starts with a number but it should be 1038 because actual number of nodes is 1039
	ctr-=2;
	//std::cout<<"ctr has been changed to "<<ctr<<std::endl;	
	
//the additional unwanted entry in the end must be deleted
	//std::cout<<"The  size of nodes vector after finishing input reading is "<<nodes_.size()<<std::endl;
	nodes_.erase(nodes_.end());
/*	
	std::cout<<"The unwanted entry has been erased"<<std::endl;
	std::cout<<"number of nodes is "<<nodes_.size()<<std::endl;
	std::cout<<std::endl;	
*/

	
//Displaying the node details as stored in nodes_
/*
	for(size_t i=0;i<nodes_.size();++i)
		std::cout<<"Node No. \t"<<i<<"\t x-value : \t"<<nodes_[i].x_<<"\t y-vlaue: \t"<<nodes_[i].y_<<std::endl;
*/


//the stream state becomes invalid after we finish reading the first part and thus must be reset
/*
	if(file_input.is_open())
		std::cout<<"file is still open"<<std::endl;

	if(file_input.good())
		std::cout<<"Stream is in valid state"<<std::endl;
	else
		std::cout<<"Stream is in invalid state & must be reset"<<std::endl;
*/
	
	file_input.clear(); // to reset the stream state 

/*
	if(file_input.good())
		std::cout<<"Stream has been reset and is in valid state now"<<std::endl;
	else
		std::cout<<"Some error,...Stream is still in invalid state"<<std::endl;
	std::cout<<std::endl;	
*/
	
	/*###################################################################
	###############	 Now reading the element data	  ###################
	###################################################################*/
/*
	wasteLine = "Now trying to get further data";
	std::cout<<wasteLine<<std::endl;
*/	
//We don't need to store data from the first two lines
	getline(file_input, wasteLine);

//	std::cout<<wasteLine<<std::endl;
	
	getline(file_input, wasteLine);
	
//	std::cout<<wasteLine<<std::endl;
	
	
	size_t tmp3=0, tmp4=0, tmp5=0;
	size_t ktr=0;	
	while(file_input.good())
	{
		file_input>> tmp3;
		file_input>> tmp4;
		file_input>> tmp5;
		Face tmp(tmp3,tmp4,tmp5);
		elems_.push_back(tmp);
		//std::cout<<"Element : "<<ktr<<"\t"<<elems_[ktr].n_N_1_<<"\t"<<elems_[ktr].n_N_2_<<"\t"<<elems_[ktr].n_N_3_<<std::endl;		
		++ktr;
		
	}
	//std::cout<<"ktr is now "<<ktr<<std::endl;
//ktr has now become 1977, +1 due to post-increment and +1 due to repeatition of last entry but it should be 1975 because actual number of elements is 1976
	ktr-=2;
	//std::cout<<"ktr has been changed to "<<ktr<<std::endl;
	
	/* %%%%%%%%%%%%%%%%%%Check for this issue %%%%%%%%%%%%%%%%%%
	the last entry is being repeated and must be deleted
	also checked this in separate file trial1.cpp - this repetition occurs
	*/

//the additional unwanted entry in the end must be deleted
	//std::cout<<"The  size of vector after finishing reading the file is "<<elems_.size()<<std::endl;

	elems_.erase(elems_.end());
/*
	std::cout<<"The repeated entry has been erased"<<std::endl;
	std::cout<<"number of elements is "<<elems_.size()<<std::endl;
	std::cout<<std::endl;
*/	

//Displaying the element details as stored in elems_
/*
	for(size_t i=0;i<elems_.size();++i)
		std::cout<<"Element : "<<i<<"\t"<<elems_[i].n_N_1_<<"\t"<<elems_[i].n_N_2_<<"\t"<<elems_[i].n_N_3_<<std::endl;
*/

//closing the input file
	file_input.close();
}


/*
This is a getter function which returns the size of the nodes_ vector
*/
size_t Mesh::returnSizeNodes()
{
	return nodes_.size();
}


/*
This is a getter function which returns the size of the elems_ vector
*/
size_t Mesh::returnSizeElems()
{
	return elems_.size();
}


/*
This is a getter function which returns the x-coordinate of i-th vertex in the nodes vector
*/
real& Mesh::returnXvertex(const size_t & i)
{
	return nodes_[i].x_ ;
}


/*
This is a getter function which returns the Y-coordinate of i-th vertex in the nodes vector
*/
real& Mesh::returnYvertex(const size_t & i)
{
	return nodes_[i].y_ ;
}


/*
This is a getter function which returns the global number of local node 1 of the i-th face in the elements vector
*/
size_t Mesh::returnN1element(const size_t & i)
{
	return elems_[i].n_N_1_ ;
}


/*
This is a getter function which returns the global number of local node 2 of the i-th face in the elements vector
*/
size_t Mesh::returnN2element(const size_t & i)
{
	return elems_[i].n_N_2_ ;
}


/*
This is a getter function which returns the global number of local node 3 of the i-th face in the elements vector
*/
size_t Mesh::returnN3element(const size_t & i)
{
	return elems_[i].n_N_3_ ;
}


/*
this function is used to find the neighbours for each node and store it in the neighbours_ data member of class Vertex 
*/
void Mesh::findNeighbours()
{

	size_t tmp_G_n_1,tmp_G_n_2,tmp_G_n_3;
	const size_t sizeElems = elems_.size();
	
	for (size_t i=0; i<sizeElems; ++i)
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
	const size_t sizeNodes = nodes_.size();
	for (size_t j =0; j< sizeNodes; ++j)
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

