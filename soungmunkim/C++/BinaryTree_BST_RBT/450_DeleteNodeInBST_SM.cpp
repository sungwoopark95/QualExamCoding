/*
[BST에서 특정 노드 삭제하기]
!! TreeNode class만 주어졌을 때 !!
> deleteNode(list, key:int) 형태임

< 구헌된 함수들 >
1. create_BST
    Insert
2. transplant
3. delete
4. seach
5. minimum
5. print_BST
    inorder
    level order(왼쪽에서 오른쪽)
    null 표시하게 프린트 or null 없이 프린트

(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % g++ -std=c++17 450_DeleteNodeInBST_SM.cpp -o test
(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree_BST_RBT % ./test                                           
Enter node values in [a,b,c,...] format: [5,3,6,2,4,None,7]
Enter the key to delete: 3
5 4 6 2 Null Null 7 
*/

#include <iostream>
#include <vector>
#include <queue>
#include <sstream>

using namespace std;

// TreeNode 클래스 선언: 이진 트리의 각 노드를 표현하기 위한 클래스
class TreeNode {
public:
    int key; // 노드에 저장될 키 값
    TreeNode* parent; // 부모 노드를 가리키는 포인터
    TreeNode* left;   // 왼쪽 자식 노드를 가리키는 포인터
    TreeNode* right;  // 오른쪽 자식 노드를 가리키는 포인터

    // TreeNode 생성자: 주어진 값으로 노드를 초기화
    TreeNode(int val) : key(val), parent(nullptr), left(nullptr), right(nullptr) {}
};


/*--------------------- insert 함수 구현--------------------------------*/
// 이진 탐색 트리에 키 값을 가진 노드를 삽입하는 함수
TreeNode* insert(TreeNode* root, int key) {
    if (!root) { // 현재 노드가 비어있다면
        return new TreeNode(key); // 새로운 노드를 생성하여 반환
    }

    if (key < root->key) { // 삽입할 키 값이 현재 노드의 키 값보다 작다면

        if (root->left == nullptr) { // 왼쪽 자식이 없다면
            root->left = new TreeNode(key); // 왼쪽 자식에 새 노드를 생성
            root->left->parent = root; // 새로 생성된 노드의 부모를 현재 노드로 설정
        } else { // 왼쪽 자식이 있다면
            insert(root->left, key); // 왼쪽 서브트리에 삽입 재귀적으로 수행
        }

    } else { // 삽입할 키 값이 현재 노드의 키 값보다 크거나 같다면
        if (root->right == nullptr) { // 오른쪽 자식이 없다면
            root->right = new TreeNode(key); // 오른쪽 자식에 새 노드를 생성
            root->right->parent = root; // 새로 생성된 노드의 부모를 현재 노드로 설정
        } else { // 오른쪽 자식이 있다면
            insert(root->right, key); // 오른쪽 서브트리에 삽입 재귀적으로 수행
        }
    }

    return root; // 루트 노드를 반환
}


/*--------------------List에서 BST 만들기 (Insert함수 이용)--------------------------*/
// 주어진 숫자 리스트를 이용하여 이진 탐색 트리(BST)를 생성하는 함수
TreeNode* create_BST(const vector<int>& input_list) {

    TreeNode* root = nullptr; // 트리의 루트를 null로 초기화

    for (int item : input_list) { // 리스트의 각 숫자에 대해
        root = insert(root, item); // 트리에 숫자를 삽입
    }

    return root; // 생성된 트리의 루트를 반환
}


/*------------------ (delete 위해) transplant 함수 구현-----------------------*/
// 삭제 연산을 위한 transplant 함수: u 노드를 v 노드로 대체
TreeNode* transplant(TreeNode* root, TreeNode* u, TreeNode* v) {
    if (!u->parent) { // u가 루트 노드라면
        root = v; // v를 루트로 설정
    } else if (u == u->parent->left) { // u가 부모의 왼쪽 자식이라면
        u->parent->left = v; // 부모의 왼쪽 자식을 v로 변경
    } else { // u가 부모의 오른쪽 자식이라면
        u->parent->right = v; // 부모의 오른쪽 자식을 v로 변경
    }

    if (v) { // v가 nullptr이 아니라면
        v->parent = u->parent; // v의 부모를 u의 부모로 설정
    }

    return root; // 수정된 루트 노드를 반환
}

/*----------------------- (delete or get target 찾는) search 함수 구현 -----------------*/
TreeNode* search(TreeNode* node, int key) {
    while (node && key != node->key) { // 노드가 존재하고, 찾는 키가 아니면 계속 탐색
        if (key < node->key) { // 찾는 키가 노드의 키보다 작으면
            node = node->left; // 왼쪽으로 이동
        } else { // 그렇지 않으면
            node = node->right; // 오른쪽으로 이동
        }
    }
    return node; // 찾은 노드 또는 nullptr 반환
}

/*-------------------------- minimum node 찾는 함수 구현------------------------*/
TreeNode* minimum(TreeNode* node) {
    while (node->left) { // 왼쪽 자식이 존재하면 계속 왼쪽으로 이동
        node = node->left;
    }
    return node; // 가장 작은 키를 가진 노드 반환
}

