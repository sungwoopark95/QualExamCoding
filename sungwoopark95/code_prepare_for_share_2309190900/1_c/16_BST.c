#include <stdio.h> //printf, scanf
#include <stdlib.h> //malloc
#include <stdbool.h> //bool

typedef struct Node{
    int val;
    struct Node* left;
    struct Node* right;
} Node;

void node_init(Node* node, int x){
    node->val = x;
    node->left = NULL;
    node->right = NULL;
}

typedef struct {
    Node* root;
} BST;

void bst_init(BST* bst){
    bst->root=NULL;
}

Node* search_help(Node* currNode, int x){
    if (currNode==NULL) {
        printf("No such valued node.\n");
        return NULL;
    }
    if (x==currNode->val){
        return currNode;
    }
    else if (x<currNode->val){
        return search_help(currNode->left, x);
    }
    else {
        return search_help(currNode->right, x);
    }
}

Node* search(BST* bst, int x){
    return search_help(bst->root, x);
}

Node* insert_help(Node* currNode, int x){
    if (currNode==NULL){
        Node* newNode =(Node*) malloc(sizeof(Node));
        node_init(newNode, x);
        return newNode;
    }

    if (x<currNode->val){
        currNode->left=insert_help(currNode->left, x);
    }
    else if (x>currNode->val){
        currNode->right=insert_help(currNode->right, x);
    }
    else {
        printf("Already exist. (Value : %d)\n", x);
        return currNode;
    }
    return currNode;

}

void insert(BST* bst, int x){
    bst->root = insert_help(bst->root, x);
}

int find_min(Node* currNode) {
    Node* current = currNode;
    while (current->left!=NULL){
        current=current->left;
    }
    return current->val;
}

Node* delete_help(Node* currNode, int x){
    if (currNode==NULL) {
        printf("No such valued node (%d).\n", x);
    }
    if (x<currNode->val){
        currNode->left=delete_help(currNode->left, x);
    }
    else if(x>currNode->val){
        currNode->right=delete_help(currNode->right, x);
    }
    else {
        if ((currNode->left==NULL) && (currNode->right==NULL)) {
            return NULL;
        }
        else if (currNode->left==NULL){
            return currNode->right;
        }
        else if (currNode->right==NULL){
            return currNode->left;
        }
        else {
            int min_val = find_min(currNode->right);
            currNode->val=min_val;
            currNode->right=delete_help(currNode->right, min_val);
        }
    }
    return currNode;
}

void delete(BST* bst, int x){
    bst->root = delete_help(bst->root, x);
}

int main() {
    BST bst;
    bst_init(&bst);

    insert(&bst, 5);
    insert(&bst, 3);
    insert(&bst, 7);
    insert(&bst, 1);
    insert(&bst, 4);
    insert(&bst, 6);
    insert(&bst, 8);

    Node* result = search(&bst, 5);
    if (result != NULL) {
        printf("Found node with value %d\n", result->val);
    } else {
        printf("Node not found\n");
    }

    delete(&bst, 5);

    result = search(&bst, 5);
    if (result != NULL) {
        printf("Found node with value %d\n", result->val);
    } else {
        printf("Node not found\n");
    }

    return 0;
}