#include <stdio.h>

int main(void){

    char name[50];
    int bd_year;
    int bd_month;
    int bd_day;
    printf("Enter last name and birthday YYYY/MM/DD :\n");
    scanf("%s %d/%d/%d", name, &bd_year, &bd_month, &bd_day);
    printf("Name : %s\n", name);
    printf("Birthday : %d/%d/%d", bd_year, bd_month, bd_day);
}