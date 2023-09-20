#include <cstdlib>
#include <iostream>
#include <math.h>
#include "mycode.h"

// Fill in

void Shape::print(void){
    printf("This is Shape. Area is %f\n", area());
}

float Square::area(void){
    return len*len;
}

void Square::print(void){
    printf("This is Square. Area is %f\n", area());
}



float Equilateral::area(void){
    return sqrt(3)/4*len*len;
}

void Equilateral::print(void){
    printf("This is Equilateral. Area is %f\n", area());
}
