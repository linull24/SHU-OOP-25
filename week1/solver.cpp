#include<iostream>
#include<string>
#include "parse.h"
int main () {
    std::cout << "请输入类似Ax^2 (+/- Bx) (+/- C) 并严格遵守";
    std::string test_parse="x^2 -4"; // 这个包含了最多的异常
    parse* myParse = new parse();
    myParse->get(test_parse);
    std::cout << myParse->a << " " << myParse->b << " " << myParse->c << " ";
    delete myParse;
    return 0;
}