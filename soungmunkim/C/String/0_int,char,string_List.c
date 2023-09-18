#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


int main() {
    // 사용 예제
    // INT 타입의 DynamicArray 예제
    DynamicArray* intArray = createArray(INT, 5);
    int intVal1 = 1, intVal2 = 2, intVal3 = 3;
    append(intArray, &intVal1);
    append(intArray, &intVal2);
    append(intArray, &intVal3);
    printArray(intArray);  // 출력: [1, 2, 3]

    DynamicArray* floatArray = createArray(FLOAT, 5);
    float f1 = 1.1, f2 = 2.2, f3 = 3.3;
    append(floatArray, &f1);
    append(floatArray, &f2);
    append(floatArray, &f3);
    printArray(floatArray);  // 출력: [1.10, 2.20, 3.30]

    DynamicArray* charArray = createArray(CHAR, 5);
    char charVal1 = 'A', charVal2 = 'B', charVal3 = 'C';
    append(charArray, &charVal1);
    append(charArray, &charVal2);
    append(charArray, &charVal3);
    printArray(charArray);  // 출력: [A, B, C]

    DynamicArray* stringArray = createArray(STRING, 5);
    append(stringArray, "Hello");
    append(stringArray, "World");
    printArray(stringArray);  // 출력: ["Hello", "World"]

    freeArray(intArray);
    freeArray(floatArray);
    freeArray(charArray);
    freeArray(stringArray);

    int arr[] = {1, 3, 4, 5};
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    // INT 타입의 DynamicArray 생성
    DynamicArray* intArray = createArray(INT, arrSize);

    // arr의 각 요소를 intArray에 복사 (int array 할당 방법)
    for (int i = 0; i < arrSize; i++) {
        int* value = malloc(sizeof(int));
        *value = arr[i];
        append(intArray, value);
    }

    printArray(intArray);  // 출력: [1, 3, 4, 5]

    // 메모리 해제
    for (int i = 0; i < intArray->size; i++) {
        free(intArray->data.iArray[i]);
    }
    freeArray(intArray);
    return 0;
}
