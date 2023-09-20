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

template <class T>
class Mypair {
    
    public :
    T values[2];
    Mypair (T first, T second) {
        values[0]=first;
        values[1]=second;
    }
    T get_max();
};

template <class T>
T Mypair<T>::get_max(void){
    T retval;
    retval = values[0] > values[1] ? values[0] : values[1];
    return retval;
}


int main(void){
    Mypair<int> pair_integer(2, 3);
    cout << "First is "<< pair_integer.values[0] << ".\n";
    cout << "Second is "<< pair_integer.values[1] << ".\n";
    cout << "Max is "<< pair_integer.get_max() << ".\n";

    Mypair<char> pair_char('X', 'Y');
    cout << "First is "<< pair_char.values[0] << ".\n";
    cout << "Second is "<< pair_char.values[1] << ".\n";
    cout << "Max is "<< pair_char.get_max() << ".\n";
    return 0;
}