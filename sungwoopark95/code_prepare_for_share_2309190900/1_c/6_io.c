#include <stdio.h>
#include <unistd.h>

int main(void){
    char c='h';
    putchar(c);
    putchar('e');
    // sleep(5);
    putchar(104); //ASCII value로 인식

    char d;
    d=getchar();
    putchar(d);
}