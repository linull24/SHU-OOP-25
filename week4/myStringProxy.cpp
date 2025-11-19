#include "myString.hpp"
#include <string>

myStringProxy::myStringProxy(myString& str) : str(str) {}

myStringProxy::~myStringProxy() {}

myStringProxy::operator std::string() const {
    return std::string(str.getRaw());
}

myStringProxy::operator const char*() const {
    return str.getRaw();
}

myStringProxy& myStringProxy::operator=(const std::string& stdStr) {
    str.setData(stdStr.c_str(), stdStr.length());
    return *this;
}

myStringProxy& myStringProxy::operator=(const char* cStr) {
    if (cStr) {
        str.setData(cStr, strlen(cStr));
    }
    return *this;
}

std::string operator+(const std::string& lhs, const myString& rhs) {
    return lhs + std::string(rhs.getRaw());
}

std::string operator+(const myString& lhs, const std::string& rhs) {
    return std::string(lhs.getRaw()) + rhs;
}

bool operator==(const char* lhs, const myString& rhs) {
    return strcmp(lhs, rhs.getRaw()) == 0;
}

bool operator==(const myString& lhs, const char* rhs) {
    return strcmp(lhs.getRaw(), rhs) == 0;
}

bool operator==(const std::string& lhs, const myString& rhs) {
    return lhs == std::string(rhs.getRaw());
}

bool operator==(const myString& lhs, const std::string& rhs) {
    return std::string(lhs.getRaw()) == rhs;
}