#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
   int num;

   int size = 0;        // 배열 현재 크기(원소 개수 0개로 시작)
   int capacity = 1;    // 배열 현재 용량(초기화 용량)

   // 초기 int malloc array 설정
   int* arr = (int*)malloc(sizeof(int)*capacity);

   while(scanf("%d", &num) != EOF){
        // 만약 배열 현재 크기가 꽉 찼다면 (용량 늘려주기)
        if(size==capacity){
            // 용량을 두배로 늘리고 다시 arr도 해당 용량 반영하기
            capacity *= 2; 
            arr = (int*)realloc(arr, sizeof(int)*capacity);
        }
        arr[size++] = num; // 숫자 계속 arr에 넣어주기

    }

    // max number와 해당 Index 계속 업뎃
    float max_num = -INFINITY;
    int idx;
    for(int i=0; i<size; i++){
        if(max_num < arr[i]){
            max_num = arr[i];
            idx = i+1;
        }
    }
    printf("%d\n", (int)max_num);
    printf("%d\n", idx);
    free(arr); // 동적 할당 해제
    return 0;
}