#include <cmath>
#include <concepts>

template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template <typename userType>
requires Arithmetic<userType>
class complex {
public:
    complex(userType real = 0, userType imag = 0) : re(real), im(imag), mo(0), ar(0), isConverted(false) {}
    complex(userType _a, userType _b, bool isRadius) : mo(0), ar(0), isConverted(false) {
        if (isRadius) {
            re = _a * std::cos(_b);
            im = _a * std::sin(_b);
            mo = _a;
            ar = _b;
            isConverted = true;
        } else {
            re = _a;
            im = _b;
        }
    }
    
    userType getReal() const { return re; }
    userType getImag() const { return im; }
    double getModulus() {
        if (!isConverted) {
            mo = std::sqrt(re * re + im * im);
            ar = arctan(im, re);
            isConverted = true;
        }
        return mo;
    }
    double getArgument() {
        if (!isConverted) {
            mo = std::sqrt(re * re + im * im);
            ar = arctan(im, re);
            isConverted = true;
        }
        return ar;
    }
    
    complex operator+(const complex& other) const {
        return complex(re + other.re, im + other.im);
    }
    
    complex operator-(const complex& other) const {
        return complex(re - other.re, im - other.im);
    }
    
    complex operator*(const complex& other) const {
        return complex(re * other.re - im * other.im, re * other.im + im * other.re);
    }
    
    complex operator/(const complex& other) const {
        double denom = other.re * other.re + other.im * other.im;
        return complex((re * other.re + im * other.im) / denom, 
                      (im * other.re - re * other.im) / denom);
    }
    

    bool operator==(const complex& other) const {
        return (re == other.re) && (im == other.im);
    }
    
    bool operator!=(const complex& other) const {
        return !(*this == other);
    }
    
    complex& operator+=(const complex& other) {
        re += other.re;
        im += other.im;
        update();
        return *this;
    }
    
    complex& operator-=(const complex& other) {
        re -= other.re;
        im -= other.im;
        update();
        return *this;
    }
    
    complex conjugate() const {
        return complex(re, -im);
    }
    
    void update() {
        isConverted = false;
    }
    
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
    
private:
    userType re, im;
    double mo;
    double ar;
    bool isConverted;
};


