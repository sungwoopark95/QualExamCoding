// class type-casting
#include <iostream>
using namespace std;
class Dummy {
    // double i=3.0;
    // double j=4.0;
    int i=3;
    int j=4;
};

class Addition {
    int x,y;
    public:
    Addition (int a, int b) { x=a; y=b; }
    int result() { return x+y;}
};

int main () {
    Dummy d;
    Addition * padd;
    padd = (Addition*) &d;
    cout << padd->result();
    return 0;
}