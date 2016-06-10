
#include "ProblemFormulate.hpp"

#include<iostream>
#include<fstream> // required for creating ofstream object file_output
#include<cmath>	// required for the exp function in computeWriteKsq()
#include <utility> //reuires for std::pair

#include "Colsamm.h"

using namespace :: _COLSAMM_;

/*
This is a free function which computes and returns the value of K-square at a given (x,y) position.
This is required for the integrate function used in
*/
real calcKsq(real x, real y)
{
    return ((100.0+delta)* exp(-50.0*(x*x + y*y))) - 100.0;
}


/*
This function is for setting up the FE mesh from the input file
*/
void ProblemFormulate::setUpMesh()
{
    std::cout<<"Setting up the Finite Element Mesh"<<std::endl;
    FEMesh2D_.readInputFile();
}



Mat& ProblemFormulate::getAMat()
{
    return global_A_;
}

Mat& ProblemFormulate::getMMat()
{
    return global_M_;
}


/*
this function computes the value of Ksquare at each node and writes the result to the file "ksq.txt"
*/
void ProblemFormulate::computeWriteKsq()
{
    std::ofstream  file_output;
    file_output.open("ksq.txt");
    const size_t sizeNodes = FEMesh2D_.returnSizeNodes();
    real ksq_tmp =0.0;

    std::cout<<"Writing Ksquare to the file"<<std::endl;

    //std::cout<<"The value of delta is  "<<delta<<std::endl;


    for(size_t i=0; i<sizeNodes; ++i)
    {
        real x = FEMesh2D_.returnXvertex(i);
        real y = FEMesh2D_.returnYvertex(i);
        ksq_tmp = ((100.0+delta)* exp(-50.0*(x*x + y*y))) - 100.0;
        file_output<<x<<"\t"<<y<<"\t"<<ksq_tmp<<"\n";

    }
    file_output.close();

}

/*
This function resizes the data structures global_A_ and global_M_ to number of nodes in the mesh
*/
void ProblemFormulate::resize_A_M()
{
    const size_t n = FEMesh2D_.returnSizeNodes();
    global_A_.resize(n);
    global_M_.resize(n);
}


/*
This function computes the local Stiffness and Matrices matrices for each element & assembles them to form the global Stiffness and Mass matrices
*/
void ProblemFormulate::computeAssembleGlobalMatrices()
{
    const size_t sizeElems = FEMesh2D_.returnSizeElems();

    for(size_t i =0; i<sizeElems; ++i)
    {

        ELEMENTS::Triangle shellElem;
        std::vector< std::vector< double > > local_A_Matrix, local_M_Matrix;
        std::vector<double> corners(6, 0.0);

        size_t tmp_n1 = FEMesh2D_.returnN1element(i);
        size_t tmp_n2 = FEMesh2D_.returnN2element(i);
        size_t tmp_n3 = FEMesh2D_.returnN3element(i);

//assembling the corners vector necessary to generate the element
        corners[0] = FEMesh2D_.returnXvertex(tmp_n1); 	corners[1] = FEMesh2D_.returnYvertex(tmp_n1);
        corners[2] = FEMesh2D_.returnXvertex(tmp_n2);	corners[3] = FEMesh2D_.returnYvertex(tmp_n2);
        corners[4] = FEMesh2D_.returnXvertex(tmp_n3); 	corners[5] = FEMesh2D_.returnYvertex(tmp_n3);

//generating an element by providing the nodal information in the corners vector
        shellElem(corners);


        /*###################################################################
        ########	Assembling the Stiffness Matrix		#############
        ###################################################################*/

//generating the local stiffness matrix using the intehgrate function from Colsamm
        local_A_Matrix = shellElem.integrate((grad(v_()) * grad(w_())) - (func<double>(calcKsq) * v_() * w_()));
//Assembling the local vlaues into the Global Matrix
        assemblerA(tmp_n1,tmp_n1,local_A_Matrix[0][0]);
        assemblerA(tmp_n1,tmp_n2,local_A_Matrix[0][1]);
        assemblerA(tmp_n1,tmp_n3,local_A_Matrix[0][2]);

        assemblerA(tmp_n2,tmp_n1,local_A_Matrix[1][0]);
        assemblerA(tmp_n2,tmp_n2,local_A_Matrix[1][1]);
        assemblerA(tmp_n2,tmp_n3,local_A_Matrix[1][2]);

        assemblerA(tmp_n3,tmp_n1,local_A_Matrix[2][0]);
        assemblerA(tmp_n3,tmp_n2,local_A_Matrix[2][1]);
        assemblerA(tmp_n3,tmp_n3,local_A_Matrix[2][2]);


        /*###################################################################
        ########	Assembling the Mass Matrix		#############
        ###################################################################*/

//generating the local mass matrix using the intehgrate function from Colsamm
        local_M_Matrix = shellElem.integrate( v_() * w_());

//Assembling the local vlaues into the Global Matrix
        assemblerM(tmp_n1,tmp_n1,local_M_Matrix[0][0]);
        assemblerM(tmp_n1,tmp_n2,local_M_Matrix[0][1]);
        assemblerM(tmp_n1,tmp_n3,local_M_Matrix[0][2]);

        assemblerM(tmp_n2,tmp_n1,local_M_Matrix[1][0]);
        assemblerM(tmp_n2,tmp_n2,local_M_Matrix[1][1]);
        assemblerM(tmp_n2,tmp_n3,local_M_Matrix[1][2]);

        assemblerM(tmp_n3,tmp_n1,local_M_Matrix[2][0]);
        assemblerM(tmp_n3,tmp_n2,local_M_Matrix[2][1]);
        assemblerM(tmp_n3,tmp_n3,local_M_Matrix[2][2]);
    }

}

