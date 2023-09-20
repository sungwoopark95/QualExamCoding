#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void merge(int* l, int start, int mid, int end) {
    int len1=mid-start+1;
    int len2=end-(mid+1)+1;
    int sub1[len1];
    int sub2[len2];
    memcpy(sub1, l+start, (len1)*sizeof(int)); 
    memcpy(sub2, l+mid+1, (len2)*sizeof(int));
    int k = start;
    int i = 0;
    int j = 0;
    while ((i<len1) && (j<len2)) {
        if (sub1[i]<sub2[j]) {
            l[k]=sub1[i];
            i++;
        }
        else {
            l[k]=sub2[j];
            j++;
        }
        k++;
    }
    if (i<len1) {
        memcpy(l+k, sub1+i, (len1-i)*sizeof(int));
    }
    if (j<len2){
        memcpy(l+k, sub2+j, (len2-j)*sizeof(int));
    }

}

void merge_sort(int* l, int start, int end) {
    if (start==end) {return;}
    int mid = start + (end-start)/2;
    merge_sort(l, start, mid);
    merge_sort(l, mid+1, end);
    merge(l, start, mid ,end);
}

int main(void){
    int length=20;
    int randomArray[length];
    // Seed the random number generator
    srand(time(NULL));

    for (int i=0; i<length; i++){
        randomArray[i]=rand();
    }
    printf("Random Array : ");
    for (int i=0; i<10; i++){
        printf("%d  ", randomArray[i]);
    }
    printf("\n");


    merge_sort(randomArray, 0, length-1);
    printf("After merge sort : ");
    for (int i=0; i<10; i++){
        printf("%d  ", randomArray[i]);
    }
    printf("\n");
    
    return 0;
}