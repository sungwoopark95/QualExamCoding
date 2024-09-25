#include <stdio.h>

int main() {
    int a, b;
    // EOF가 아닐때까지 while 반복되는 방식으로
    while(scanf("%d %d", &a, &b) != EOF){
        printf("%d\n", a+b);
    }
    return 0;
}