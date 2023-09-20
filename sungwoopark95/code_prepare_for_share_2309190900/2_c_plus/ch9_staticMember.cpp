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

class Dummy {
    public:
    static int n;
    Dummy() {n++;}
};

int Dummy::n=0; //Static members cannot be initialized directly in the class, but need to be initialized somewhere outside it.


int main(void){
    Dummy a;
    Dummy b[5];
    cout << a.n << ".\n"; // 6
    Dummy *c = new Dummy;
    cout << Dummy::n << ".\n"; //7
    delete c;
    cout << Dummy::n << ".\n"; //7 "delete는 감소시키지 않으니"
    return 0;
}