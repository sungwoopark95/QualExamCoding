#include <cstdlib>
#include <iostream>
#include <math.h>
using namespace std;

bool is_prime(int n) {
    if (n <= 1) { return false; }
    for (int i=2;i<=sqrt(n);i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    unsigned int start_num;
    unsigned int end_num;

    cout << "Find prime number within a range:\n";
    cout << "--------------------------------------\n";
    cout << "-> The start of the range: ";
    // TODO: set start_num
    cin >> start_num;

    cout << "-> The end of the range: ";
    // TODO: set end_num
    cin >> end_num;

    cout << "\nThe prime numbers between " << start_num << " and " << end_num << " are:" << endl;

    // TODO: print prime numbers
    for (int n=start_num;n<=end_num;n++) {
        if (is_prime(n)) {
            cout << n << " ";
        }
    }
    cout << endl;

    return EXIT_SUCCESS;
}
