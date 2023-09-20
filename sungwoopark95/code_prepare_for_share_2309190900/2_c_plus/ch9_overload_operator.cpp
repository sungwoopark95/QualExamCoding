#include <cstdlib> //new
#include <stdio.h> //printf, scanf
#include <stdlib.h> //malloc
#include <stdbool.h> //bool
#include <math.h>
#include <iostream>
#include <sstream>
#include <string>
#include <array>
#include <new>


using namespace std;

class CVector {
    public:
    int x;
    int y;
    CVector() {}; //constructor
    CVector(int a, int b) : x(a), y(b) { };
    CVector operator+(const CVector&);
};

CVector CVector::operator+(const CVector& vec){
    CVector tmp;
    tmp.x = x + vec.x;
    tmp.y = y + vec.y;
    return tmp;
}

int main(void){
    CVector v1(3, 4);
    CVector v2(5, 7);
    CVector result;
    // result = v1.operator+(v2);
    result = v1 + v2;
    cout << "result.x = " << result.x << ",\t  result.y = " << result.y << endl;
    return 0;
}