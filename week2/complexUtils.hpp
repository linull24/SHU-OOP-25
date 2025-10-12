#include <cmath>
#include <iostream>

class complex {
public:
    complex(double _real = 0, double _imag = 0);
    complex(double _a, double _b, bool isRadius);
    
    double getReal() const;
    double getImag() const;
    double getModulus() const;
    double getArgument() const;
    
    complex operator+(const complex& other) const;
    complex operator-(const complex& other) const;
    complex operator*(const complex& other) const;
    complex operator/(const complex& other) const;
    
    complex operator+(double val) const;
    complex operator-(double val) const;
    complex operator*(double val) const;
    complex operator/(double val) const;
    
    bool operator==(const complex& other) const;
    bool operator!=(const complex& other) const;
    
    complex& operator+=(const complex& other);
    complex& operator-=(const complex& other);
    
    complex conjugate() const;
    
    void update();
    
private:
    double re, im;
    double* mo;
    double* ar;
    bool isConverted;
    void invalidateCache();
};


