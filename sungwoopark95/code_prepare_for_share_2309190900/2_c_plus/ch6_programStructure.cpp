#include <stdio.h> //printf, scanf
#include <stdlib.h> //malloc
#include <stdbool.h> //bool
#include <math.h>
#include <iostream>
#include <sstream>
#include <string>


using namespace std;
string concatenate(const string& s1, const string& s2){
    return s1+s2;
}

//template
template <class SomeType>
SomeType sum (SomeType a, SomeType b) {
    return a+b;
}


template <class T, class U>
bool are_equal (T a, U b) {
    return (a==b);
}

template <class T, int N>
T fixed_multiply(T val) {
    return val*N;
}

int main(void) {

    // [4]
    std::cout << fixed_multiply<int,2>(10) << '\n';
    std::cout << fixed_multiply<int,3>(10) << '\n';

    // // [3]
    // if (are_equal(10,10.0))
    // cout << "x and y are equal\n";
    // else
    // cout << "x and y are not equal\n";


    // // [2]
    // int x=7, y=15;
    // cout << sum(x,y) << endl; // 22

    // double a=1.23, b=4.56;
    // cout << sum(a,b) << endl; // 5.79

    // string s1="Hello", s2=" World";
    // cout << sum(s1,s2) << endl; // Hello World


    // cout << sum<int>(10.3, 20) << endl;
    // cout << (int)(32.7) << endl;


    // // [1]
    // string s1="Hello, ";
    // string s2="World!";
    // cout << concatenate(s1, s2) << endl; 
    return 0;
}