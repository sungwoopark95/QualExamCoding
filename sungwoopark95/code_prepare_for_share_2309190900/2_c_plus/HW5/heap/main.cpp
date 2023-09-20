#include "heap_by_vector.h"

int main(void){
    vector<int> * v = new vector<int>;
    vector<int> value = {9, 17, 4, 13, 16, 23, 34, 40, 5};

    for (int i=0; i<value.size();i++){
        cout<< "Insert ("<<value[i] <<")\n";
        insert_max_heap(v, value[i]);
        print_array(v);
        print_tree(v);
        cout<< "\n";
    }

    cout << "EXTRACT STARTS" << endl;
    for (int i=0; i<3;i++){
        cout<< "POP!!"<<")\n";
        pop_max_heap(v);
        print_array(v);
        print_tree(v);
        cout<< "\n";
    }
    return 0;
}