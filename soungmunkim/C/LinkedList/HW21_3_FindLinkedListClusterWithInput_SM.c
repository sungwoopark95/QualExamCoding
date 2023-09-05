/*
File로 읽어서 하는 것이 아닌 Input으로 숫자들 입력 받았을 때
linked list로 연결된 cluster 찾기
*/
#include <stdio.h>
#include <stdlib.h>

/* 연결 리스트의 노드를 표현하는 구조체 */
struct Node {
    int data;               // 노드에 저장될 데이터 값
    struct Node* next;     // 다음 노드를 가리키는 포인터
};

/* 새로운 노드를 생성하고 초기화하는 함수 */
struct Node * createNode(struct Node * newNode, int data){
    newNode = (struct Node *) malloc(sizeof(struct Node)); // 메모리 할당
    newNode->data = data;  // 데이터 설정
    newNode->next = NULL;  // 다음 노드 포인터 초기화
    return newNode;        // 생성된 노드 반환
}

/*------------------ 사용자에게 입력 받았을 때 -----------------------*/
int main()
{
    char input[1000];  // 사용자 입력을 저장할 문자열
    printf("Enter the numbers separated by spaces: ");
    fgets(input, sizeof(input), stdin);  // 사용자로부터 입력 받기

    // 입력을 공백으로 분할하고 연결 리스트 생성
    struct Node* head = NULL;  // 연결 리스트의 헤드
    struct Node* prev = NULL;  // 이전 노드
    struct Node* curr = NULL;  // 현재 노드

    char* token = strtok(input, " ");  // 첫 번째 토큰 추출
    while(token != NULL) {
        int val = atoi(token);  // 문자열을 정수로 변환
        curr = createNode(curr, val);  // 새 노드 생성

        if (prev == NULL) {
            head = curr;  // 첫 번째 노드면 head로 설정
        } else {
            prev->next = curr;  // 이전 노드의 next를 현재 노드로 설정
        }

        prev = curr;  // 이전 노드 업데이트
        token = strtok(NULL, " ");  // 다음 토큰 추출
    }

    int numConnected = 0;  // 연결된 "클러스터"의 수
    int val = 0, cnt = 0;

    if (head != NULL) {
        curr = head;
        while (curr) {
            val = curr->data;
            int found = 0;
            char *token = strtok(input, " ");  // 첫 번째 토큰 추출
            while(token != NULL) {
                if (val == atoi(token)) {
                    cnt++;
                    if (cnt == 1) {
                        numConnected++;
                    }
                    found = 1;
                    break;
                }
                token = strtok(NULL, " ");  // 다음 토큰 추출
            }
            if (!found) {
                cnt = 0;
            }
            curr = curr->next;
        }
    }

    printf("%d", numConnected);  // 결과 출력

    return 0;
}





/*---------------- argv로 입력받았을 때 ------------------------*/
// int main(int argc, char* argv[])
// {  
//     /* 입력 인수들의 길이 */
//     int length = argc - 1;
//     /* 입력 인수들을 저장할 배열 */
//     int * inputArr = (int *) malloc(sizeof(int) * length);

//     /* inputArr 생성 */
//     for (int i = 0; i < length; ++i){
//         inputArr[i] = atoi(argv[i+1]);  // 문자열을 정수로 변환하여 배열에 저장
//     }

//     /* 입력 인수에서 연결 리스트 생성 */
//     struct Node* head = NULL;  // 연결 리스트의 헤드
//     struct Node* prev = NULL;  // 이전 노드
//     struct Node* curr = NULL;  // 현재 노드

//     for (int i = 0; i < length; ++i){
//         curr = createNode(curr, inputArr[i]);  // 새 노드 생성
//         if (i > 0){
//             prev->next = curr;  // 이전 노드의 next를 현재 노드로 설정
//         }
//         else{
//             head = curr;  // 첫 번째 노드면 head로 설정
//         }
//         prev = curr;  // 이전 노드 업데이트
//     }
  
//     /* 연결된 "클러스터"의 수 */
//     int numConnected = 0;
//     // 클러스터 내 노드의 수
//     int val = 0, cnt = 0;

//     if (head != NULL){
//         curr = head;
//         while (curr){
//             val = curr->data;
//             int found = 0;
//             // 현재 노드 값이 배열에 있는지 확인
//             for (int i = 0; i < length; ++i){
//                 // 배열에 값이 있으면 cnt 증가
//                 if (inputArr[i] == val){
//                     cnt++;
//                     // 새로운 클러스터면 numConnected 증가
//                     if (cnt == 1){
//                         numConnected++;
//                     }          
//                     found = 1;
//                     break;
//                 }
//             }
//             // 배열에 값이 없으면 cnt 리셋 (새로운 클러스터 시작)
//             if (!found){
//                 cnt = 0;
//             }
//             // 다음 노드로 이동
//             curr = curr->next;
//         }    
//     } 

//     printf("%d", numConnected);  // 결과 출력

//     return 0;
// }
