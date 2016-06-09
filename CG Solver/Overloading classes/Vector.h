#include <assert.h>
#include <iostream>
#include <vector>
#include <map>
#include "Type.hpp"

/*using std::cout;
using std::cin;
using std::endl;
using std::ostream;
*/

class Vector
{
    public:
    std::vector<double> vec_;


    Vector(const size_t&, real=0);              // Constructor
    ~Vector();                                 // Destructor


    Vector operator+ (const Vector& );
    real operator* (const Vector& );
    Vector operator* (const real& );
    void operator= (const Vector& );
    void display();

} ;
