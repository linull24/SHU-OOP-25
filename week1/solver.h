#include <string>
#include <iostream>
#include <cmath>
class solver{
public:
    double delta;
    double sqrtOfAbsDelta;
    double a,b,c;
    std::string x1,x2;
    void computeDelta();
    solver(const double _a, const double _b, const double _c)
        : a(_a), b(_b), c(_c) {
        computeDelta();
    }
    void printResult(){
        std::cout << "x1 = " << x1 << std::endl;
        std::cout << "x2 = " << x2 << std::endl;
    }
private:
    bool isReal;
};
void solver::computeDelta(){
    delta = b*b - 4*a*c;
    isReal = delta >= 0;
    sqrtOfAbsDelta = isReal ? sqrt(delta) : sqrt(-delta);
    if(isReal){
        x1 = std::to_string((-b + sqrtOfAbsDelta)/(2*a));
        x2 = std::to_string((-b - sqrtOfAbsDelta)/(2*a));
    }
    else{
        x1 = std::to_string(-b/(2*a)) + " + " + std::to_string(sqrtOfAbsDelta/(2*a)) + "i";
        x2 = std::to_string(-b/(2*a)) + " - " + std::to_string(sqrtOfAbsDelta/(2*a)) + "i";
    }
}
