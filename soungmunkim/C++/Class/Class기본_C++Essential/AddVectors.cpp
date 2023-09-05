#include <iostream>
using namespace std;

class CVector{
    public:
        int x, y;
        CVector () {}; // constructor
        CVector (int a, int b) : x(a), y(b) {} // member variable x = a, y = b
        CVector operator + (const CVector&); // CVector은 type, operator sign, parameters

};
// vector 더하기 연산을 만든 것
CVector CVector::operator+ (const CVector& param){
    CVector temp;
    temp.x = x + param.x; // 각각 x, y끼리 더하는 것
    temp.y = y + param.y;
    return temp;
}

int main() {
    CVector foo (3,1);
    CVector bar (1,2);
    CVector result;
    result = foo + bar; // temp.x = foo.x + bar.x = 3 + 1 = 4
    cout << result.x << ',' << result.y << '\n';

    return 0;
}