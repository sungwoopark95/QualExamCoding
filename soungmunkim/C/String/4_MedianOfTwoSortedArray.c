/*
[두개의 sorted array의 median을 구하는 것]

Example 1:
Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.

Example 2:
Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*------------------------------- dynamic array (list 구현) ----------------------------------*/
typedef enum { INT, FLOAT, CHAR, STRING } Type;

typedef union {
    int* iArray;
    float* fArray;
    char* cArray;
    char** sArray;  // 추가된 부분
} ArrayData;

typedef struct {
    Type type;
    ArrayData data;
    int size;
    int capacity;
} DynamicArray;

DynamicArray* createArray(Type type, int initialCapacity) {
    DynamicArray* array = malloc(sizeof(DynamicArray));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    array->type = type;
    array->size = 0;
    array->capacity = initialCapacity;

    switch (type) {
        case INT:
            array->data.iArray = malloc(initialCapacity * sizeof(int));
            break;
        case FLOAT:
            array->data.fArray = malloc(initialCapacity * sizeof(float));
            break;
        case CHAR:
            array->data.cArray = malloc(initialCapacity * sizeof(char));
            break;
        case STRING:
            array->data.sArray = malloc(initialCapacity * sizeof(char*));  // 추가된 부분
            break;
        default:
            fprintf(stderr, "Unknown data type.\n");
            free(array);
            exit(EXIT_FAILURE);
    }

    if (array->data.iArray == NULL) {  // iArray는 공용체의 모든 포인터 멤버와 동일한 주소를 가지므로, 이를 체크하는 것만으로도 충분합니다.
        fprintf(stderr, "Memory allocation for data failed.\n");
        free(array);
        exit(EXIT_FAILURE);
    }

    return array;
}

void append(DynamicArray* array, void* item) {
    if (array->size == array->capacity) {
        array->capacity *= 2;  // Double the capacity
        switch(array->type) {
            case INT:
                array->data.iArray = realloc(array->data.iArray, array->capacity * sizeof(int));
                array->data.iArray[array->size] = *((int*)item);
                break;
            case FLOAT:
                array->data.fArray = realloc(array->data.fArray, array->capacity * sizeof(float));
                array->data.fArray[array->size] = *((float*)item);
                break;
            case CHAR:
                array->data.cArray = realloc(array->data.cArray, array->capacity * sizeof(char));
                array->data.cArray[array->size] = *((char*)item);
                break;
            case STRING:
                array->data.sArray = realloc(array->data.sArray, array->capacity * sizeof(char*));  // 수정된 부분
                array->data.sArray[array->size] = strdup((char*)item);
                break;
        }
    } else {
        switch(array->type) {
            case INT:
                array->data.iArray[array->size] = *((int*)item);
                break;
            case FLOAT:
                array->data.fArray[array->size] = *((float*)item);
                break;
            case CHAR:
                array->data.cArray[array->size] = *((char*)item);
                break;
            case STRING:
                array->data.sArray[array->size] = strdup((char*)item);  // 문자열을 복사합니다.
                break;
        }
    }
    array->size++;
}

void* pop(DynamicArray* array, int index) {
    if (index < 0 || index >= array->size) {
        fprintf(stderr, "Index out of range\n");
        exit(EXIT_FAILURE);
    }

    void* item = malloc(sizeof(int));  // The biggest possible size

    switch(array->type) {
        case INT:
            *((int*)item) = array->data.iArray[index];
            memmove(&array->data.iArray[index], &array->data.iArray[index + 1], (array->size - index - 1) * sizeof(int));
            break;
        case FLOAT:
            *((float*)item) = array->data.fArray[index];
            memmove(&array->data.fArray[index], &array->data.fArray[index + 1], (array->size - index - 1) * sizeof(float));
            break;
        case CHAR:
            *((char*)item) = array->data.cArray[index];
            memmove(&array->data.cArray[index], &array->data.cArray[index + 1], (array->size - index - 1) * sizeof(char));
            break;
        case STRING:
            item = strdup(array->data.sArray[index]);
            free(array->data.sArray[index]);  // 메모리 해제
            memmove(&array->data.sArray[index], &array->data.sArray[index + 1], (array->size - index - 1) * sizeof(char*));
            break;
    }
    array->size--;
    return item;
}

