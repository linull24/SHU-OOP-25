#include "QuadraticEquation.hpp"
#include <cmath>
#include <string>

QuadraticEquation::QuadraticEquation(const double params[], size_t size) 
    : QuadraticEquation({size > 0 ? params[0] : 0.0, 
                         size > 1 ? params[1] : 0.0, 
                         size > 2 ? params[2] : 0.0}) {}

QuadraticEquation::QuadraticEquation(std::initializer_list<double> params) {
    auto it = params.begin();
    A = it != params.end() ? *it++ : 0.0;
    B = it != params.end() ? *it++ : 0.0;
    C = it != params.end() ? *it++ : 0.0;
    init();
}

void QuadraticEquation::updateIsLegal() {
    isLegal = (A != 0.0);
}

void QuadraticEquation::updateDiscriminant() {
    discriminant = B * B - 4 * A * C;
    sqrtOfAbsDiscriminant = discriminant >= 0 ? std::sqrt(discriminant) : std::sqrt(-discriminant);
}

void QuadraticEquation::updateIsSolvable() {
    isSolvable = isLegal && discriminant >= 0;
}

void QuadraticEquation::updateSameSolution() {
    sameSolution = isSolvable && (discriminant == 0);
}

void QuadraticEquation::init() {
    updateIsLegal();
    updateDiscriminant();
    updateIsSolvable();
    updateSameSolution();
}

bool QuadraticEquation::getIsLegal() {
    return isLegal;
}

bool QuadraticEquation::getIsSolvable() {
    return isSolvable;
}

bool QuadraticEquation::isSameSolution() {
    return sameSolution;
}

double QuadraticEquation::getDiscriminant() {
    return discriminant;
}

double QuadraticEquation::getSolution() {
    if (!isSolvable) return NAN;
    return -B / (2 * A);
}

std::pair<double, double> QuadraticEquation::getSolutionStdPair() {
    if (!isSolvable) return {NAN, NAN};
    return {(-B + sqrtOfAbsDiscriminant) / (2 * A), (-B - sqrtOfAbsDiscriminant) / (2 * A)};
}

std::pair<complex<double>, complex<double>> QuadraticEquation::getComplexSolutionPair() {
    if (!isLegal) return {complex<double>(NAN, NAN), complex<double>(NAN, NAN)};
    if (discriminant >= 0) {
        return {complex<double>((-B + sqrtOfAbsDiscriminant) / (2 * A), 0),
                complex<double>((-B - sqrtOfAbsDiscriminant) / (2 * A), 0)};
    }
    double real = -B / (2 * A);
    double imag = sqrtOfAbsDiscriminant / (2 * A);
    return {complex<double>(real, imag), complex<double>(real, -imag)};
}
