#include "complexUtilsTemplated.hpp"
#include <iostream>
#include <memory>

void testComplex(complex<double>& c1, complex<double>& c2) {
    std::cout << "c1: " << c1.getReal() << " + " << c1.getImag() << "i\n";
    std::cout << "c2: " << c2.getReal() << " + " << c2.getImag() << "i\n";
    std::cout << "c1 模长: " << c1.getModulus() << "\n";
    std::cout << "c1 幅角: " << c1.getArgument() << "\n";
    auto sum = c1 + c2;
    std::cout << "c1 + c2: " << sum.getReal() << " + " << sum.getImag() << "i\n";
    auto conj = c1.conjugate();
    std::cout << "c1 共轭: " << conj.getReal() << " + " << conj.getImag() << "i\n";
    std::cout << "c1 == c2: " << (c1 == c2) << "\n\n";
}

int main() {
    // 栈上分配
    complex<double> c1(3, 4);
    complex<double> c2(1, 2);
    testComplex(c1, c2);
    
    auto c3 = std::make_unique<complex<double>>(5, 6);
    auto c4 = std::make_unique<complex<double>>(2, 3);
    testComplex(*c3, *c4);
    
    auto c5 = new complex<double>(7, 8);
    auto c6 = new complex<double>(1, 1);
    testComplex(*c5, *c6);
    delete c5;
    delete c6;
    
    return 0;
}
