#include<assert.h>
#include<iostream>
#include<fstream>

using std::cout;
using std::cin;
using std::endl;
using std::ostream;

//template <class T>
class Matrix 
{
	private :
	int m;
	int n;
	T *ptr;

	public :
	
	int getNumRows()
	{
	return m;
	}

	int getNumCols()
	{
	return n;
	}

	Matrix(int nrow, int ncol, T val);  // Constructor
	Matrix(int nrow, int ncol);
	~Matrix();				// Destructor
	Matrix(const Matrix &obj);		// Copy Constructor
	Matrix & operator= (const Matrix &obj);  //Copy Assignment Operator

	Matrix operator+ (const Matrix &obj);
	Matrix  operator- (const Matrix &obj);
	Matrix operator* (const Matrix &obj);

	T operator() (int r, int c) const;
	T& operator() (int r, int c);

	Matrix & operator+= (const Matrix &obj);
	Matrix & operator-= (const Matrix &obj);
	Matrix operator*= (const Matrix &obj);

	bool operator== (const Matrix &obj);
	bool operator!= (const Matrix &obj);
	
	//template <class T>;
	//template<class U>
 	//friend ostream& operator<< (ostream& os, const Matrix<U>& obj); 
	/*A<U> foo(A<U>& a);
	template <typename Type> // this is the template parameter declaration
	friend ostream& operator<< (ostream& os, const Type &obj);*/

	void displayMatrix() const;


} ;



template <class T>
Matrix<T> :: Matrix (int nrow, int ncol)  // Constructor
	{

	//cout<<"\nConstructor called for "<< nrow <<" rows and "<< ncol << " columns" << endl; 

	m = nrow;
	n = ncol;
	ptr = new T[m*n];

	for(int i=0 ; i < m*n ; ++i)
	    {	
	      *(ptr+i)=0;
	    }

	}


template <class T>
Matrix<T> :: Matrix (int nrow, int ncol, T val)  // Constructor
	{

	//cout<<"\nConstructor called for "<< nrow <<" rows and "<< ncol << " columns" << endl; 

	m = nrow;
	n = ncol;
	ptr = new T[m*n];

	for(int i=0 ; i < m*n ; ++i)
	    {	
	      *(ptr+i)=val;
	    }

	}

template <class T>	
Matrix<T>::Matrix(const Matrix &obj)       // Copy Constructor
	 {
	   
	 // cout<<"\nCopy constructor called"<<endl;
	  
	  this->m=obj.m;
	  this->n=obj.n;
	  
	  ptr = new T[m*n];
	  
	  for(int i=0 ; i < m*n ; ++i)
	    {	
	      *(ptr+i)=*(obj.ptr+i);
	    }
	 }

template <class T>	 
Matrix<T> & Matrix<T>::operator=(const Matrix &obj)
	 {
	  //cout<<"\nCopy assignment operator called"<<endl;
	  
	  if(this != &obj)
	  {
	   
	      m=obj.m;
	      n=obj.n;
	  
	      for(int i=0 ; i < m*n ; ++i)
	      {	
	      *(ptr+i)=*(obj.ptr+i);
	      }
	  
	  }
	  
	  return *this;
	  
	 }

template <class T>
Matrix<T>  Matrix<T>::operator+ (const Matrix &obj)
{
	assert(obj.m == this->m);
	assert(obj.n == this->n);

	//for(int i=0; i<m*n ; ++i)
		//*(this->ptr+i) = (*(this->ptr + i)) + (*(obj.ptr +i));
	
	Matrix temp(*this);
	temp += obj;

	return temp;
}

template <class T>
Matrix<T> & Matrix<T>::operator+= (const Matrix &obj)
{
	assert(obj.m == this->m);
	assert(obj.n == this->n);

	for(int i=0; i<m*n ; ++i)
		*(this->ptr+i) = (*(this->ptr + i)) + (*(obj.ptr +i));

	return *this;
}

template <class T>
Matrix<T>  Matrix<T>::operator- (const Matrix &obj)
{
	assert(obj.m == this->m);
	assert(obj.n == this->n);

	Matrix temp(*this);
	temp -= obj;

	return temp;
}	

