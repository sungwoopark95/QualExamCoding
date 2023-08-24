/*
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
/*
파일에서 숫자를 읽어서 링크드 리스트를 생성합니다.
명령줄 인수로 주어진 숫자들이 링크드 리스트 내에서 연속적으로 연결되어 있는지 확인합니다.
연속적으로 연결된 그룹의 개수를 계산하고 출력합니다.
*/

// 노드를 정의하는 구조체
typedef struct Node {
    int data;               // 노드에 저장되는 데이터
    struct Node* next;     // 다음 노드를 가리키는 포인터
} Node;

// 새로운 노드를 생성하고 초기화하는 함수
Node* newNode(int data) {
    Node* temp = (Node*)malloc(sizeof(Node));  // 노드의 크기만큼 메모리 할당
    temp->data = data;                         // 데이터 저장
    temp->next = NULL;                         // 다음 노드를 NULL로 초기화
    return temp;                               // 새로 생성된 노드 반환
}

// 링크드 리스트의 끝에 노드를 추가하는 함수
void append(Node** head, int data) {
    Node* temp = newNode(data);                // 새 노드 생성
    if (*head == NULL) {                       // 리스트가 비어 있으면
        *head = temp;                          // head에 새 노드 저장
        return;
    }
    Node* last = *head;                        // 현재 노드를 head로 설정
    while (last->next != NULL) {               // 리스트의 끝을 찾을 때까지 순회
        last = last->next;
    }
    last->next = temp;                         // 마지막 노드의 다음에 새 노드 추가
}

// 주어진 값들이 연속적으로 연결된 그룹에 있는지 확인하는 함수
int isInSameCluster(Node* head, int* arr, int size) {
    Node* curr = head;                         // 현재 노드를 head로 설정
    while (curr) {
        int count = 0;                          // 일치하는 노드 수를 저장하는 변수
        // 현재 노드와 배열의 값이 일치하는 동안 순회
        while (curr && count < size && curr->data == arr[count]) {
            curr = curr->next;
            count++;
        }
        if (count == size) {                    // 모든 값이 일치하면 1 반환
            return 1;
        }
        curr = curr->next;                      // 다음 노드로 이동
    }
    return 0;                                   // 일치하는 그룹을 찾지 못하면 0 반환
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("인수가 충분하지 않습니다.\n");
        return -1;
    }

    FILE* file = fopen(argv[1], "r");           // 입력 파일 열기
    if (!file) {
        printf("파일을 열 수 없습니다.\n");
        return -1;
    }

    Node* head = NULL;
    int num;
    // 파일에서 숫자를 읽어서 링크드 리스트 생성
    while (fscanf(file, "%d", &num) != EOF) {
        append(&head, num);
    }
    fclose(file);                               // 파일 닫기

    int clusters = 0;                           // 연속된 그룹의 수 저장
    for (int i = 2; i < argc; i++) {
        int arr[argc-2];
        int j;
        // 명령줄 인수에서 숫자 읽기
        for (j = 0; j < argc-2 && i+j < argc; j++) {
            arr[j] = atoi(argv[i+j]);
        }
        // 해당 숫자가 연속된 그룹에 있는지 확인
        if (isInSameCluster(head, arr, j)) {
            clusters++;                         // 그룹 수 증가
            i += j - 1;                         // 다음 그룹으로 이동
        }
    }

    printf("%d\n", clusters);                    // 연속된 그룹의 수 출력

    return 0;
}
