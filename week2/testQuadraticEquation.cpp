#include "QuadraticEquation.hpp"
#include <iostream>
#include <memory>

void test(QuadraticEquation& eq, const std::string& desc) {
    std::cout << "方程: " << desc << "\n";
    std::cout << "合法性: " << eq.getIsLegal() << "\n";
    
    if (eq.getIsSolvable()) {
        auto sol = eq.getSolutionStdPair();
        std::cout << "实数解: " << sol.first << ", " << sol.second << "\n";
    } else {
        auto sol = eq.getComplexSolutionPair();
        std::cout << "复数解:\n";
        std::cout << "  " << sol.first.getReal() << " + " << sol.first.getImag() << "i\n";
        std::cout << "  " << sol.second.getReal() << " + " << sol.second.getImag() << "i\n";
    }
    std::cout << "\n";
}

int main() {
    QuadraticEquation eq1(1, -3, 2);
    test(eq1, "x^2 - 3x + 2 = 0");
    
    auto eq2 = std::make_unique<QuadraticEquation>(1.0f, 0, 1); //这就是在堆上
    test(*eq2, "x^2 + 1 = 0 (混合类型)");
    
    auto eq3 = new QuadraticEquation(1, 2);
    test(*eq3, "x^2 + 2x = 0");
    delete eq3;
    return 0;
}