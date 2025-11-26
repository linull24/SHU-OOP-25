#include "complexUtils.hpp"
#include <iostream>

complex::complex(double _real, double _imag) : re(_real), im(_imag), isConverted(false) {}

complex::complex(double _a, double _b, bool isRadius) : isConverted(false) {
    if (isRadius) {
        re = _a * std::cos(_b);
        im = _a * std::sin(_b);
        isConverted = true;
    } else {
        re = _a;
        im = _b;
    }
}

double complex::getReal() const { return re; }

double complex::getImag() const { return im; }

double complex::getModulus() const {
    if (!mo) {
        const_cast<complex*>(this)->mo = new double(std::sqrt(re * re + im * im));
    }
    return *mo;
}

double complex::getArgument() const {
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

void complex::invalidateCache() {
    delete mo;
    delete ar;
    mo = nullptr;
    ar = nullptr;
}

void complex::update() {
    delete mo;
    delete ar;
    mo = nullptr;
    ar = nullptr;
    isConverted = false;
}

complex complex::operator+(const complex& other) const {
    return complex(re + other.re, im + other.im);
}

complex complex::operator-(const complex& other) const {
    return complex(re - other.re, im - other.im);
}

complex complex::operator*(const complex& other) const {
    return complex(re * other.re - im * other.im, 
                  re * other.im + im * other.re);
}

complex complex::operator/(const complex& other) const {
    double denom = other.re * other.re + other.im * other.im;
    return complex((re * other.re + im * other.im) / denom, 
                  (im * other.re - re * other.im) / denom);
}

complex complex::operator+(double val) const {
    return complex(re + val, im);
}

complex complex::operator-(double val) const {
    return complex(re - val, im);
}

complex complex::operator*(double val) const {
    return complex(re * val, im * val);
}

complex complex::operator/(double val) const {
    return complex(re / val, im / val);
}

bool complex::operator==(const complex& other) const {
    return (re == other.re) && (im == other.im);
}

bool complex::operator!=(const complex& other) const {
    return !(*this == other);
}

complex& complex::operator+=(const complex& other) {
    re += other.re;
    im += other.im;
    update();
    return *this;
}

complex& complex::operator-=(const complex& other) {
    re -= other.re;
    im -= other.im;
    update();
    return *this;
}

complex complex::conjugate() const {
    return complex(re, -im);
}

complex operator+(double val, const complex& c) {
    return c + val;
}

complex operator-(double val, const complex& c) {
    return complex(val - c.getReal(), -c.getImag());
}

complex operator*(double val, const complex& c) {
    return c * val;
}

complex operator/(double val, const complex& c) {
    complex conj = c.conjugate();
    double denom = c.getReal() * c.getReal() + c.getImag() * c.getImag();
    return complex(val * conj.getReal() / denom, val * conj.getImag() / denom);
}

std::ostream& operator<<(std::ostream& os, const complex& c) {
    os << "(" << c.getReal();
    if (c.getImag() >= 0) os << "+";
    os << c.getImag() << "i)";
    return os;
}
