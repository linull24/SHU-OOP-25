#include "complexUtilsTemplated.hpp"
#include <iostream>

int main() {
    // 测试构造函数
    complex<double> c1(3, 4);
    complex<double> c2(1, 2);
    complex<double> c3(5, 0.927, true); // 极坐标构造
    
    std::cout << "c1: " << c1.getReal() << " + " << c1.getImag() << "i\n";
    std::cout << "c2: " << c2.getReal() << " + " << c2.getImag() << "i\n";
    std::cout << "c3 极坐标: " << c3.getReal() << " + " << c3.getImag() << "i\n\n";
    
    // 测试模长和幅角
    std::cout << "c1 模长: " << c1.getModulus() << "\n";
    std::cout << "c1 幅角: " << c1.getArgument() << "\n\n";
    
    // 测试四则运算
    auto sum = c1 + c2;
    std::cout << "c1 + c2: " << sum.getReal() << " + " << sum.getImag() << "i\n";
    
    auto diff = c1 - c2;
    std::cout << "c1 - c2: " << diff.getReal() << " + " << diff.getImag() << "i\n";
    
    auto prod = c1 * c2;
    std::cout << "c1 * c2: " << prod.getReal() << " + " << prod.getImag() << "i\n";
    
    auto quot = c1 / c2;
    std::cout << "c1 / c2: " << quot.getReal() << " + " << quot.getImag() << "i\n\n";
    
    // 测试比较运算符
    std::cout << "c1 == c2: " << (c1 == c2) << "\n";
    std::cout << "c1 != c2: " << (c1 != c2) << "\n\n";
    
    // 测试复合赋值运算符
    complex<double> c4 = c1;
    c4 += c2;
    std::cout << "c4  += c2: " << c4.getReal() << " + " << c4.getImag() << "i\n";
    
    c4 -= c2;
    std::cout << "c4 after -= c2: " << c4.getReal() << " + " << c4.getImag() << "i\n\n";
    
    // 测试共轭
    auto conj = c1.conjugate();
    std::cout << "c1 共轭 " << conj.getReal() << " + " << conj.getImag() << "i\n";
    
    return 0;
}
