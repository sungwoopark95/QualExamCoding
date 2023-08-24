/*
중복된 숫자 출력하는 함수

1. 사용자로부터 10개 이내의 정수를 입력 받고, 중복된 숫자 한번만 출력하라.
2. 중복인 숫자가 없으면 -1 출력하라.

TestCase1)
./P4 4 3 9 8 8 8 3 1 
83
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_LEN 10

void print_dup_numbers(int* numbers, int n_integers);

int main(int argc, char* argv[]) {
    if (argc == 1) {
      printf("Please input at least 1 integer.\n");
    }

    int numbers[MAX_LEN];
    // argv[1] 부터 받은 input 시작이기 때문에 1부터 설정하기
    for (int i = 1; i < argc; ++i) {
        int tmp = atoi(argv[i]); //받은 문자열 숫자로 변환 
        // index는 0부터라서 1빼기
        numbers[i-1] = tmp;
    }
    // input 개수는 4개넣으면 0,1,2,3개
    print_dup_numbers(numbers, argc-1);

    return 0;
}
/* Do not modify above*/

void print_dup_numbers(int* numbers, int n_integers) {
    /*
    numbers: input integer array
    n_integers: length of 'numbers'
    */
    /* Write your code here */	
    
    bool hasDuplicates = false; //중복된 숫자가 있는지 확인용

    // cursur를 다른 곳에 계속 두면서 겹치는게 있는지 확인하기
    for(int i = 0; i < n_integers; i++){
        bool isDuplicate = false;
        for(int j = i+1; j < n_integers; j++){
            // 겹치는 숫자가 있으면 isDuplicate = true로 바꾸기
            if(numbers[i] == numbers[j]){
                isDuplicate = true;
                break; // 겹치는게 있으면 멈추기 (빠져나오기)
            }
        }
        // 중복된 값이 (현재 값)이 이미 출력되었는지 확인 용
        if (isDuplicate) {
            bool alreadyPrinted = false;
            // 여태 돌았던 숫자들 중 중복된 값이 전에 있었다면 already printed로 바꾸기
            for(int k = 0; k < i; k++){
                if(numbers[k] == numbers[i]){
                    alreadyPrinted = true;
                    break;
                }
            }
            // 현재 숫자가 중복되었는지 아직 출력되지 않았다면 출력함 (중복된 숫자지만 처음 나온거라면)
            if (!alreadyPrinted){
                printf("%d ", numbers[i]);
                hasDuplicates = true;
            }

        }
    }
    // 최종적으로 중복된 숫자가 없으면 -1 출력함
    if (!hasDuplicates){
        printf("-1");
    }
    printf("\n");
}