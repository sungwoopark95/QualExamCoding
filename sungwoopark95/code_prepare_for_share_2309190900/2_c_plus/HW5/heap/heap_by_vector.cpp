#include "heap_by_vector.h"

void insert_max_heap(vector<int>* v, const int& var){
    v->push_back(var); // 추가 후
    push_heap(v->begin(), v->end()); //push
}

void pop_max_heap(vector<int>* v){
    pop_heap(v->begin(), v->end()); //pop 후
    v->pop_back(); // size 줄이기
}

void print_array(vector<int>* v) {
    cout << "array : ";
    for (vector<int>::iterator it=v->begin(); it!=v->end();it++){
        cout << *it << " ";
    }
    cout << "\n";
}

void print_tree(vector<int>* v){
    int height = ceil(log2(v->size() + 1));  // Calculate the height of the tree
    int level_start = 0;  // The first index of the current level

    for (int i = 0; i < height; ++i) {
        int level_end = min((int)pow(2, i + 1) - 1, (int)v->size());  // The last index of the current level
        for (int j = level_start; j < level_end; ++j) {
            cout << v->at(j) << ' ';
        }
        cout << '\n';
        level_start = level_end;
    }
}