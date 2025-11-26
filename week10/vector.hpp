#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <vector>
#include <initializer_list>
#include <iostream>

template<typename T>
class Vector {
public:
    Vector() = default;
    Vector(std::initializer_list<T> init) : data(init) {}
    Vector(size_t n) : data(n) {}
    
    size_t size() const { return data.size(); }
    T& operator[](size_t i) { return data[i]; }
    const T& operator[](size_t i) const { return data[i]; }
    
    Vector operator+(const Vector& other) const {
        Vector result(size());
        for (size_t i = 0; i < size(); ++i)
            result[i] = data[i] + other[i];
        return result;
    }
    
    Vector operator-(const Vector& other) const {
        Vector result(size());
        for (size_t i = 0; i < size(); ++i)
            result[i] = data[i] - other[i];
        return result;
    }
    
    T operator*(const Vector& other) const {
        T result = data[0] * other[0];
        for (size_t i = 1; i < size(); ++i)
            result = result + (data[i] * other[i]);
        return result;
    }
    
    Vector operator*(const T& scalar) const {
        Vector result(size());
        for (size_t i = 0; i < size(); ++i)
            result[i] = data[i] * scalar;
        return result;
    }
    
    Vector operator/(const T& scalar) const {
        Vector result(size());
        for (size_t i = 0; i < size(); ++i)
            result[i] = data[i] / scalar;
        return result;
    }
    
    Vector& operator+=(const Vector& other) {
        for (size_t i = 0; i < size(); ++i)
            data[i] = data[i] + other[i];
        return *this;
    }
    
    bool operator==(const Vector& other) const {
        if (size() != other.size()) return false;
        for (size_t i = 0; i < size(); ++i)
            if (!(data[i] == other[i])) return false;
        return true;
    }
    
    template<typename U>
    friend Vector<U> operator*(const U& scalar, const Vector<U>& vec);
    
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Vector<U>& vec);
    
private:
    std::vector<T> data;
};

template<typename T>
Vector<T> operator*(const T& scalar, const Vector<T>& vec) {
    return vec * scalar;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        os << vec[i];
        if (i < vec.size() - 1) os << ", ";
    }
    os << "]";
    return os;
}

#endif
