#include <stdio.h>
#include <stdbool.h>


bool is_prime(int num) {
    bool flag = false;
    int half = num/2;
    for (int x=2; x<=half; x++){
        if (num%x==0) {
            flag=true;
            break;
        }
    }

}

int main(void){
    int cnt =0;
    for (int x=1; x<=100; x++) {
        if (is_prime(x)) {
            cnt++;
            printf("%d\n", x);
        }
    }
    printf("The total number of prime number smaller than 100 is %d.\n", cnt);
    
}