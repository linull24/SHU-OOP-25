#include <cmath>
#include <concepts>

template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template <typename userType>
requires Arithmetic<userType>
class complex {
public:
    complex(userType real = 0, userType imag = 0) : re(real), im(imag), isConverted(false) {}
    complex(userType _a, userType _b, bool isRadius) : isConverted(false) {
        if (isRadius) {
            re = _a * std::cos(_b);
            im = _a * std::sin(_b);
            isConverted = true;
        } else {
            re = _a;
            im = _b;
        }
    }
    
    userType getReal() const { return re; }
    userType getImag() const { return im; }
    double getModulus() const {
        if (!mo) {
            const_cast<complex*>(this)->mo = new double(std::sqrt(re * re + im * im));
        }
        return *mo;
    }
    double getArgument() const {
        if (!ar) {
            if (re == 0 && im == 0) {
                const_cast<complex*>(this)->ar = new double(0);
            } else if (re > 0) {
                const_cast<complex*>(this)->ar = new double(std::atan(im / re));
            } else if (re < 0 && im >= 0) {
                const_cast<complex*>(this)->ar = new double(std::atan(im / re) + M_PI);
            } else if (re < 0 && im < 0) {
                const_cast<complex*>(this)->ar = new double(std::atan(im / re) - M_PI);
            } else if (re == 0 && im > 0) {
                const_cast<complex*>(this)->ar = new double(M_PI / 2);
            } else {
                const_cast<complex*>(this)->ar = new double(-M_PI / 2);
            }
        }
        return *ar;
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
        delete mo;
        delete ar;
        mo = nullptr;
        ar = nullptr;
        isConverted = false;
    }
    
private:
    userType re, im;
    double* mo;
    double* ar;
    bool isConverted;
};


