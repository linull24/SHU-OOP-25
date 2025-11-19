#include "myString.hpp"
#include <cstring>

size_t myString::length() const {
    return getSize();
}

const char* myString::c_str() const {
    return getRaw();
}

int myString::find(char ch) const {
    const char* str = getRaw();
    size_t len = getSize();
    for (size_t i = 0; i < len; ++i) {
        if (str[i] == ch) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

myString myString::substr(size_t pos, size_t count) const {
    if (pos >= getSize()) return myString();
    
    size_t actualCount = (pos + count > getSize()) ? getSize() - pos : count;
    char* temp = new char[actualCount + 1];
    strncpy(temp, getRaw() + pos, actualCount);
    temp[actualCount] = '\0';
    
    myString result(temp);
    delete[] temp;
    return result;
}

myString myString::operator+(const myString& other) const {
    size_t totalLen = getSize() + other.getSize();
    char* temp = new char[totalLen + 1];
    strcpy(temp, getRaw());
    strcat(temp, other.getRaw());
    
    myString result(temp);
    delete[] temp;
    return result;
}

bool myString::operator!=(const myString& other) const {
    return !(*this == other);
}