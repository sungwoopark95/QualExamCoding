#include <cstdlib>
#include <iostream>
#include "CFDS1_HW3_Polymorphsim_SM.h"

int main() {
    Square sq(0.5f);
    Equilateral eq(4.0f);

    sq.print();
    eq.print();

    Shape *s1 = &sq;
    Shape *s2 = &eq;

    s1->print();
    s2->print();

    return EXIT_SUCCESS;
}