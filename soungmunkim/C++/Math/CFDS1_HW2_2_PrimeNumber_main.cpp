/*
!! 
[Check Prime Number] 사용자에게 Input 따로 받기
1) 2부터 X-1까지의 모든 자연수로 나누었을 때,
    나누어떨어지는 수가 하나라도 존재하면 X는 소수가아님
2) 2부터 math.sqrt(x) + 1 까지만 확인해서,
    나누어떨어지는 수가 하나라도 존재하면 X는 소수가아님 (더 빠른 방법)

[output]
Find prime number within a range: 
--------------------------------------
-> The start of the range: 1
-> The end of the range: 100

The prime numbers between 1 and 100 are:
2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97 
*/

#include <cstdlib>
#include <iostream>
#include <math.h>
using namespace std;

int main() {
    unsigned int start_num;
    unsigned int end_num;

    // Set start num and end num (Input 받기)
    cout << "Find prime number within a range: " << endl;
    cout << "--------------------------------------\n";
    cout << "-> The start of the range: ";
    cin >> start_num;
    cout << "-> The end of the range: ";
    cin >> end_num;

    cout << "\nThe prime numbers between " << start_num 
        << " and " << end_num << " are:" << endl;

    // Prime number 찾기
    for (unsigned int i = start_num; i <= end_num; i++) {
        bool is_prime = false;
        for (unsigned int j = 2; j <= sqrt(i); j++) {
            if (i % j == 0) {
                is_prime = true;
                break;
            }
        }
        if (is_prime == false && i != 1) {
            cout << i << " ";
        }
    }
    cout << endl;
    return EXIT_SUCCESS;
}