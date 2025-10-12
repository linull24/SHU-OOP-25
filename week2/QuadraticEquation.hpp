#include <utility>
#include <concepts>
#include <cstddef>
#include <initializer_list>
#include <string>
#include "complexUtilsTemplated.hpp"

template<typename T>
concept ConvertibleToDouble = std::convertible_to<T, double>;

class QuadraticEquation{
public:
    template<typename... Args>
    requires (sizeof...(Args) >= 1 && sizeof...(Args) <= 3 && (ConvertibleToDouble<Args> && ...))
    QuadraticEquation(Args... args);
    QuadraticEquation(const double params[], size_t size);
    QuadraticEquation(std::initializer_list<double> params);

    bool getIsLegal();
    bool getIsSolvable();
    bool isSameSolution();
    double getDiscriminant();
    double getSolution();
    std::pair<double, double> getSolutionStdPair();
    std::pair<complex<double>, complex<double>> getComplexSolutionPair();
    
private:
    double A, B, C;
    double discriminant, sqrtOfAbsDiscriminant;
    bool isLegal, isSolvable, sameSolution;
    
    void updateIsLegal();
    void updateDiscriminant();
    void updateIsSolvable();
    void updateSameSolution();
    void init();
    
};

// 模板实现必须在头文件中以支持混合类型
template<typename... Args>
requires (sizeof...(Args) >= 1 && sizeof...(Args) <= 3 && (ConvertibleToDouble<Args> && ...))
QuadraticEquation::QuadraticEquation(Args... args) 
    : QuadraticEquation({static_cast<double>(args)...}) {}
