/*"SET" for visited nodes*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100000

typedef struct {
    int data[MAX_SIZE];
    int size;
} Set;

void init(Set *set) {
    set->size = 0;
}

bool contains(Set *set, int value) {
    for (int i = 0; i < set->size; i++) {
        if (set->data[i] == value) {
            return true;
        }
    }
    return false;
}

void add(Set *set, int value) {
    if (!contains(set, value)) {
        set->data[set->size++] = value;
    }
}

void remove(Set *set, int value) {
    for (int i = 0; i < set->size; i++) {
        if (set->data[i] == value) {
            set->data[i] = set->data[--set->size]; //0~5 idx를 사용하고 있을 때 idx=2인걸 지우면 idx=5 인 element를 -> idx=2로 넣어야 함
            break;
        }
    }
}

void print(Set *set) {
    printf("{");
    for (int i = 0; i < set->size; i++) {
        printf("%d", set->data[i]);
        if (i < set->size - 1) {
            printf(", ");
        }
    }
    printf("}\n");
}



/*"dictionary"*/

typedef struct {
    int keys[MAX_SIZE];
    int values[MAX_SIZE];
    int size;
} Dictionary;

void init(Dictionary *dict) {
    dict->size = 0;
}

int get(Dictionary *dict, int key) {
    for (int i = 0; i < dict->size; i++) {
        if (dict->keys[i] == key) {
            return dict->values[i];
        }
    }
    return -1;
}

int get_idx(Dictionary *dict, int key) {
    for (int i = 0; i < dict->size; i++) {
        if (dict->keys[i] == key) {
            return i;
        }
    }
    return -1;
}

void put(Dictionary *dict, int key, int value) {
    for (int i = 0; i < dict->size; i++) {
        if (dict->keys[i] == key) {
            dict->values[i] = value;
            return;
        }
    }
    dict->keys[dict->size] = key;
    dict->values[dict->size] = value;
    dict->size++;
}



void put_idx(Dictionary *dict, int idx, int value) {
    if ((idx<dict->size) && (idx>=0)){
        dict->values[idx]=value;
        return;
    }
    return;
}

void remove_key(Dictionary *dict, int key) {
    for (int i = 0; i < dict->size; i++) {
        if (dict->keys[i] == key) {
            dict->keys[i] = dict->keys[--dict->size];
            dict->values[i] = dict->values[dict->size];
            break;
        }
    }
}

void print(Dictionary *dict) {
    printf("{");
    for (int i = 0; i < dict->size; i++) {
        printf("%d: %d", dict->keys[i], dict->values[i]);
        if (i < dict->size - 1) {
            printf(", ");
        }
    }
    printf("}\n");
}