template <class T>
Matrix<T> & Matrix<T>::operator-= (const Matrix &obj)
{
	assert(obj.m == this->m);
	assert(obj.n == this->n);

	for(int i=0; i<m*n ; ++i)
		*(this->ptr+i) = (*(this->ptr + i)) - (*(obj.ptr +i));

	return *this;
}


template <class T>
Matrix<T> Matrix<T>::operator* (const Matrix &obj)
{
	assert(this->n == obj.m);

	Matrix m3(this->m, obj.n,0.0); 

	T temp = 0.0;
	int row = 0;
	int col = 0;

	for(int i=0; i< (this->m)*(obj.n) ; ++i)
		{
			//cout<<"i is: "<<i <<endl;
			temp = 0.0;
			row = i/(obj.n);
			col = i % (obj.n); 

			//cout<<"\nrow is: "<<row<<endl;
			//cout<<"\ncol is:"<<col<<endl; 

			for(int j=0 ; j < this->n ; ++j)
			{
				//cout<<"j is: " << j << endl;

				//cout<<"\ntemp:   "<<temp<<endl;

				//cout<< "\n(*(this->ptr + (row*(this->n) + j) ))" << (*(this->ptr + (row*(this->n) + j) )) <<endl;

				//cout<<"\n(*(obj.ptr + (col + j*(obj.n)) ))" << (*(obj.ptr + (col + j*(obj.n)) )) << endl;

				temp = temp +  (*(this->ptr + (row*(this->n) + j) )) * (*(obj.ptr + (col + j*(obj.n)) ));

			}
			//cout<<"Now the temp is : " << temp << endl;
			//*(this->ptr + i) = temp;
			*(m3.ptr + i) = temp;
		}


	return m3;
}	

template <class T>
Matrix<T> Matrix<T>::operator*= (const Matrix &obj)  
{
	//Matrix retMat(this->m, obj.n, 0.0); 
	Matrix m1(*this); 
	Matrix m2(obj);
	m1 = m1*m2;

	return m1;
}

template <class T>
bool Matrix<T> :: operator== (const Matrix &obj)
{
	bool flag = true;

	if(((this->m) != (obj.m)) || ((this->n) != (obj.n)) )
	{
		flag = false;
		//cout<<"I am in flag"<<endl;
	}
	else 
	{
		for(int i=0;i <(this->m)* (this->n);++i)
		{
			if(*(this->ptr + i ) != *(obj.ptr + i))
				{
					flag = false;
					//cout<<"I am in for loop for i: " << i << endl;
					break;
				}
		}
	}

	return flag;
	
}

template <class T>
bool Matrix<T> :: operator!= (const Matrix &obj)
{
	return !(*this == obj);
}

template <class T>
Matrix<T>::~Matrix()
	{
	//cout<<"\nDestructor called " << endl; 
	
	delete[] ptr; 

	}

template <class T>
T Matrix<T> :: operator() (int r, int c) const
{
	//cout<<"I am inside const operator ()" <<  endl; 	
	return *(ptr+ r*n + c);
} 

template <class T>
T& Matrix<T> :: operator() (int r, int c)
{	
	//cout<<"I am inside operator ()" <<  endl; 	
	return *(ptr+ r*n + c);
}	



template<class T>
 ostream& operator<< (ostream& os,const Matrix<T>& obj)
 {
   
   obj.displayMatrix();
   return os;
 }


	
template <class T>	
void Matrix<T>::displayMatrix() const
      {
	int i=0,j=0;
	//cout<<"\nThe contents of the matrix are: "<< endl;
	
	for(i=0 ; i< this->m ; ++i)
	    {	
	    	//cout<<"i is: "<<i<<endl;
	      for(j=0 ; j< this->n; ++j)
	      {
	      	//cout<<"j is: " <<j<<endl;
	      cout<< *(ptr+ (i*(this->n) +j))<<"\t";
	      }
	      cout<<endl;
	    }
	
	
      }