/*
this function takes the local stiffness values into their appropriate postions in the global Data Structure
*/
void ProblemFormulate::assemblerA(const size_t& n1, const size_t& n2, const real& val)
{

        std::pair<std::map<size_t,real>::iterator,bool> checker;
        checker = global_A_[n1].insert(std::pair<size_t,real> (n2,val));
        if (checker.second == false)
        {
            //std::cout<<"A vlaue "<<checker.first->second<< " already exists at the position "<<n1<<","<<n2<<std::endl;
            //std::cout<<"Adding the new value of "<<val<<" to the old value"<<std::endl;


            global_A_[n1][n2] += val;

            //std::cout<<"The changed value is "<<global_A_[n1][n2]<<std::endl;
        }
        else
        {
            //std::cout<<"No value exists at the position "<<n1<<","<<n2<<std::endl;
            //std::cout<<"Inserting the value "<<val<<std::endl;
            //std::cout<<"the inserted value is  "<<global_A_[n1][n2]<<std::endl;
        }


}


/*
this function takes the local Mass values into their appropriate postions in the global Data Structure
*/
void ProblemFormulate::assemblerM(const size_t& n1, const size_t& n2, const real& val)
{

        std::pair<std::map<size_t,real>::iterator,bool> checker;
        checker = global_M_[n1].insert(std::pair<size_t,real> (n2,val));
        if (checker.second == false)
        {
            //std::cout<<"A vlaue "<<checker.first->second<< " already exists at the position "<<n1<<","<<n2<<std::endl;
            //std::cout<<"Adding the new value of "<<val<<" to the old value"<<std::endl;


            global_M_[n1][n2] += val;

            //std::cout<<"The changed value is "<<global_M_[n1][n2]<<std::endl;
        }
        else
        {
            //std::cout<<"No value exists at the position "<<n1<<","<<n2<<std::endl;
            //std::cout<<"Inserting the value "<<val<<std::endl;
            //std::cout<<"the inserted value is  "<<global_M_[n1][n2]<<std::endl;
        }


}


/*
This function writes the Global Stiffness Matrix to the file "A.txt"
*/
void ProblemFormulate::writeGlobalAMatrix()
{
    std::ofstream  file_A_output;
    file_A_output.open("A.txt");
    const size_t sizeA = global_A_.size();

    std::map<size_t,real>::iterator itr,itr_beg,itr_end;


    /*###################################################################
    ###############		Writing the A Matrix to file	#############
    ###################################################################*/
    std::cout<<"Writing The Global A Matrix to the file"<<std::endl;

    for(size_t i=0; i<sizeA; ++i)
    {
        itr_beg = global_A_[i].begin();
        itr_end = global_A_[i].end();

        for (itr=itr_beg; itr!=itr_end; ++itr)
        {
                file_A_output<<i<<"\t"<<itr->first<<"\t"<<itr->second<<std::endl;
        }
    }
    file_A_output.close();
}

/*
This function writes the Global Mass Matrix to the file "A.txt"
*/
void ProblemFormulate::writeGlobalMMatrix()
{
    std::ofstream  file_M_output;
    file_M_output.open("M.txt");
    const size_t sizeM = global_M_.size();

    std::map<size_t,real>::iterator itr,itr_beg,itr_end;


    /*###################################################################
    ###############		Writing the M Matrix to file	#############
    ###################################################################*/
    std::cout<<"Writing The Global M Matrix to the file"<<std::endl;

    for(size_t i=0; i<sizeM; ++i)
    {
        itr_beg = global_M_[i].begin();
        itr_end = global_M_[i].end();

        for (itr=itr_beg; itr!=itr_end; ++itr)
        {
                file_M_output<<i<<"\t"<<itr->first<<"\t"<<itr->second<<std::endl;
        }
    }
    file_M_output.close();
}
