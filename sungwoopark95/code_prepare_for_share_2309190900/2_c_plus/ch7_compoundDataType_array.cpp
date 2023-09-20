#include <cstdlib>
#include <stdio.h> //printf, scanf
#include <stdlib.h> //malloc
#include <stdbool.h> //bool
#include <math.h>
#include <iostream>
#include <sstream>
#include <string>
#include <array>
using namespace std;

void printarray (int arg[], int length) {
    for (int n=0; n<length; ++n)
    cout << arg[n] << ' ';
    cout << '\n';
}


int main(void) {

    // [4] pointer 주의
    int myints[]={10, 20, 30, 40, 50};
    int *myptr = myints ;
    cout << *myptr++ << endl; //10
    cout << *++myptr << endl; //30
    cout << *myptr <<endl; //30
    cout << ++*myptr << endl; // 31
    cout << (*myptr)++ << endl; // 31
    cout << *myptr << endl; //32

 
    // // [3]
    // char myword[] = "Hello. This is Yongsang.";
    // string mystring = myword;
    // cout << mystring << endl;
    // cout << "length : " << mystring.length() << endl;
    // cout << mystring.c_str() << endl;
    // cout << "length : " << mystring.size() << endl;

    // // [2]
    // array<int, 3> myarray {88, 77, 66};
    // for (int i=0; i<myarray.size(); i++){
    //     ++myarray[i];
    // }
    // for (int elem : myarray)
    //     cout<< elem << endl;


    // // [1]    
    // int firstarray[] = {5, 10, 15};
    // int secondarray[] = {2, 4, 6, 8, 10};
    // printarray (firstarray,3);
    // printarray (secondarray,5);
    
    return 0;
}