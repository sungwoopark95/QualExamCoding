/*
Binary Tree의 모든 node에 대해서, 해당 노드의 left subtree의 depth와 right subtree의 depth가 1보다 많이 차이나면 False, 1 이하로 차이나면 True
=> 모든 node에 대해 검사해야 하므로 recursion 필요!

int a = 3, b = 9, c = 20, d = 15, e = 7;
int* root_list[] = {&a, &b, &c, NULL, NULL, &d, &e};
TreeNode* root = list_to_btree(root_list, 7);
printf("%d\n", isBalanced(root));
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Definition for a binary tree node.
typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 노드들을 연결하기 위해 리스트를 순회하는 함수
TreeNode* list_to_btree(int* nums[], int size) {
    if (size == 0) {
        return NULL;
    }

    struct Queue {
        TreeNode* node;
        struct Queue* next;
    };

    struct Queue* front = NULL;
    struct Queue* rear = NULL;

    TreeNode* root = malloc(sizeof(TreeNode));
    root->val = *nums[0];
    root->left = NULL;
    root->right = NULL;

    struct Queue* new_node = malloc(sizeof(struct Queue));
    new_node->node = root;
    new_node->next = NULL;
    front = rear = new_node;

    int i = 1;
    while (front && i < size) {
        TreeNode* current = front->node;
        struct Queue* temp = front;
        front = front->next;
        free(temp);

        if (nums[i]) {
            current->left = malloc(sizeof(TreeNode));
            current->left->val = *nums[i];
            current->left->left = NULL;
            current->left->right = NULL;
            struct Queue* left_node = malloc(sizeof(struct Queue));
            left_node->node = current->left;
            left_node->next = NULL;
            if (rear) {
                rear->next = left_node;
                rear = left_node;
            }
        }
        i++;
        if (i < size && nums[i]) {
            current->right = malloc(sizeof(TreeNode));
            current->right->val = *nums[i];
            current->right->left = NULL;
            current->right->right = NULL;
            struct Queue* right_node = malloc(sizeof(struct Queue));
            right_node->node = current->right;
            right_node->next = NULL;
            if (rear) {
                rear->next = right_node;
                rear = right_node;
            }
        }
        i++;
    }
    return root;
}

// 함수 bfs는 주어진 노드로부터 가장 깊은 깊이(레벨)를 반환합니다.
int bfs(TreeNode* root) {
    if (!root) {
        return 0;
    }

    struct QueueNode {
        TreeNode* treeNode;
        int level;
        struct QueueNode* next;
    };

    struct QueueNode* front = malloc(sizeof(struct QueueNode));
    front->treeNode = root;
    front->level = 0;
    front->next = NULL;

    struct QueueNode* rear = front;
    int curr_level;

    while (front) {
        TreeNode* curr_node = front->treeNode;
        curr_level = front->level;
        struct QueueNode* temp = front;
        front = front->next;
        free(temp);

        if (curr_node->left) {
            struct QueueNode* left_node = malloc(sizeof(struct QueueNode));
            left_node->treeNode = curr_node->left;
            left_node->level = curr_level + 1;
            left_node->next = NULL;
            if (rear) {
                rear->next = left_node;
                rear = left_node;
            }
        }

        if (curr_node->right) {
            struct QueueNode* right_node = malloc(sizeof(struct QueueNode));
            right_node->treeNode = curr_node->right;
            right_node->level = curr_level + 1;
            right_node->next = NULL;
            if (rear) {
                rear->next = right_node;
                rear = right_node;
            }
        }
    }
    return curr_level + 1;
}

// 트리의 루트 노드에서 시작하여 전체 트리가 균형 잡혔는지 판단하는 함수
bool isBalanced(TreeNode* root) {
    if (!root) {
        return true;
    }
    int left_depth = bfs(root->left);
    int right_depth = bfs(root->right);
    if (abs(left_depth - right_depth) > 1) {
        return false;
    }
    return isBalanced(root->left) && isBalanced(root->right);
}

void free_tree(TreeNode* root) {
    if (!root) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main() {
    int a = 3, b = 9, c = 20, d = 15, e = 7;
    int* root_list[] = {&a, &b, &c, NULL, NULL, &d, &e};
    TreeNode* root = list_to_btree(root_list, 7);
    printf("%d\n", isBalanced(root));

    free_tree(root);
}
