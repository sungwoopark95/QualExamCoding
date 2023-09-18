/*
주어진 후보 숫자 집합(candidates)과 목표 숫자(target)가 있을 때, 후보 숫자의 합이 목표 숫자가 되는 모든 유일한 조합을 찾아야 합니다.
각 후보 숫자는 조합에서 한 번만 사용될 수 있습니다.
참고: 결과 집합에는 중복된 조합이 포함되어서는 안 됩니다.

예시 1:
입력: candidates = [10,1,2,7,6,1,5], target = 8
출력:
[
[1,1,6],
[1,2,5],
[1,7],
[2,6]
]

예시 2:
입력: candidates = [2,5,2,1,2], target = 5
출력:
[
[1,2,2],
[5]
]
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// 배열의 최대 크기
#define MAX_SIZE 100

// 백트래킹에 필요한 글로벌 변수 정의
int* g_candidates;
int g_candidatesSize;
int** g_result;
int* g_resultRowSizes;
int g_resultSize;
int g_resultCapacity;

int** g_uniqueResult;
int g_uniqueResultSize;
int* g_uniqueResultRowSizes; // 추가한 부분

// qsort 함수에서 사용될 비교 함수
// 두 포인터를 인자로 받아 실제 값의 차이를 반환
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

/* ================================= BackTracking ================================= */
// remaining: 남은 목표 합, start: 조합 탐색 시작 지점, combo: 현재까지의 조합, comboSize: 현재 조합의 크기
void backtrack(int remaining, int start, int* combo, int comboSize) {
    // 남은 목표 합이 0이면, 현재 조합이 목표 합에 해당
    if (remaining == 0) {
        // 현재 조합을 저장할 메모리를 동적 할당
        int* currCombo = (int*)malloc(comboSize * sizeof(int));
        
        // currCombo에 combo의 값을 복사
        memcpy(currCombo, combo, comboSize * sizeof(int));
        
        // 고유한 결과 배열에 현재 조합 추가
        g_uniqueResult[g_uniqueResultSize] = currCombo;
        
        // 현재 조합의 크기를 크기 배열에 저장하고 고유한 결과 크기 증가
        g_uniqueResultRowSizes[g_uniqueResultSize++] = comboSize;
        return;
    } 
    // 남은 목표 합이 0보다 작으면, 현재 조합은 목표 합을 초과하므로 탐색 종료
    else if (remaining < 0) {
        return;
    }

    // start부터 후보 숫자를 하나씩 조합에 추가해 보면서 백트래킹 수행
    for (int i = start; i < g_candidatesSize; i++) {
        // 현재 후보 숫자를 조합에 추가
        combo[comboSize] = g_candidates[i];
        
        // 남은 목표 합을 업데이트하고 백트래킹 재귀 호출
        // i + 1은 중복을 피하기 위해 다음 후보 숫자부터 탐색
        backtrack(remaining - g_candidates[i], i + 1, combo, comboSize + 1);
    }
}
/* =========================================================================== */

/* =================================== Combination Function =================================== */
// 주어진 후보자 배열(candidates)에서 목표 합계(target)를 얻는 조합을 찾는 함수
int** combinationSum2(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes) {
    // candidates 배열을 오름차순 정렬
    qsort(candidates, candidatesSize, sizeof(int), compare);
    
    // 현재 조합을 저장할 배열
    int combo[MAX_SIZE];
    
    // 전역 변수 초기화
    g_candidates = candidates; // 후보자 배열
    g_candidatesSize = candidatesSize; // 후보자 배열의 크기
    g_uniqueResultSize = 0; // 유니크한 결과의 크기
    g_uniqueResult = (int**)malloc(MAX_SIZE * sizeof(int*)); // 유니크한 결과를 저장할 2차원 배열
    g_uniqueResultRowSizes = (int*)malloc(MAX_SIZE * sizeof(int)); // 각 결과의 크기를 저장할 배열 초기화
    
    // 백트래킹을 사용하여 모든 조합을 찾음
    backtrack(target, 0, combo, 0);
    
    // 결과 배열과 그 크기를 저장할 전역 변수 초기화
    g_resultSize = 0;
    g_resultCapacity = 10; // 초기 용량 설정
    g_result = (int**)malloc(g_resultCapacity * sizeof(int*)); // 결과를 저장할 2차원 배열
    g_resultRowSizes = (int*)malloc(g_resultCapacity * sizeof(int)); // 각 결과의 크기를 저장할 배열
    
    // g_uniqueResult에 저장된 모든 조합을 검사하여 중복되지 않는 조합만 g_result에 저장
    for (int i = 0; i < g_uniqueResultSize; i++) {
        bool found = false;
        for (int j = 0; j < g_resultSize; j++) {
            // 기존 결과와 현재 조합을 비교하여 동일한지 확인
            if (memcmp(g_result[j], g_uniqueResult[i], g_resultRowSizes[j] * sizeof(int)) == 0) {
                found = true; // 같은 조합을 찾았다면 플래그 설정
                break;
            }
        }
        // 중복되지 않는 조합만 결과에 추가
        if (!found) {
            g_result[g_resultSize] = g_uniqueResult[i];
            g_resultRowSizes[g_resultSize++] = g_uniqueResultRowSizes[i]; // 수정된 부분
        }
    }
    
    // 결과의 크기와 각 결과의 크기를 반환 값으로 설정
    *returnSize = g_resultSize;
    *returnColumnSizes = g_resultRowSizes;
    
    return g_result; // 최종 결과 반환
}
/* =============================================================================== */

int main() {
    // 테스트 케이스
    int candidates[] = {10,1,2,7,6,1,5}; // 예제로 주어진 값을 사용합니다.
    int target = 8;
    int returnSize;
    int* returnColumnSizes;
    
    int** result = combinationSum2(candidates, sizeof(candidates) / sizeof(int), target, &returnSize, &returnColumnSizes);
    // 결과 출력
    for (int i = 0; i < returnSize; i++) {
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    return 0;
}
