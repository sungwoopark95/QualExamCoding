#pragma once
// #include <vector>
// #include <algorithm>
#include <iostream>
#include <queue> //print_bst 
// #include <cmath>

using namespace std;

class Node {
    public :
    int val;
    Node* left=nullptr;
    Node* right=nullptr;
    Node(int x) : val(x) {};

    Node* search_help(int);
    Node* insert_help(int);
    int find_min(void);
    Node* delete_help(int);
};

class BST {
    public:
    BST() {};
    Node* root=nullptr;
    Node* search_bst(int);
    void insert_bst(int);
    void delete_bst(int);
    void print_bst(void);
};