void* get(DynamicArray* array, int index) {
    if (index < 0 || index >= array->size) {
        fprintf(stderr, "Index out of range\n");
        exit(EXIT_FAILURE);
    }

    switch(array->type) {
        case INT:
            return &array->data.iArray[index];
        case FLOAT:
            return &array->data.fArray[index];
        case CHAR:
            return &array->data.cArray[index];
        case STRING:
            return array->data.sArray[index];
    }
    return NULL;
}

void freeArray(DynamicArray* array) {
    switch(array->type) {
        case INT:
            free(array->data.iArray);
            break;
        case FLOAT:
            free(array->data.fArray);
            break;
        case CHAR:
            free(array->data.cArray);
            break;
        case STRING:
            for (int i = 0; i < array->size; i++) {
                free(array->data.sArray[i]);
            }
            free(array->data.sArray);
            break;
    }
    free(array);
}

void printArray(DynamicArray* array) {
    if (array == NULL) {
        printf("Array is NULL\n");
        return;
    }

    printf("[");
    for (int i = 0; i < array->size; i++) {
        if (i != 0) {
            printf(", ");
        }

        switch (array->type) {
            case INT:
                printf("%d", array->data.iArray[i]);
                break;
            case FLOAT:
                printf("%.2f", array->data.fArray[i]);
                break;
            case CHAR:
                printf("%c", array->data.cArray[i]);
                break;
            case STRING:
                printf("\"%s\"", array->data.sArray[i]);
                break;
        }
    }
    printf("]\n");
}
/*-----------------------------------------------------------------------------------------*/

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size){
    // INT 타입의 DynamicArray 예제
    DynamicArray* intArray = createArray(INT, 10);


    int num1_idx = 0;
    int num2_idx = 0;
    // 각 array 비교해서 낮은 숫자를 새로운 array에 넣고 
    // 해당 index를 +1 로 해서 다시 비교 하는 방식
    // 둘 중 한 array를 다 돌면 while 끝
    while (num1_idx<nums1Size && num2_idx<nums2Size) {
        int* value = malloc(sizeof(int));
        if (nums1[num1_idx] <= nums2[num2_idx]){
            *value = nums1[num1_idx];
            num1_idx+=1;
            
        }
        else{
            *value = nums2[num2_idx];
            num2_idx+=1;
        }
        append(intArray, value);
    }
    // printf("the num1 index: %d\n", num1_idx);
    // printf("the num2 index: %d\n", num2_idx);

    // 아직 다 안 돈 array를 다 붙이기 
    if ((num1_idx<nums1Size)){
        for(int i=num1_idx; i<nums1Size; i++){
            // printf("%d\n", nums1[i]);
            int* value1 = malloc(sizeof(int));
            *value1 = nums1[i];
            append(intArray, value1);
        }
    }

    if ((num2_idx<nums2Size)){
        for(int j=num2_idx; j<nums2Size; j++){
            int* value2 = malloc(sizeof(int));
            *value2 = nums2[j];
            append(intArray, value2);
        }
    }


    printArray(intArray);
    double median; 

    // array 홀,짝 길이에 따른 median 구하기
    int arr_size = intArray->size;
    // printf("%d\n", arr_size);
    if(arr_size % 2 == 0){
        int i = arr_size/2;
        int left = *((int*) get(intArray, i-1));
        int right = *((int*) get(intArray, i));
        // printf("left, right: %d, %d\n", left, right);

        median = ((double)left + (double)right) / 2;
    }
    else{
        int j = arr_size/2;
        int num = *((int*) get(intArray, j));
        median = (double)num;
    }

    return median;
    
}

int main(){
    int num1[] = {1, 3};
    int num1Size = 2;

    int num2[] = {2};
    int num2Size = 1;

    double result1;

    result1 = findMedianSortedArrays(num1, num1Size, num2, num2Size);

    printf("The result1 is: %lf\n", result1);


    int num3[] = {1, 2};
    int num3Size = 2;

    int num4[] = {3,4};
    int num4Size = 2;

    double result2;

    result2 = findMedianSortedArrays(num3, num3Size, num4, num4Size);

    printf("The result2 is: %lf\n", result2);




}