#include "complexUtils.hpp"
#include <iostream>

complex::complex(double _real, double _imag) : re(_real), im(_imag), mo(0), ar(0), isConverted(false) {}

complex::complex(double _a, double _b, bool isRadius) : mo(0), ar(0), isConverted(false) {
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

double complex::getReal() const { return re; }

double complex::getImag() const { return im; }

double complex::getModulus() {
    if (!isConverted) {
        mo = std::sqrt(re * re + im * im);
        ar = arctan(im, re);
        isConverted = true;
    }
    return mo;
}

double complex::getArgument() {
    if (!isConverted) {
        mo = std::sqrt(re * re + im * im);
        ar = arctan(im, re);
        isConverted = true;
    }
    return ar;
}



void complex::update() {
    isConverted = false;
}

double complex::arctan(double y, double x) {
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
