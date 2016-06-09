#include "Matrix.h"

int main()
{
    Vector v1(5,3);
    Vector v2(5);

    /*//v1.display();
    //v2.display();
    

    Vector v3(5);
    //v3.display();

    //v3 = v1 + v2;
    //v3 = v3*2;

    //v3.display();

    //v1.display();
    //v2.display();

    real sum = v1*v2;
    std::cout << "Sum ? 15: " << sum << std::endl;*/
    
    
    std::vector<std::map<size_t, real> > m(5);
    m[0].insert(std::pair<size_t, real> (0,3));
    m[0].insert(std::pair<size_t, real> (3,4));
    m[1].insert(std::pair<size_t, real> (1,5));
    m[2].insert(std::pair<size_t, real> (0,2));
    m[2].insert(std::pair<size_t, real> (2,8));
    m[3].insert(std::pair<size_t, real> (0,7));
    m[3].insert(std::pair<size_t, real> (2,9));
    m[3].insert(std::pair<size_t, real> (3,1));

    Matrix mat(m);
    
    v2 = mat*v1;
    
    std::cout << "Matrix before:\n";
    mat.display();
    
    std::cout << "Vector after:\n";
    v2.display();
    
}
