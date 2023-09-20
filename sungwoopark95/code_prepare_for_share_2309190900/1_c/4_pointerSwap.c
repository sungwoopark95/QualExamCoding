#include <stdio.h>

void newSwap(int* firstVal, int* secondVal);

int main(void){
    int valA=5;
    int valB=7;
    printf("Before swap A val is %d and B val is %d.\n", valA, valB);
    newSwap(&valA, &valB);
    printf("After swap A val is %d and B val is %d.", valA, valB);
    return 0;
}

void newSwap(int* firstVal, int* secondVal){
    int tmp = *firstVal;
    *firstVal = *secondVal;
    *secondVal = tmp;
}