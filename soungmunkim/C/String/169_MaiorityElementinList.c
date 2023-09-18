/*

Given an array nums of size n, 
    return the majority element.

The majority element is the element that appears 
    more than(이상) ⌊n / 2⌋ times. 
    You may assume that the majority element 
    always exists in the array.

(base) soungmunkim@gimseongmun-ui-MacBookPro String % gcc 169_MaiorityElementinList.c -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test                                 
Enter the list of integers in the format [x,y,z,...]: [3,2,3]
The majority element is: 3

(base) soungmunkim@gimseongmun-ui-MacBookPro String % ./test                                 
Enter the list of integers in the format [x,y,z,...]: [2,2,1,1,1,2,2]
The majority element is: 2
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

# define NUMBER_SIZE 10

// 0-9 까지 빈도 저장하는 구조체 정의
// int dict
typedef struct {
    int count[NUMBER_SIZE];
} Counter;

Counter newCounter(){
    Counter c;
    for (int i=0; i<NUMBER_SIZE; i++){
        c.count[i] = 0;
    }
    return c;
}

int majorityElem(int* nums, int size){
    Counter num_cnt = newCounter();
    
    for(int i=0; i<size; i++){
        num_cnt.count[nums[i]]++;
    }

    int majority = size / 2; // C에서는 몫이어서 more than도 >
    
    // majority값보다 큰 count인 number 내보냄
    for(int j=0; j<NUMBER_SIZE; j++){
        if(num_cnt.count[j] > majority){
            return j;
        }
    }
    return -1;
}

int main() {
    // 사용자에게 숫자 리스트를 입력하라는 메시지를 출력
    printf("Enter the list of integers in the format [x,y,z,...]: ");
    char line[1000]; // 입력 라인의 최대 길이로 가정
    fgets(line, sizeof(line), stdin); // 전체 라인을 읽음

    // \n character을 지우기 
    char *newline = strchr(line, '\n');
    if (newline) {
        *newline = '\0';
    }

    int arr[1000]; // 최대 1000개의 숫자를 가정
    int n = 0;
    char *token = strtok(line, "[], "); // 대괄호, 쉼표, 공백을 기준으로 첫 번째 토큰(숫자)를 얻음
    while (token) {
        arr[n++] = atoi(token); // 토큰을 정수로 변환하여 배열에 추가
        token = strtok(NULL, "[], "); // 다음 토큰을 얻음
    }

    int result = majorityElem(arr, n);

    printf("The majority element is: %d\n", result);

    // 메모리 해제 (간략하게 생략)
    return 0;
}
