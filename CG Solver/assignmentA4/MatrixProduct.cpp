#include<iostream>
#include "Matrix.h"
using std::cout;
using std::cin;
using std::endl;
using std::string; 

template <class T>
void init(int row, int col, Matrix<T> &mat)
{ 
	
	cout<<"Please enter Matrix elements row by row" << endl;

	for(int i=0;i<row;++i)
   	{
		for(int j=0;j<col;++j)
		{
		cin >> mat(i,j) ; 
		}
	}

}

int main()
{
	int s1,s2,s3;
	string type;
	cout<<"Please enter the three numbers s1, s2, s3" << endl;
	cin>> s1 >> s2 >> s3;

	cout<<"Please enter data type of string elements" << endl;
	cin>>type;
	
	
	if(type == "int")
	{		
		
		Matrix< int > m1(s1,s2);
		Matrix< int > m2(s2,s3);
		Matrix< int > m3(s1,s3);
		init(s1,s2,m1);
		init(s2,s3,m2);
		m3 = m1*m2;
		cout<<m3<<endl;
	}
		
	else if(type == "double")
	{
		Matrix< float > m1(s1,s2);
		Matrix< float > m2(s2,s3);
		Matrix< float > m3(s1,s3);
		init(s1,s2,m1);
		init(s2,s3,m2);
		m3 = m1*m2;
		cout<<m3<<endl;

	}

	else if(type == "float")
	{	
		Matrix< double > m1(s1,s2);
		Matrix< double > m2(s2,s3);
		Matrix< double > m3(s1,s3);
		init(s1,s2,m1);
		init(s2,s3,m2);
		m3 = m1*m2;
		cout<<m3<<endl;
	}

	else
	cout<<"Data Type Error: The data type should be int, double or float"<<endl;
	
	return 0;	

}		



