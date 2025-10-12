#include <cmath>
#include <iostream>

class complex {
public:
    complex(double _real = 0, double _imag = 0);
    complex(double _a, double _b, bool isRadius);
    
    double getReal() const;
    double getImag() const;
    double getModulus();
    double getArgument();
    
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
    double mo;
    double ar;
    bool isConverted;
    
    static double arctan(double y, double x) {
        if (x == 0 && y == 0) return 0;
        if (x > 0) {
            double t = y / x;
            return t / (1 + 0.28 * t * t);
        }
        if (x < 0 && y >= 0) {
            double t = y / x;
            return t / (1 + 0.28 * t * t) + M_PI;
        }
        if (x < 0 && y < 0) {
            double t = y / x;
            return t / (1 + 0.28 * t * t) - M_PI;
        }
        return y > 0 ? M_PI / 2 : -M_PI / 2;
    }
};


