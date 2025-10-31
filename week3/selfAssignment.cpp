#include <cstring>

class theClass1{
public:
    char* str;
    theClass1(const char* s){
        str = new char[strlen(s)+1];
        strcpy(str,s);
    }
    theClass1 operator=(const theClass1&other) {
        if (this != &other) {//Manual Check
            delete[] str; 
            str = new char[strlen(other.str) + 1];
            strcpy(str, other.str);
        }
        return *this;
    }
};
class theClass2{
public:
    char* str;
    theClass2(const char* s){
        str = new char[strlen(s)+1];
        strcpy(str,s);
    }
    theClass2(const theClass2& other) {
        str = new char[strlen(other.str) + 1];
        strcpy(str, other.str);
    }
    ~theClass2() {
        delete[] str;
    }
    void swap(theClass2& other) {
        char* temp = str;
        str = other.str;
        other.str = temp;
    }
    theClass2& operator=(theClass2 other) {
        swap(other); //In this way, there is no exception in the case of sefl-assignment.
        return *this;
    }
};
int main() {

}