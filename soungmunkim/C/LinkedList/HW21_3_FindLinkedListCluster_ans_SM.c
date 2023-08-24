/*
[Linked list에서 cluster 찾기]
프로그램의 첫번째 입력(Argument)으로는 파일 경로를 받은 후 파일을 읽어 Linked list를 생성한다. 
두번째 입력값(Argument)부터는 임의의 정수들을 입력받는다. 
그런 다음 입력으로 받은 정수들이 파일로부터 생성된 Linked list에서 연결되어 있는지를 확인한다. 
서로 연결되어 있는 정수 그룹의 개수를 출력하는 프로그램을 완성하여라. 

※ Input file에 포함되지 않은 정수는 Argument로 들어오지 않는다.
※ Input file에는 중복되는 정수는 존재하지 않는다. 
※ 함수 내에서 File path에 대한 error check는 별도로 필요하지 않다. 
※ 테스트 시, P3.c와 동일한 경로에 inputList.txt를 만들어 테스트하는 것을 권장한다. 

inputList.txt 파일에는 “1 2 3 4 5”가 입력되어 있다고 가정하자. 
그렇다면 Skeleton code를 통해 1->2->3->4->5인 Linked list가 생성될 것이다. 
이 경우의 프로그램 실행 예시는 다음과 같다. 

TestCase1)
>>./P3 inputList.txt 1 2 3
>>1
설명: Linked List가 1-2-3-4-5이고 입력으로 1,2,3이 들어왔다. 
Linked List 내에서 1,2,3은 모두 Link로 연결되어 하나의 그룹(Cluster)을 형성한다. 따라서 그룹의 개수는 1이다.

TestCase2)
>>./P3 inputList.txt 1 3 5
>>3	
설명: Linked List가 1-2-3-4-5이고 입력으로 1,3,5가 들어왔다. 
주어진 Linked List 내에서 1,3,5 사이에는 Link가 존재하지 않는다. 따라서 1,3,5는 별도의 그룹을 각각 형성하므로 그룹의 개수는 3이다. 
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

int main(int argc, char* argv[])
{  
    /* 입력 인수들의 길이 (inputList.txt를 제외) */
    int length = argc - 2;
    /* 입력 인수들을 저장할 배열 (inputList.txt를 제외) */
    int * inputArr = (int *) malloc(sizeof(int) * length);
    /* 첫 번째 인수로 주어진 inputList.txt의 경로 */
    char * filepath = argv[1]; 

    /* inputArr 생성 */
    for (int i = 0; i < length; ++i){
        inputArr[i] = atoi(argv[i+2]);  // 문자열을 정수로 변환하여 배열에 저장
    }

    /* 파일 입력으로 연결 리스트 생성 */
    int k = 1;
    struct Node* head = NULL;  // 연결 리스트의 헤드
    struct Node* prev = NULL;  // 이전 노드
    struct Node* curr = NULL;  // 현재 노드

    FILE *fp = fopen(filepath, "r");  // 파일 열기
    char buffer[10];   // 파일에서 읽은 숫자를 임시 저장할 버퍼
  
    while (fscanf(fp, "%s", buffer) == 1){  // 파일에서 숫자 읽기
        curr = createNode(curr, atoi(buffer));  // 새 노드 생성
        if (k > 1){
            prev->next = curr;  // 이전 노드의 next를 현재 노드로 설정
        }
        else{
            head = curr;  // 첫 번째 노드면 head로 설정
        }
        k++;
        prev = curr;  // 이전 노드 업데이트
    }

    fclose(fp);  // 파일 닫기
  
    /* 연결된 "클러스터"의 수 */
    int numConnected = 0;
    
    // 클러스터 내 노드의 수
    int val = 0, cnt = 0;

    if (head != NULL){
        curr = head;
        while (curr){
            val = curr->data;
            int found = 0;
            // 현재 노드 값이 배열에 있는지 확인
            for (int i = 0; i < length; ++i){
                // 배열에 값이 있으면 cnt 증가
                if (inputArr[i] == val){
                    cnt++;
                    // 새로운 클러스터면 numConnected 증가
                    if (cnt == 1){
                        numConnected++;
                    }          
                    found = 1;
                    break;
                }
            }
            // 배열에 값이 없으면 cnt 리셋 (새로운 클러스터 시작)
            if (!found){
                cnt = 0;
            }
            // 다음 노드로 이동
            curr = curr->next;
        }    
    } 

    /* 아래 코드는 수정하지 않음 */	
    printf("%d", numConnected);

    return 0;
}
