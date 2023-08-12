/*
사용자로부터 10개 이내의 정수를 입력 받고, 그 중 중복인 숫자만 입력 순서대로 출력하라. 
중복인 숫자가 없으면 -1을 출력하라.(출력 결과의 끝에 space가 있어도 무방)
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_LEN 10

void print_dup_numbers(int* numbers, int n_integers);
bool in(int* numbers, int num, int idx, int length);

int main(int argc, char* argv[]) {
    if (argc == 1) {
      printf("Please input at least 1 integer.\n");
    }

    int numbers[MAX_LEN];
    for (int i = 1; i < argc; ++i) {
        int tmp = atoi(argv[i]);
        numbers[i-1] = tmp;
    }
    print_dup_numbers(numbers, argc-1);

    return 0;
}
/* Do not modify above */

void print_dup_numbers(int* numbers, int n_integers) {
    /*
    numbers: input integer array
    n_integers: length of 'numbers'
    */

    /* Write your code here */
    int copy[n_integers];
    int printed[n_integers];
    int copy_length = 0;
    int num_printed = 0;
    for (int i=0;i<n_integers;i++) {
        int num = numbers[i];
        if (in(numbers, num, i+1, n_integers) && !in(copy, num, 0, copy_length)) {
            copy[copy_length] = num;
            copy_length++;
        } else if (in(copy, num, 0, copy_length) && !in(printed, num, 0, num_printed)) {
            printf("%d ", num);
            printed[num_printed] = num;
            num_printed++;
        }
    }
    
    if (copy_length == 0) {
        printf("%d", -1);
    }
    
    printf("\n");
}

bool in(int* numbers, int num, int idx, int length) {
    for (int i=idx;i<length;i++) {
        if (numbers[i] == num) { return true; }
    }
    return false;
}
