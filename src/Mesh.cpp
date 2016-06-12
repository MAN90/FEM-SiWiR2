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
	
	std::cout<<"Reading from the input file and generating the nodes and elements"<<std::endl; 	
	
//opening the input file

    file_input.open("unit_circle.txt");
//    file_input.open("unit_circle_fine.txt");
	
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

	std::cout<<"Finished reading the input file - "<<returnSizeNodes()<<" nodes and "<<returnSizeElems()<<"  elements generated"<<std::endl;
}


/*
This function is used to refine the FE Mesh according to the refinement level variable
*/
void Mesh::refineMesh(const size_t& reflvl)
{
	
	std::cout<<"Mesh refinement requested"<<std::endl;
	std::cout<<"Mesh will be refined "<<reflvl<<" times"<<std::endl;

	size_t tmp_n1,tmp_n2,tmp_n3, loopLimit;
	int loc_1, loc_2, loc_3; 
	real X,Y;


	for(size_t k=1; k<=reflvl; ++k)
	{
		loopLimit = returnSizeElems(); // loopLimit is set to size of elems_ before refinement
	
		for(size_t i=0; i<loopLimit; ++i)
		{


// Reading the global node numbers of the nodes of the original element
			tmp_n1 = returnN1element(i);
			tmp_n2 = returnN2element(i);
			tmp_n3 = returnN3element(i);		

// displaying the size of nodes_ vector before refinement 
			//std::cout<<"Size of nodes_ before refinement is "<<returnSizeNodes()<<std::endl;

// Generating the new nodes and inserting into the nodes_ vector;
			X = (returnXvertex(tmp_n1) + returnXvertex(tmp_n2))/2;
			Y = (returnYvertex(tmp_n1) + returnYvertex(tmp_n2))/2;
			loc_1 = checkNodeExistence(X,Y);
			if(loc_1 == -1)
			{
				Vertex tmpNode_4(X,Y );
				nodes_.push_back(tmpNode_4);
				loc_1 = returnSizeNodes() -1;
			}
					

			X = (returnXvertex(tmp_n2) + returnXvertex(tmp_n3))/2;
			Y = (returnYvertex(tmp_n2) + returnYvertex(tmp_n3))/2;
			loc_2 = checkNodeExistence(X,Y);
			if(loc_2 == -1)
			{
				Vertex tmpNode_5(X,Y );
				nodes_.push_back(tmpNode_5);
				loc_2 = returnSizeNodes() -1;
			}

			X = (returnXvertex(tmp_n3) + returnXvertex(tmp_n1))/2;
			Y = (returnYvertex(tmp_n3) + returnYvertex(tmp_n1))/2;
			loc_3 = checkNodeExistence(X,Y);
			if(loc_3 == -1)
			{
				Vertex tmpNode_6(X,Y );
				nodes_.push_back(tmpNode_6);
				loc_3 = returnSizeNodes() -1;
			}

			//std::cout<<"Finished generating  3 new nodes"<<std::endl;
			//std::cout<<"Size of nodes_ shoulb be +3, but actual is "<<nodes_.size()<<std::endl;

// making new elements to refine the mesh and inserting them into the elems_ vector;
			//std::cout<<"Size of elems_ before refinement is "<<elems_.size()<<std::endl;

			Face tmpElem_1(tmp_n1, loc_1, loc_3);
			elems_.push_back(tmpElem_1);

			Face tmpElem_2(tmp_n2, loc_1, loc_2);
			elems_.push_back(tmpElem_2);

			Face tmpElem_3(loc_1,loc_2,loc_3);
			elems_.push_back(tmpElem_3);

			Face tmpElem_4(tmp_n3, loc_2,loc_3);
			elems_.push_back(tmpElem_4);		

			//std::cout<<"Finished generating 4 new elements"<<std::endl;
			//std::cout<<"Size of nodes_ shoulb be +4, but actual is "<<elems_.size()<<std::endl;
			//std::cout<<"Deleting the first element from the elems_ vector"<<std::endl;
			//elems_.erase(elems_.begin());
				
		}
/*
		std::cout<<"Finished Generating new nodes and elements"<<std::endl;
		std::cout<<"The mesh now has "<<nodes_.size()<<" nodes and "<<elems_.size()<<"  elements"<<std::endl;
		std::cout<<"Now erasing the old elements"<<std::endl;
*/

// erasing the old elements from the elems_ vector;

		for(size_t j = 0; j<loopLimit; ++j)
			elems_.erase(elems_.begin());


		std::cout<<"Mesh refinement Completed "<<k<<" time(s)"<< std::endl;	
		std::cout<<"The mesh now has "<<nodes_.size()<<" nodes and "<<elems_.size()<<"  elements"<<std::endl;		

	}
	std::cout<<"After refinement, the mesh has "<<nodes_.size()<<" nodes and "<<elems_.size()<<"  elements"<<std::endl;
	writeRefinedMesh();

}

/*
This function checks if the given (X,Y) point already exists in the nodes_ vector
This is required to maintain the node connectivity during mesh refinement
It returns the index of the node if it exists, else returns -1
*/
int Mesh::checkNodeExistence(const real& X, const real& Y)
{
	const size_t loopLimit = returnSizeNodes();
	size_t location =-1;

	for(size_t i=0; i<loopLimit; ++i)
	{
		if(returnXvertex(i) == X && returnYvertex(i) == Y)
		{				
			location = i;
		}
	}
	
	return location;

}


/*
This function writes the refined nodes_ and elems_ data to "refined_nodes.txt" and "refined_nodes.txt" respectively
*/
void Mesh::writeRefinedMesh()
{
	
	   
    

	/*###################################################################
	###############	 Now writing the refine nodes data	  ###############
	###################################################################*/
	const size_t sizeNodes = returnSizeNodes();	
	real x,y;	
	std::ofstream  write_nodes_file;
	write_nodes_file.open("refined_nodes.txt");

    std::cout<<"Writing the refined nodes to the file"<<std::endl;


    for(size_t i=0; i<sizeNodes; ++i)
    {
        x = returnXvertex(i);
       	y = returnYvertex(i);
      
        write_nodes_file<<i<<"\t"<<x<<"\t"<<y<<"\n";

    }
    write_nodes_file.close();

	/*###################################################################
	###############	 Now writing the refined elems data	  ###############
	###################################################################*/
	const size_t sizeElems = returnSizeElems();
	size_t n1,n2,n3;	
	std::ofstream  write_elems_file;
	write_elems_file.open("refined_elems.txt");

    std::cout<<"Writing the refined elems to the file"<<std::endl;


    for(size_t i=0; i<sizeElems; ++i)
    {
		n1 = returnN1element(i);
		n2 = returnN2element(i);
		n3 = returnN3element(i);
        
		write_elems_file<<n1<<"\t"<<n2<<"\t"<<n3<<"\n";
    }
    write_elems_file.close();


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

