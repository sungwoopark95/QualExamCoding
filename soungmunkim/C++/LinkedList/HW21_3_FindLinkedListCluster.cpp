/*
[Linked list에서 cluster 찾기] 사용자에게 숫자로 입력받았을 때

프로그램의 첫번째 입력(Argument)으로는 파일 경로를 받은 후 파일을 읽어 Linked list를 생성한다. 
두번째 입력값(Argument)부터는 임의의 정수들을 입력받는다. 
그런 다음 입력으로 받은 정수들이 파일로부터 생성된 Linked list에서 연결되어 있는지를 확인한다. 
서로 연결되어 있는 정수 그룹의 개수를 출력하는 프로그램을 완성하여라. 

 “1 2 3 4 5”가 입력되어 있다고 가정하자. 
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

#include <iostream>
#include <sstream>
#include <vector>

// 연결 리스트의 노드를 표현하는 클래스
class Node {
public:
    int data;           // 노드에 저장될 데이터 값
    Node* next;         // 다음 노드를 가리키는 포인터

    Node(int val)       // 생성자
        : data(val), next(nullptr) {}   // 멤버 초기화 리스트
};

int main() {
    std::string input;   // 사용자 입력을 저장할 문자열

    std::cout << "Enter the numbers separated by spaces: ";
    getline(std::cin, input);   // 사용자로부터 입력 받기

    // 입력을 공백으로 분할하고 연결 리스트 생성
    Node* head = nullptr;    // 연결 리스트의 헤드 초기화
    Node* prev = nullptr;    // 이전 노드 초기화

    std::istringstream iss(input); // 문자열을 분할하기 위한 스트림 생성
    int val;
    while (iss >> val) {             // 문자열에서 숫자를 하나씩 추출
        Node* curr = new Node(val);   // 새 노드 생성

        if (prev == nullptr) {
            head = curr;    // 첫 번째 노드면 head로 설정
        } else {
            prev->next = curr;    // 이전 노드의 next를 현재 노드로 설정
        }

        prev = curr;  // 이전 노드 업데이트
    }

    int numConnected = 0;  // 연결된 "클러스터"의 수 초기화

    std::istringstream checker(input);  // 문자열을 다시 분할하기 위한 스트림 생성
    std::vector<int> numbers;           // 숫자들을 저장할 벡터

    while (checker >> val) {
        numbers.push_back(val);  // 숫자들을 vector에 저장
    }

    if (head != nullptr) {
        Node* curr = head;             // 헤드로부터 시작
        while (curr) {
            int found = 0;
            for (int num : numbers) {   // 벡터 내의 모든 숫자들을 확인
                if (curr->data == num) {
                    numConnected++;     // 일치하는 숫자 발견 시 클러스터 수 증가
                    found = 1;
                    break;              // 더 이상 탐색 중단
                }
            }
            if (!found) {
                curr = curr->next;      // 일치하는 숫자가 없을 경우 다음 노드로 이동
            }
        }
    }

    std::cout << numConnected << std::endl;  // 결과 출력

    return 0;
}
