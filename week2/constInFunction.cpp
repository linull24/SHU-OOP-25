#include <iostream>
#include <string>

class MyClass {
private:
    std::string data = "Hello";

public:
    // non const 
    char& operator[](size_t index) {
        std::cout << "Non-const version\n";
        return data[index];
    }

    // const 
    const char& operator[](size_t index) const {
        std::cout << "Const version\n";
        return data[index];
    }
};

int main() {
    MyClass obj;
    const MyClass cobj;

    obj[0] = 'X';      
    std::cout << cobj[0] << std::endl; 
    return 0;
}