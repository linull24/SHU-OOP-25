#include<string>
#include <cstring> 
// STACK_STORAGE_SIZE可以研讨与调整，考虑内存对齐与实际应用的特点。
class myString;
class myStringData;
class myStringInterface;
class myStringProxy;
// functions: split connect swap operator[] front()/back() size find
// binData实现不同的类型存储
// Interface封装binData，提供跨类型的统一的操作
// myString 提供主要的函数功能
// Proxy提供与cstring 和 std::string的操作
class myStringBinData
{
public:
    myStringBinData();
    ~myStringBinData();
    enum type {SSO, PILE};
    union 
    {
        struct {
            size_t length;
            size_t capacity;
            char* heapstr;
        } longstr;
        struct 
        {
            size_t length;
            char data[23];
        } shortstr; 
    } storage;
    
    size_t getSize() const;
    size_t getCapacity() const;   
    void setLength(size_t len);
    // pile
    void setRawByIndex(const char* raw, size_t i);
    const char* getRaw() const;
    // sso
    void setRaw(const char* raw, size_t length);
    void setType(type t);
private:
    type memType;
};
class myStringInterface : public myStringBinData
{
public:
    myStringInterface();
    ~myStringInterface();
    void setData(const char * ptr,size_t size);
    void append(const char * ptr, size_t size);
    void copy(const char * ptr, size_t size,size_t pos);
    void clear();
    void swap(myStringInterface& other);
    bool checkCapacity(size_t size) const;
    bool isEmpty();
private:
    bool Capacity;
};
class myString : public myStringInterface
{
public:
    myString();
    ~myString();
    myString(const char* ptr);
    myString(const myString& other);
    myString& operator=(const myString& other);
    myString& operator+=(const myString& other);
    bool operator==(const myString& other) const;
    char& operator[](size_t index);
    const char& operator[](size_t index) const;
    myString substr(size_t pos, size_t count) const;
    size_t length() const;
    const char* c_str() const;
    int find(char ch) const;
    myString operator+(const myString& other) const;
    bool operator!=(const myString& other) const;
    friend class myStringProxy;
};
class myStringProxy
{
public:
    myStringProxy(myString& str);
    ~myStringProxy();
    operator std::string() const;
    operator const char*() const;
    myStringProxy& operator=(const std::string& stdStr);
    myStringProxy& operator=(const char* cStr);  
    friend std::string operator+(const std::string& lhs, const myString& rhs);
    friend std::string operator+(const myString& lhs, const std::string& rhs);
    friend bool operator==(const char* lhs, const myString& rhs);
    friend bool operator==(const myString& lhs, const char* rhs);
    friend bool operator==(const std::string& lhs, const myString& rhs);
    friend bool operator==(const myString& lhs, const std::string& rhs);
private:
    myString& str;
};