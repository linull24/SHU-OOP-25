#include<iostream>
#include "swap_utils.h"
using namespace std;
int main(  ){
   int m = 3, n = 5;
   double a = 3.3, b=5.5;
   char str1[80] = "Tom", str2[80] = "Jerry";
   const char *p1 = "Tom", *p2 = "Jerry";
       
   cout << "m = " << m << ", n = " << n << endl;
//自定义函数调用        //调用自定义函数交换两个值
    myswap(m,n);
   cout << "m = " << m << ", n = " << n << endl;
 
   cout << "a = " << a << ", b= " <<b << endl;
//自定义函数调用        //调用自定义函数交换两个值
    myswap(a,b);
  cout << "a = " << a << ", b= " <<b << endl;
 
 cout << str1 << '\t' << str2 << endl;
//自定义函数调用        //调用自定义函数交换两个值 数组需要特殊处理
      myswap(str1,str2);
  cout << str1 << '\t' << str2 << endl;
 
   cout << p1 << '\t' << p2 << endl;
//自定义函数调用        //调用自定义函数交换两个值 这里由于是指针，所以不需要特殊处理，直接交换指针即可。
    myswap(p1,p2);
   cout << p1 << '\t' << p2 << endl;
   return 0;
}