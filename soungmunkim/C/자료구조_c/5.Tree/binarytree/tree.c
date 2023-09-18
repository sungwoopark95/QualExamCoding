/*
binary tree

데이터 구조 정의:

Node라는 이름의 구조체를 정의하여 이진 트리의 노드를 표현합니다. 
각 노드에는 데이터(data)와 두 개의 포인터(left, right)가 있습니다. 
이 포인터들은 해당 노드의 왼쪽 자식과 오른쪽 자식을 가리킵니다.

트리 연산:

setLeft와 setRight 함수는 주어진 부모 노드에 왼쪽 또는 오른쪽 자식 노드를 설정합니다.
preorder, inorder, postorder 함수들은 각각 전위, 중위, 후위 순회 알고리즘을 사용하여 트리의 노드들을 방문합니다.

트리 생성 및 순회:

main 함수에서는 15개의 노드로 구성된 이진 트리를 만듭니다.
각 노드에 숫자를 할당하고, setLeft 및 setRight 함수를 사용하여 트리 구조를 설정합니다. 
여기서 사용하는 방식은 숫자가 짝수인 경우 왼쪽 자식으로, 홀수인 경우 오른쪽 자식으로 노드를 할당하는 방식입니다.
트리를 생성한 후, 전위, 중위, 후위 순회 방식으로 트리를 순회하며 노드의 데이터를 출력합니다.
*/

#include <stdio.h>
#include <stdlib.h>

typedef int element;   // int 형을 element로 정의

// 이진 트리의 노드를 표현하는 구조체 정의
typedef struct node
{
	int data;           // 데이터 필드
	struct node* left;  // 왼쪽 자식 노드를 가리키는 포인터
	struct node* right; // 오른쪽 자식 노드를 가리키는 포인터
} Node;

// 부모 노드의 왼쪽 자식을 설정하는 함수
void setLeft(Node* parent, Node* child)
{
	if(parent == NULL || child == NULL) // 부모나 자식 노드가 NULL이면 함수 종료
	{
		return;
	}

	parent->left = child;  // 부모의 왼쪽 자식을 child로 설정
}

// 부모 노드의 오른쪽 자식을 설정하는 함수
void setRight(Node* parent, Node* child)
{
	if (parent == NULL || child == NULL) // 부모나 자식 노드가 NULL이면 함수 종료
	{
		return;
	}

	parent->right = child; // 부모의 오른쪽 자식을 child로 설정
}

// 주어진 수가 짝수인지 판별하는 함수
int isEvenNumber(int number)
{
	return number % 2 == 0;  // 수를 2로 나눈 나머지가 0이면 짝수
}

// 전위 순회 (Preorder Traversal) 함수
void preorder(Node* node)
{
	if(node == NULL)  // 노드가 NULL이면 함수 종료
	{
		return;
	}

	printf("%d ", node->data);  // 노드의 데이터 출력
	preorder(node->left);       // 왼쪽 서브 트리를 전위 순회
	preorder(node->right);      // 오른쪽 서브 트리를 전위 순회
}

// 중위 순회 (Inorder Traversal) 함수
void inorder(Node* node)
{
	if (node == NULL) // 노드가 NULL이면 함수 종료
	{
		return;
	}

	inorder(node->left);        // 왼쪽 서브 트리를 중위 순회
	printf("%d ", node->data);  // 노드의 데이터 출력
	inorder(node->right);       // 오른쪽 서브 트리를 중위 순회
}

// 후위 순회 (Postorder Traversal) 함수
void postorder(Node* node)
{
	if (node == NULL) // 노드가 NULL이면 함수 종료
	{
		return;
	}

	postorder(node->left);      // 왼쪽 서브 트리를 후위 순회
	postorder(node->right);     // 오른쪽 서브 트리를 후위 순회
	printf("%d ", node->data);  // 노드의 데이터 출력
}

int main(int argc, char* argv[])
{
	Node* nodes = (Node*)malloc(sizeof(Node) * 16); // 16개의 노드를 동적 할당

	for (int i = 1; i <= 15; ++i)
	{
		nodes[i].data = i;        // 각 노드에 1부터 15까지의 데이터 할당
		nodes[i].left = NULL;     // 초기에는 왼쪽 자식을 NULL로 설정
		nodes[i].right = NULL;    // 초기에는 오른쪽 자식을 NULL로 설정
	}

	for (int i = 1; i <= 15; ++i)
	{
		if(isEvenNumber(i))       // i가 짝수일 경우
		{
			setLeft(&nodes[i / 2], &nodes[i]);  // i/2 번 노드의 왼쪽 자식을 i번 노드로 설정
		}
		else                      // i가 홀수일 경우
		{
			setRight(&nodes[i / 2], &nodes[i]); // i/2 번 노드의 오른쪽 자식을 i번 노드로 설정
		}
	}

	printf("preorder!! \n");      // 전위 순회 시작을 알리는 메시지 출력
	preorder(&nodes[1]);          // 루트 노드부터 전위 순회 실행
	printf("\n");

	printf("inorder!! \n");       // 중위 순회 시작을 알리는 메시지 출력
	inorder(&nodes[1]);           // 루트 노드부터 중위 순회 실행
	printf("\n");

	printf("postorder!! \n");     // 후위 순회 시작을 알리는 메시지 출력
	postorder(&nodes[1]);         // 루트 노드부터 후위 순회 실행
	printf("\n");

	getchar();                    // 사용자의 키 입력을 대기(프로그램 종료 지연)

	return 0;
}
