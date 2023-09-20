#include "bst_by_class.h"


    
void erase(BST* mybst, int x){
    cout << "ERASE (" << x <<")" << endl;
    mybst->delete_bst(x);
    mybst->print_bst();
}

int main(int argc, char** argv){
    
    BST* mybst = new BST();
    vector<int> value = {9, 17, 4, 13, 16, 23, 34, 40, 5};

    for (int i=0; i<value.size();i++){
        cout<< "Insert ("<<value[i] <<")\n";
        mybst->insert_bst(value[i]);
        mybst->print_bst();
        cout<< "\n";
    }
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " [selector]" << endl;
        cout << "Selector 0: erase 4" << endl;
        cout << "Selector 1: erase 9" << endl;
        cout << "Selector 2: erase 34" << endl;
        cout << "Selector 3: erase 16" << endl;
        cout << "Selector 4: erase 17" << endl;
        return EXIT_FAILURE;
    }

    int selector = atoi(argv[1]);

    switch (selector) {
        case 0: erase(mybst, 4); break;
        case 1: erase(mybst, 9); break;
        case 2: erase(mybst, 34); break;
        case 3: erase(mybst, 16); break;
        case 4: erase(mybst, 17); break;
    }
    return EXIT_SUCCESS;
}