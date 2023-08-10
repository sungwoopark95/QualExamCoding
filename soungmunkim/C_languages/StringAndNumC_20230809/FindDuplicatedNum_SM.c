/*
중복된 숫자 출력하는 함수

1. 사용자로부터 10개 이내의 정수를 입력 받고, 중복된 숫자 한번만 출력하라.
2. 그 중 중복인 숫자만 입력 순서대로 출력하라. (중복된 숫자를 만났을때 해당 숫자 출력하는 방식)
3. 중복인 숫자가 없으면 -1 출력하라.

TestCase1)
./P4 4 3 9 8 8 8 3 1 
83
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_LEN 10

void print_dup_numbers(int* numbers, int n_integers);
int check_in_arr(int check_int, int* check_arr, int size_arr);

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
    int unique[n_integers]; // 중복되지 않는 숫자 넣는 array
    int dup[n_integers]; // 중복되는 숫자 넣는 array

    // array에 넣을때 사용하는 index는 idx
    int idx = 0, idx_dup = 0;
    for(int i = 0; i < n_integers; i++){
        // 현재 숫자 (numbers[i])가 unique arrary에 있는지 check하는 함수
        int checkDup_Uniq = check_in_arr(numbers[i], unique, idx); 

        // 만약 현재 숫자가 처음 나타난거면, unique array에 넣고 idx update
        if (checkDup_Uniq < 0) {
                unique[idx] = numbers[i];
                 ++idx;
        }
        else {
            // 만약 현재 숫자가 처음이 아니라면, dup array에 있는지 체크해보기
            // unique array에서 처음이 아니란 걸 체크했을 때 받아온 index사용 = checkDup_Uniq
            int checkDup_Dup = check_in_arr(numbers[checkDup_Uniq], dup, idx_dup);
            // 현재 숫자가 중복인데 dup array에 없으면 추가하기
            if (checkDup_Dup < 0) {
                dup[idx_dup] = numbers[checkDup_Uniq];
                idx_dup++;
            }
        }
    }
    // 중복된 숫자 프린트하기
    for(int k = 0; k < idx_dup; k++){
        printf("%d ", dup[k]);
    }

    // 최종적으로 중복된 숫자 없으면 -1 프린트
    if (idx_dup == 0){
        printf("-1\n");
    }
}
/*
해당 숫자가 체크하고 싶은 array에 있는지 확인하는 함수
만약 있으면, 해당 숫자의 index를 반환함
만약 없으먄, -1 반환함
*/
int check_in_arr(int check_num, int* check_arr, int size_arr){
    for(int i = 0; i < size_arr; i++){
        if(check_num == check_arr[i])
            return i;
    }
    return -1;
}