/*------------------------ delete 함수 구현 ---------------------------------*/
TreeNode* delete_node(TreeNode* root, int key) {
    TreeNode* z = search(root, key); // 삭제할 노드를 검색

    if (z) { 
        if (!z->left) { // 왼쪽 자식이 없다면
            root = transplant(root, z, z->right); // 오른쪽 자식으로 transplant
            delete z; // 노드 메모리 해제
        } else if (!z->right) { // 오른쪽 자식이 없다면
            root = transplant(root, z, z->left); // 왼쪽 자식으로 transplant
            delete z; // 노드 메모리 해제
        } else { // 두 자식이 모두 존재하는 경우

            TreeNode* y = minimum(z->right); // 오른쪽 서브트리의 최솟값을 찾음

            if (y->parent != z) { // y가 z의 직접적인 오른쪽 자식이 아닌 경우
                root = transplant(root, y, y->right); // y를 y의 오른쪽 자식으로 대체
                y->right = z->right; // y의 오른쪽 자식을 z의 오른쪽 자식으로 설정
                y->right->parent = y; // y의 오른쪽 자식의 부모를 y로 설정
            }

            root = transplant(root, z, y); // z를 y로 대체
            y->left = z->left; // y의 왼쪽 자식을 z의 왼쪽 자식으로 설정
            y->left->parent = y; // y의 왼쪽 자식의 부모를 y로 설정

            delete z; // 노드 메모리 해제
        }
    }
    return root; // 루트 노드 반환
}


/*------------------------- 왼쪽에서 오른쪽 방향으로 BFS 형태로 프린트 하기 ----------------*/
// vector<int> print_BST(TreeNode* node) {
//     if (!node) {              // 노드가 없으면 빈 벡터 반환
//         return {};
//     }

//     vector<int> result;       // 결과를 저장할 벡터
//     queue<TreeNode*> queue;   // BFS를 위한 큐. 파이썬의 리스트 대신 C++의 queue를 사용합니다.
//     queue.push(node);        // 초기 큐에 루트 노드 저장

//     while (!queue.empty()) {  // 큐가 빌 때까지 반복
//         TreeNode* current = queue.front(); // 큐에서 노드 꺼내기
//         queue.pop();          // 꺼낸 노드는 큐에서 제거

//         result.push_back(current->key);  // 결과 벡터에 키 값 추가

//         if (current->left) {  // 왼쪽 자식이 있으면 큐에 추가
//             queue.push(current->left);
//         }
//         if (current->right) { // 오른쪽 자식이 있으면 큐에 추가
//             queue.push(current->right);
//         }
//     }

//     return result;            // 결과 벡터 반환
// }


/*----------- (None node Null로 프린트) 왼쪽에서 오른쪽 방향으로 BFS 형태로 프린트 하기 -----------*/
vector<string> print_BST(TreeNode* node) {
    if (!node) { // 노드가 비어 있으면 빈 벡터 반환
        return {};
    }

    vector<string> result; // 결과를 저장할 벡터
    queue<TreeNode*> queue; // BFS를 위한 큐

    queue.push(node); // 루트 노드를 큐에 삽입

    while (!queue.empty()) { // 큐가 비어있지 않으면 계속

        TreeNode* current = queue.front(); // 큐의 맨 앞에 있는 노드를 가져옴
        queue.pop(); // 큐에서 노드를 제거

        if (current) { // 노드가 존재하면
            result.push_back(to_string(current->key)); // 노드의 키 값을 결과에 추가
            queue.push(current->left); // 왼쪽 자식을 큐에 삽입
            queue.push(current->right); // 오른쪽 자식을 큐에 삽입
        } else { // 노드가 비어 있으면
            result.push_back("Null"); // "Null"을 결과에 추가
        }
    }

    while (!result.empty() && result.back() == "Null") { // 결과의 맨 뒤에 "Null"이 있으면 제거
        result.pop_back();
    }

    return result; // 결과 반환
}


// /*---------------------- in order는 sorted list 형태로 나옴 -----------------*/
// vector<int> print_BST(TreeNode* node) {
//     vector<int> result; // 중위 순회의 결과를 저장할 벡터

//     // 중위 순회를 위한 재귀 함수
//     function<void(TreeNode*)> inorder = [&](TreeNode* n) {
//         if (n) {  // 현재 노드가 null이 아니면
//             inorder(n->left);             // 왼쪽 서브트리를 순회합니다.
//             result.push_back(n->key);     // 현재 노드의 키 값을 결과 벡터에 추가합니다.
//             inorder(n->right);            // 오른쪽 서브트리를 순회합니다.
//         }
//     };

//     inorder(node);  // 시작 노드에서 중위 순회를 실행합니다.
//     return result;  // 결과 벡터를 반환합니다.
// }

// // 주어진 키 값에 해당하는 노드를 삭제하고 중위 순회 결과를 반환합니다.
// vector<int> deleteNode(vector<int>& root, int key) {
//     TreeNode* tree = create_BST(root);      // 벡터를 기반으로 이진 탐색 트리를 생성합니다.
//     TreeNode* result_tree = delete_tree(tree, key);  // 주어진 키 값을 가진 노드를 삭제합니다.

//     return print_BST(result_tree);  // 삭제한 후의 트리를 중위 순회한 결과를 반환합니다.
// }


// main function
int main() {
    vector<int> input; // 입력을 저장할 벡터
    string line; // 한 줄의 입력을 저장할 문자열
    int key;

    cout << "Enter node values in [a,b,c,...] format: ";
    getline(cin, line); // 입력 받기

    // 괄호와 쉼표를 제거하고 파싱
    // 첫 번째와 마지막 문자를 제외한 나머지 부분의 문자열
    stringstream ss(line.substr(1, line.size() - 2)); 
    string item;


    while (getline(ss, item, ',')) {
        // 문자열이 "None"이 아니면 리스트에 추가
        if (item != "None") {
            input.push_back(stoi(item));
        }
    }


    cout << "Enter the key to delete: ";
    cin >> key; // 삭제할 키 값을 입력 받기

    TreeNode* root = create_BST(input); // 이진 탐색 트리 생성
    root = delete_node(root, key); // 노드 삭제
    vector<string> output = print_BST(root); // 트리 출력
    
    for (string val : output) {
        cout << val << " ";
    }
    cout << endl;

    return 0; // 프로그램 종료
}






