#include "myString.hpp"
#include <cstring>

myStringInterface::myStringInterface() : Capacity(true) {}

myStringInterface::~myStringInterface() {}

void myStringInterface::setData(const char* ptr, size_t size) {
    setRaw(ptr, size);
}

void myStringInterface::append(const char* ptr, size_t size) {
    size_t currentSize = getSize();
    size_t newSize = currentSize + size;
    
    char* temp = new char[newSize + 1];
    strncpy(temp, getRaw(), currentSize);
    strncpy(temp + currentSize, ptr, size);
    temp[newSize] = '\0';
    setRaw(temp, newSize);
    delete[] temp;
}

void myStringInterface::copy(const char* ptr, size_t size, size_t pos) {
    if (pos >= getSize()) return;
    
    size_t copySize = (pos + size > getSize()) ? getSize() - pos : size;
    const char* src = getRaw();
    
    for (size_t i = 0; i < copySize; ++i) {
        const_cast<char*>(src)[pos + i] = ptr[i];
    }
}

void myStringInterface::clear() {
    setRaw("", 0);
}

void myStringInterface::swap(myStringInterface& other) {
    auto tempStorage = storage;
    storage = other.storage;
    other.storage = tempStorage;
    
    // Swap types through setType method
    auto thisSize = getSize();
    auto otherSize = other.getSize();
    setType(otherSize < 23 ? SSO : PILE);
    other.setType(thisSize < 23 ? SSO : PILE);
}

bool myStringInterface::checkCapacity(size_t size) const {
    return getCapacity() >= size;
}

bool myStringInterface::isEmpty() {
    return getSize() == 0;
}