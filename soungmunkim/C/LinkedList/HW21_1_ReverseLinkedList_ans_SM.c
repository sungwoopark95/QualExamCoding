/*
[reversed linked list]
프로그램의 입력값(Argument)으로 Singly linked list의 각 Data값을 순서대로 입력 받은 뒤, 
순서를 뒤집은 Singly linked list로 만들고 이를 출력하는 함수를 작성하여라.
 (출력 시 node 사이에 공백이나 맨 마지막에 공백, new line 등은 불필요함) 

※ Command line argument 입력 시 각 node는 공백(space)으로 구분된다. 

TestCase1)
>>> ./P1 1 2 3 4 5
54321
*/

#include <stdio.h>
#include <stdlib.h>

// 연결 리스트의 노드 구조체
struct Node {
    int data;
    struct Node* next;
};

// 새 노드를 생성하는 함수
struct Node * createNode(struct Node * newNode, int data){
  // 새로운 노드에 대한 메모리를 할당
  newNode = (struct Node *) malloc(sizeof(struct Node));
  // 데이터 설정
  newNode->data = data;
  // 다음 노드를 NULL로 초기화
  newNode->next = NULL;
  return newNode;
}


int main(int argc, char* argv[])
{  
  // 입력된 인자의 개수를 계산
  int length = argc - 1;

  // 입력 정수를 사용하여 연결 리스트 생성
  int k = 1;
  struct Node * head = NULL;
  struct Node * prev = NULL;
  struct Node * curr = NULL;

addNode:
  // 새 노드 생성
  curr = createNode(curr, atoi(argv[k]));  
    
  // 현재 노드가 첫 번째 노드가 아니라면, 이전 노드의 next를 현재 노드로 설정
  if (k > 1)
    prev->next = curr;
  // 현재 노드가 첫 번째 노드라면, head를 현재 노드로 설정
  else
    head = curr;

  k++;
  // prev를 현재 노드로 업데이트
  prev = curr;

  // 더 추가할 노드가 있다면 addNode로 돌아가서 아래 코드를 다시 실행
  if (k <= length)
    goto addNode;

  // 연결 리스트를 역순으로 변경하는 코드 부분
  curr = head->next;
  prev = head;
  head->next = NULL; // 첫 번째 노드의 next 포인터를 NULL로 설정하여, 리스트의 끝을 나타내게 합니다.
  struct Node * currNext = NULL; // 다음에 처리할 노드의 주소를 임시로 저장할 변수 currNext를 선언하고 초기화

  while (curr) {
    currNext = curr->next; // 현재 노드의 next 포인터 값을 currNext에 저장 (방향 바꿔도 다음 노드 정보 keep)
    curr->next = prev; // 현재 노드의 next 포인터를 이전 노드(prev)를 가리키도록 변경
    prev = curr; // 이전 노드(prev)를 현재 노드로 업데이트
    curr = currNext; // 현재 노드(curr)를 currNext로 업데이트 (다음 노드로 넘어감)
  }

  head = prev; // 리스트가 뒤집힌 후, prev는 새로운 첫 번째 노드(원래 리스트의 마지막 노드)를 가리키고 있음


  // 연결 리스트를 출력하는 부분
  curr = head;

  while (curr){
    printf("%d", curr->data);
    curr = curr->next;
  }

  return 0;
}
