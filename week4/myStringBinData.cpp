#include "./myString.hpp"
#include <cstring>

myStringBinData::myStringBinData() : memType(SSO) {
    storage.shortstr.length = 0;
    storage.shortstr.data[0] = '\0';
}

myStringBinData::~myStringBinData() {
    if (memType == PILE) {
        delete[] storage.longstr.heapstr;
    }
}

size_t myStringBinData::getSize() const {
    return memType == SSO ? storage.shortstr.length : storage.longstr.length;
}

size_t myStringBinData::getCapacity() const {
    return memType == SSO ? 23 : storage.longstr.capacity;
}

void myStringBinData::setLength(size_t len) {
    if (memType == SSO) {
        storage.shortstr.length = len;
    } else {
        storage.longstr.length = len;
    }
}

void myStringBinData::setRawByIndex(const char* raw, size_t i) {
    if (memType == PILE) {
        storage.longstr.heapstr[i] = *raw;
    } else {
        storage.shortstr.data[i] = *raw;
    }
}

const char* myStringBinData::getRaw() const {
    return memType == SSO ? storage.shortstr.data : storage.longstr.heapstr;
}

void myStringBinData::setRaw(const char* raw, size_t length) {
    if (length < 23) {
        memType = SSO;
        storage.shortstr.length = length;
        std::memcpy(storage.shortstr.data, raw, length);
        storage.shortstr.data[length] = '\0';
    } else {
        memType = PILE;
        storage.longstr.length = length;
        storage.longstr.capacity = length + 1;
        storage.longstr.heapstr = new char[storage.longstr.capacity];
        std::memcpy(storage.longstr.heapstr, raw, length);
        storage.longstr.heapstr[length] = '\0';
    }
}

void myStringBinData::setType(type t) {
    memType = t;
}
