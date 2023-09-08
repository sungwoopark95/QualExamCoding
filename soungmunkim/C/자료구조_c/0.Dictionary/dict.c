/*
[간단한 연결 리스트 기반의 사전(Dictionary)을 구현한 코드]

------------------- 해당 dict 사용하는 예제 ---------------------
#include "dict.h"
#include <stdio.h>

// 조건 함수: 값이 10 이상인 항목을 찾기 위한 함수
int greaterThanTen(int value) {
    return value >= 10;
}

int main() {
    // 새로운 빈 사전 생성
    Dictionary* dictionary = createDicionary();

    // 사전에 데이터 추가
    put(dictionary, createItem("one", 1));
    put(dictionary, createItem("ten", 10));
    put(dictionary, createItem("twenty", 20));

    // 키가 "one"인 항목의 값을 출력
    Item* one = get(dictionary, "one");
    if (one) {
        printf("Key: %s, Value: %d\n", one->key, one->value);
    }

    // 사전에 "twenty"라는 키가 있는지 확인
    if (exist(dictionary, "twenty")) {
        printf("'twenty' exists in the dictionary!\n");
    }

    // 값이 10 이상인 항목의 개수를 출력
    int cnt = count(dictionary, greaterThanTen);
    printf("Number of items with values greater than or equal to 10: %d\n", cnt);

    return 0;
}
*/


#include "dict.h"
#include <stdlib.h>
#include <string.h>

// 사전에서 주어진 키에 대한 항목(Item)을 검색하여 반환합니다.
Item* get(Dictionary *dictionary, unsigned char* key) {
    Item* temp = dictionary->head;
    for (; temp != NULL; temp = temp->next) {
        if (strcmp(temp->key, key) == 0) {
            return temp;
        }
    }
    return NULL;
}

// 사전에 주어진 키가 존재하는지 확인합니다.
int exist(Dictionary *dictionary, unsigned char* key)
{
    Item* temp = dictionary->head;
    while (temp != NULL)
    {
        if (strcmp(temp->key, key) == 0) {
            return TRUE;
        }
        temp = temp->next;
    }
    return FALSE;
}

// 사전의 마지막에 항목을 추가합니다.
void addTail(Dictionary *dictionary, Item* item)
{
    dictionary->tail->next = item;
    dictionary->tail = item;
}

// 사전에 항목을 추가하거나, 이미 존재하는 키가 있으면 값을 갱신합니다.
void put(Dictionary *dictionary, Item* item) {
    if (dictionary->head == NULL) {
        dictionary->head = item;
        dictionary->tail = item;
    }
    else
    {
        Item* existedItem = get(dictionary, item->key);
        if (existedItem) {
            existedItem->value = item->value;
            strcpy(existedItem->key, item->key);
            free(item);
            return;
        }
        addTail(dictionary, item);
    }
}

// 새로운 항목을 생성하여 반환합니다.
Item* createItem(unsigned char* key, int value) {
    Item* newNode = malloc(sizeof(Item));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;

    return newNode;
}

// 새로운 빈 사전을 생성하여 반환합니다.
Dictionary* createDicionary() {
    Dictionary* dictionary = malloc(sizeof(Dictionary));
    dictionary->head = NULL;
    dictionary->tail = NULL;

    return dictionary;
}

// 주어진 조건 함수(method)에 따라 사전 내 항목의 수를 계산합니다.
int count(Dictionary *dictionary, int(*method)(int)) {
    Item* temp = dictionary->head;
    int i = 0;
    for (; temp != NULL; temp = temp->next) {
        if (method(temp->value))
        {
            i++;
        }
    }
    return i;
}
