/*
사용자로부터 영어 알파벳 대/소문자 10개를 입력 받은 후 이를 사전 기준 역순으로 출력하는 함수

1. 단, 동일 알파벳의 대/소문자가 같이 있는 경우 대문자가 앞에 출력되도록 한다.
2. 역순으로 정렬 시 Insertion Sort 알고리즘을 변형하여 사용
3. 동일 알파벳이 중복해서 입력으로 주어지지는 않는다고 가정 (단, 대/소문자로
구분되는 경우는 제외)
    ex) A a는 가능 (AA or aa 는 불가능)
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_NUMS 10

// 문자열 배열을 인자로 받아서 역순으로 정렬하는 함수
void InsertionSortReverse(char list[]);

int main(int argc, char* argv[])
{
    char chars[MAX_NUMS]; // 정렬될 문자들의 배열

    // 입력된 인자의 개수가 예상되는 값보다 적은 경우 경고 메시지 출력
    if (argc < MAX_NUMS){
        printf("Please give %d inputs\n", MAX_NUMS);
        return -1;
    }

    // 인자로 받은 문자들을 배열에 저장
    for (int index=0; index < MAX_NUMS; index++)
    {
        chars[index] = argv[index + 1][0];    
    }

    InsertionSortReverse(chars); // 정렬 함수 호출

    // 정렬된 문자열 출력  
    for (int index = 0; index < MAX_NUMS; index++)
        printf("%c", chars[index]);
    printf("\n");

    return 0;
}

void InsertionSortReverse(char list[])
{
    int unsorted;
    int sorted;
    char unsortedItem;
    
    // 삽입 정렬로 문자열 배열을 역순으로 정렬
    for (unsorted = 1; unsorted < MAX_NUMS; unsorted++) {
        int capitalFlag = 0; // 현재 문자가 대문자인지 표시하는 플래그
        unsortedItem = list[unsorted];
        // 현재 문자가 대문자라면 소문자로 변경
        if (unsortedItem < 'a'){
            unsortedItem += 32;
            capitalFlag = 1;
        }

        // 모든 비교는 소문자를 기준으로 함
        for (sorted = unsorted - 1; 
            (sorted >= 0) && ((list[sorted] >= 'a' && list[sorted] < unsortedItem) || (list[sorted] < 'a' && list[sorted]+32 < unsortedItem)); 
            sorted--) {
            list[sorted + 1] = list[sorted];
        }

        // 대문자 플래그가 설정된 경우 다시 대문자로 변경
        if (capitalFlag){
            unsortedItem -= 32;
        }
        list[sorted + 1] = unsortedItem;
    }

    // 중복 문자가 있으면 첫 번째 문자를 대문자로 변환
    for (int i = 0; i < MAX_NUMS-1; i++){
        if (list[i] == list[i+1] + 32){
            list[i] -= 32;
            list[i+1] += 32;
        }
    }
}
