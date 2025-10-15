#include<iostream>
#include<cstring>
using namespace std;

class theClass{
public:
    char* value;
    
    theClass(const theClass &obj){
        cout << "copying" << endl;
        value = new char[strlen(obj.value)+1];
        strcpy(value, obj.value);
    }
    
    ~theClass(){
        delete[] value;
    }
};

int main() {
    try {
        theClass myClass;
    }
    catch(...){
        cout << "error" << endl;
    }
    
    return 0;
}