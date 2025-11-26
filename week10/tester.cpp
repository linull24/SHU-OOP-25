#include "complexUtils.hpp"
#include "vector.hpp"

using Complex = ::complex;

int main() {
    Vector<Complex> v1 = {Complex(1,2), Complex(3,4), Complex(5,6)};
    Vector<Complex> v2 = {Complex(2,1), Complex(4,3), Complex(6,5)};
    Complex scalar(2,0);
 
    std::cout << "v1 = " << v1 << std::endl;
    std::cout << "v2 = " << v2 << std::endl;
    std::cout << "scalar = " << scalar << std::endl;
    std::cout << "------------------------" << std::endl;
 
    Vector<Complex> v_add = v1 + v2;
    std::cout << "v1 + v2 = " << v_add << std::endl;
    Vector<Complex> v_sub = v1 - v2;
    std::cout << "v1 - v2 = " << v_sub << std::endl;
 
    Complex v_dot = v1 * v2;
    std::cout << "v1 · v2 = " << v_dot << std::endl;
 
    Vector<Complex> v_mul1 = v1 * scalar;
    Vector<Complex> v_mul2 = scalar * v1;
    std::cout << "v1 * scalar = " << v_mul1 << std::endl;
    std::cout << "scalar * v1 = " << v_mul2 << std::endl;
 
    Vector<Complex> v_div = v1 / scalar;
    std::cout << "v1 / scalar = " << v_div << std::endl;
 
    Vector<Complex> v_acc = v1;
    v_acc += v2;
    std::cout << "v1 += v2 → " << v_acc << std::endl;
 
    std::cout << "v1 == v2 ? " << (v1 == v2 ? "Yes" : "No") << std::endl;
    std::cout << "v_add == v_acc ? " << (v_add == v_acc ? "Yes" : "No") << std::endl;
    
    return 0;
}