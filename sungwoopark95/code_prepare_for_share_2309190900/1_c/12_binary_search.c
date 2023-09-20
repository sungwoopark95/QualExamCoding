#include <stdio.h>

int binary_search(int* l, int length, int val){
    int start = 0;
    int end = length-1;
    int mid;
    while (start<=end){
        mid = (start+end)/2;
        if (l[mid]<val) {
            start = mid +1;
        }
        else {
            end=mid-1;
        }
    }
    if ((start<length) && (l[start]==val)) {
        return start;
    }
    else {
        return -1;
    }
}

int main(void){
    int list[10];
    for (int i=0; i<10; i++){
        list[i]=i+3;
    }
    printf("list : ");
    for (int i=0; i<10; i++){
        printf("%d  ", list[i]);
    }
    printf("\n");
    printf("Want to find {%d} and result is {%d}\n", 1, binary_search(list, 10, 1));
    printf("Want to find {%d} and result is {%d}\n", 3, binary_search(list, 10, 3));
    printf("Want to find {%d} and result is {%d}\n", 9, binary_search(list, 10, 9));
    printf("Want to find {%d} and result is {%d}\n", 12, binary_search(list, 10, 12));
    printf("Want to find {%d} and result is {%d}\n", 15, binary_search(list, 10, 15));
    return 0;
}
