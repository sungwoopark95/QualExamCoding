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
    public :
    bool isitme(Dummy&);
};

bool Dummy::isitme(Dummy& param){
    if (&param==this){
        return true;
    }
    else {return false;}
}
int main(void){
    Dummy a;
    Dummy *b;
    b=&a;
    
    cout << "Is b indicating a ? The answer is " << b->isitme(a) << endl;
    return 0;
}