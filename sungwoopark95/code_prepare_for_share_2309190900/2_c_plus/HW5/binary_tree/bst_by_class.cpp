#include "bst_by_class.h"

// 해당 method를 사용하는 instance Node가 있어야 함(nullptr에 대해서는 해당 method를 사용할 수 없음)
// 즉, search를 하기 위해서는 일단 최초의 node가 있어야하는 문제가 있음
Node* Node::search_help(int x){
    
    if (x==this->val){
        return this;
    }
    else if (x<this->val){
        if (this->left==nullptr){
            printf("No such valued node.\n");
            return nullptr;
        }
        else {
            return this->left->search_help(x);
        }
    }
    else {
        if (this->right==nullptr){
            printf("No such valued node.\n");
            return nullptr;
        }
        else {
            return this->right->search_help(x);
        }
    }

}

Node* BST::search_bst(int x){
    if (root==nullptr) {
        printf("Tree is empty.");
        return nullptr;
    }
    else {
        return root->search_help(x);
    }
}
// 아래 method도 Node instance가 있을 때 쓸 수 있음
Node* Node::insert_help(int x){
    
    if (x<this->val){
        if (this->left==nullptr){
            Node* newNode = new Node(x);
            this->left=newNode;
            return this;
        }
        else {
            this->left=this->left->insert_help(x);
        }
    }
    else if (x>this->val){
        if (this->right==nullptr){
            Node* newNode = new Node(x);
            this->right=newNode;
            return this;
        }
        else {
            this->right=this->right->insert_help(x);
        }
    }
    else {
        printf("Already exist. (Value : %d)\n", x);
        return this;
    }
    return this;
}


void BST::insert_bst(int x) {
    if (root==nullptr){
        Node* newNode= new Node(x);
        root = newNode;
    }

    else {
        root = root->insert_help(x);
    }
}


int Node::find_min(void){
    Node* currNode = this;
    while (currNode->left!=nullptr){
        currNode=currNode->left;
    }
    return currNode->val;

}

Node* Node::delete_help(int x){
    // if (this==NULL) {
    //     printf("No such valued node (%d).\n", x);
    // }
    if (x<this->val){
        this->left=this->left->delete_help(x);
    }
    else if(x>this->val){
        this->right=this->right->delete_help(x);
    }
    else {
        if ((this->left==nullptr) && (this->right==nullptr)) {
            return nullptr;
        }
        else if (this->left==nullptr){
            return this->right;
        }
        else if (this->right==nullptr){
            return this->left;
        }
        else {
            int min_val = this->right->find_min();
            this->val=min_val;
            this->right=this->right->delete_help(min_val);
        }
    }
    return this;
}


void BST::delete_bst(int x){
    if (root==nullptr){
        printf("nothing to delete.\n");
    }

    else {
        root = root->delete_help(x);
    }
}


void BST::print_bst(void){
    
    if (root == nullptr) {
        return;
    }

    queue<Node*> nodesQueue;
    int nodesInCurrentLevel = 1;
    int nodesInNextLevel = 0;

    nodesQueue.push(root);

    while (!nodesQueue.empty()) {
        Node* currNode = nodesQueue.front();
        nodesQueue.pop();
        nodesInCurrentLevel--;

        if (currNode) {
            cout << currNode->val << " ";
            nodesQueue.push(currNode->left);
            nodesQueue.push(currNode->right);
            nodesInNextLevel += 2;
        }

        if (nodesInCurrentLevel == 0) {
            cout << endl;
            nodesInCurrentLevel = nodesInNextLevel;
            nodesInNextLevel = 0;
        }
    
    }
    cout<<endl;
}
