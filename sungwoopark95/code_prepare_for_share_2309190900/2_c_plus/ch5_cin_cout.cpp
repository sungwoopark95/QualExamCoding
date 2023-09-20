#include <stdio.h> //printf, scanf
#include <stdlib.h> //malloc
#include <stdbool.h> //bool
#include <math.h>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main(void) {
    string str1 = "hello!";
    // string str2 = {"hello!"};
    // string str2 = "he2llo!";
    // bool flag =(str1==str2);
    // cout << flag << endl;
    for (char c : str1){
        cout << "[" << c << "]";
    }

    cout << endl;

    // int num;
    // string mystr ="123 456\n789 248";
    // stringstream mystream;
    // mystream.str(mystr); //mystr이라는 string을 stream으로 만들어 보관

    // while (mystream >> num){
    //     cout << num << endl;
    // }

    // string s;
    // string mystr2 = "Hello world!\nHell world!!!";
    // stringstream mystream2;
    // mystream2.str(mystr2);
    // while (mystream2 >> s){
    //     cout << s << endl;
    // }


    // string mystr;
    // float price=0;
    // cout << "Enter the price :";
    // getline(cin, mystr);
    // stringstream(mystr) >> price;

    // int quantity;
    // cout << "Enther the quantitiy :";
    // getline(cin, mystr);
    // stringstream(mystr) >> quantity;

    // cout << "The total cost is " << price*quantity << ".\n"; 


    // string mystr;
    // cout << "Name : ";
    // getline(cin, mystr);
    // cout << "Hello, " << mystr << "! What is your favorite team?\n";
    // getline(cin, mystr);
    // cout << "Oh that's interesting. I like " << mystr << ", too.\n" << endl;
    


    // int i ;
    // cout << "Enter an integer that you want : ";
    // cin >> i;
    // cout << "What you have entered is an integer : "<< i <<endl;
    // cout << "And its double is " << 2*i << ".\n" << endl;
    return 0;
}