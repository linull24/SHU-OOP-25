#include<iostream>
#include<string>
#include "parse.h"
#include "solver.h"
int main () {
    std::cout << "请输入类似Ax^2 (+/- Bx) (+/- C) 并严格遵守" << std::endl;
    // std::string test_parse="x^2 -4"; // 这个包含了最多的异常
    // parse* myParse = new parse();
    // myParse->get(test_parse);
    // std::cout << myParse->a << " " << myParse->b << " " << myParse->c << " ";
    // delete myParse;
    std::string input;
    std::getline(std::cin, input);
    parse* myParse = new parse();
    myParse->get(input);
    //std::cout << "\nParsed: a=" << myParse->a << ", b=" << myParse->b << ", c=" << myParse->c << std::endl;
    solver* mySolver = new solver(myParse->a,myParse->b,myParse->c);
    mySolver->printResult();
    delete myParse;
    delete  mySolver;
    return 0;
}