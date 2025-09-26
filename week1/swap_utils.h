#include<cstring>
template <typename T>
void myswap(T &a,T &b){
    T temp=a;
    a=b;
    b=temp;
}
template <size_t N>
void myswap(char (&a)[N],char (&b)[N]){
    char temp[N];
    strcpy(temp,a);
    strcpy(a,b);
    strcpy(b,temp);
}