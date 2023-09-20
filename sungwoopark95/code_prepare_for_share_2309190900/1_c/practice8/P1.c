//1. Complete a program that checks whether a year is a leap year or not.
/*
<Conditions of a Leap Year>
To check if a year is a leap year, divide the year by 4.
If it is fully divisible by 4, it is a leap year. 
For example, the year 2016 is divisible 4, so it is a leap year, whereas 2015 is undivisible, therefore not.
However, Century years like 300, 700, 1900, 2000 need to be divided by 400 to check
whether they are leap years or not.

- If the input is a leap year: print "{Year} is a Leap Year"
- If the input is NOT a leap year: print "{Year} is not a Leap Year"

Please Read The Instruction Carefully
*/


#include <stdio.h>

void print_whether_leap_year(int year, int flag){
    if (flag==1){printf("%d is a Leap Year\n", year);}
    else {printf("%d is not a Leap Year\n", year);}
}
int main()
{
    int y;
    


    printf("Enter year: ");
    scanf("%d",&y);
    
    /* YOUR CODE HERE */
    if (y%4==0) {
        if (y%100==0) {
            if (y%400==0) { print_whether_leap_year(y, 1); }
            else {print_whether_leap_year(y, 0);}
        }
        else {
            print_whether_leap_year(y, 1);
        }
    }
    else {print_whether_leap_year(y, 0);}

    /*DO NOT MODIFY THE CODE UNDER*/
    return 0;
}