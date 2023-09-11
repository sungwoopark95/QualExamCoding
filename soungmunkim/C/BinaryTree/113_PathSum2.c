/*
[root부터 leaf까지 합이 target sum 합과 같은 모든 paths 찾기]

(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree % ./test
Enter node values in [a,b,c,...] format: [5,4,8,11,None,13,4,7,2,None,None,5,1]
Enter target sum: 22
[[5, 4, 11, 2], [5, 8, 4, 5]]

(base) soungmunkim@gimseongmun-ui-MacBookPro BinaryTree % ./test
Enter node values in [a,b,c,...] format: [1,2,3]
Enter target sum: 5
[]

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 이진 트리 노드 구조체
typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 새로운 노드 생성 함수
TreeNode* newNode(int val) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));  // 노드 메모리 할당
    node->val = val;  // 값 설정
    node->left = NULL;  // 왼쪽 자식 초기화
    node->right = NULL;  // 오른쪽 자식 초기화
    return node;  // 생성된 노드 반환
}

// 숫자 배열을 이진 트리로 변환하는 함수
TreeNode* list_to_btree(int* nums, int len) {
    if (len == 0 || nums[0] == -1) return NULL;  // 배열이 비었거나 첫 번째 값이 None일 경우

    TreeNode* root = newNode(nums[0]);  // 루트 노드 생성
    TreeNode* queue[len];
    int front = 0, rear = 0;

    queue[rear++] = root;  // 큐에 루트 노드 추가

    for (int i = 1; i < len && front < rear; i++) {
        TreeNode* current = queue[front++];  // 큐의 앞에서 노드 가져오기

        if (nums[i] != -1) {  // 왼쪽 자식에 대한 값이 None이 아닌 경우
            current->left = newNode(nums[i]);  // 왼쪽 자식 생성
            queue[rear++] = current->left;  // 큐에 추가
        }
        i++;

        if (i < len && nums[i] != -1) {  // 오른쪽 자식에 대한 값이 None이 아닌 경우
            current->right = newNode(nums[i]);  // 오른쪽 자식 생성
            queue[rear++] = current->right;  // 큐에 추가
        }
    }

    return root;  // 생성된 트리의 루트 노드 반환
}

int paths[1000][1000];  // 최대 1000개의 경로를 가정
int pathCount = 0;  // 찾은 경로의 수

void findPaths(TreeNode* root, int* current_path, int depth, int target_sum) {
    if (!root) return;  // 노드가 없으면 리턴

    current_path[depth++] = root->val;  // 현재 경로에 노드 값 추가

    if (!root->left && !root->right) {  // 리프 노드인 경우
        int currentSum = 0;
        for (int i = 0; i < depth; i++) {
            currentSum += current_path[i];  // 경로의 합 계산
        }
        if (currentSum == target_sum) {  // 합이 목표값과 같다면
            for (int i = 0; i < depth; i++) {
                paths[pathCount][i] = current_path[i];  // 경로 저장
            }
            paths[pathCount][depth] = -1;  // 경로의 끝 표시
            pathCount++;  // 경로 수 증가
        }
    } else {
        findPaths(root->left, current_path, depth, target_sum);  // 왼쪽 서브트리 탐색
        findPaths(root->right, current_path, depth, target_sum);  // 오른쪽 서브트리 탐색
    }
}

void hasPathSum2(int* nums, int len, int targetSum) {
    TreeNode* root = list_to_btree(nums, len);  // 배열을 트리로 변환
    int current_path[len];
    pathCount = 0;

    findPaths(root, current_path, 0, targetSum);  // 목표 합을 갖는 경로 찾기
}

int main() {
    int nums[1000];  // 최대 1000개의 노드를 가정
    char line[10000];
    int targetSum, len = 0;

    printf("Enter node values in [a,b,c,...] format: ");
    fgets(line, sizeof(line), stdin);
    char* token = strtok(line, "[], \n");

    while (token != NULL) {
        if (strcmp(token, "None") != 0 && strcmp(token, "null") != 0) {
            nums[len++] = atoi(token);  // 숫자로 변환하여 배열에 저장
        } else {
            nums[len++] = -1;  // None 값 처리
        }
        token = strtok(NULL, "[], \n");
    }

    printf("Enter target sum: ");
    scanf("%d", &targetSum);

    hasPathSum2(nums, len, targetSum);  // 목표 합을 갖는 경로 찾기

    if (pathCount == 0) {
        printf("[]\n");
    } else {
        printf("[");
        for (int i = 0; i < pathCount; i++) {
            printf("[");
            for (int j = 0; paths[i][j] != -1; j++) {
                printf("%d", paths[i][j]);
                if (paths[i][j + 1] != -1) printf(", ");
            }
            printf("]");
            if (i != pathCount - 1) printf(", ");
        }
        printf("]\n");
    }

    return 0;
}

/*----------------------- int main에 예제 주어졌을 경우 -------------------------*/
// int main() {
//     int nums1[] = {5, 4, 8, 11, -1, 13, 4, 7, 2, -1, -1, 5, 1};
//     int len1 = sizeof(nums1) / sizeof(nums1[0]);
//     int targetSum1 = 22;

//     int nums2[] = {1, 2, 3};
//     int len2 = sizeof(nums2) / sizeof(nums2[0]);
//     int targetSum2 = 6;

//     // 첫 번째 예제 실행
//     printf("For input [5,4,8,11,None,13,4,7,2,None,None,5,1] and target sum 22:\n");
//     hasPathSum2(nums1, len1, targetSum1);  // 목표 합을 갖는 경로 찾기

//     if (pathCount == 0) {
//         printf("[]\n");
//     } else {
//         printf("[");
//         for (int i = 0; i < pathCount; i++) {
//             printf("[");
//             for (int j = 0; paths[i][j] != -1; j++) {
//                 printf("%d", paths[i][j]);
//                 if (paths[i][j + 1] != -1) printf(", ");
//             }
//             printf("]");
//             if (i != pathCount - 1) printf(", ");
//         }
//         printf("]\n");
//     }

//     // Reset pathCount for the next example
//     pathCount = 0;

//     // 두 번째 예제 실행
//     printf("\nFor input [1,2,3] and target sum 6:\n");
//     hasPathSum2(nums2, len2, targetSum2);  // 목표 합을 갖는 경로 찾기

//     if (pathCount == 0) {
//         printf("[]\n");
//     } else {
//         printf("[");
//         for (int i = 0; i < pathCount; i++) {
//             printf("[");
//             for (int j = 0; paths[i][j] != -1; j++) {
//                 printf("%d", paths[i][j]);
//                 if (paths[i][j + 1] != -1) printf(", ");
//             }
//             printf("]");
//             if (i != pathCount - 1) printf(", ");
//         }
//         printf("]\n");
//     }

//     return 0;
// }