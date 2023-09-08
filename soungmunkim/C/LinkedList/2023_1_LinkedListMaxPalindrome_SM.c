/*
[Linked list로 max palindrome 찾기]
|!!! Linked list를 list로 변환해서 푼 것 !!!

Suppose we represent a sequence of integers from 0 to 9 with a list, and it is implemented with a linked list. 
For example, an integer list [3, 7, 6, 8] is implemented with a linked list:

A list of integers is a palindrome if it is identical to its reversion. 
Given a list s of integers, you will finally implement a function max_palindromes(s) 
    that prints a list of sub-lists of s that are maximal palindromes. 
    
That is, t is a list that contains palindrome sub-lists of s that are not a sub-list of another palindrome sub-list of s. 

For example, when s is [8,1,2,3,3,2,1,4,9,5,4,5,6,7,6,5,4,1], 
    **max-palindromes(s)** prints:
    [[8], [1,2,3,3,2,1], [4,9,4], [4,5,6,7,6,5,4]].

When s is [8,1,2,3,3,2,1,0,4,9,1,2,3,3,2,1,9,1], 
    max_palindromes(s) prints:
    [[8], [0], [4], [9,1,2,3,3,2,1,9], [1,9,1]].

Assume that the length of s is at most 32.


(a) Write a function **print_list(s)** that prints the sequence (i.e., the linked list) s in the list format. 
    For example, linked list in Figure 3 should be printed as [3,7,6,8].

(b) Write a function **palindrome(s)** that returns 1 if the list s is a palindrome. O
    therwise, it returns 0.

(c) Write a function **sub_list(s, t)** that returns 1 if the list t is a sub-list of the list s. 
    Otherwise, it returns 0. 

(d) Write the function **max_palindromes(s)** that uses palindrome(s), sub_list(s, t), and print_list(s).

In **print_list** and **max_palindromes**, the printed string should only contain square brackets ([ and ]), commas, digits (0 9), 
    and spaces between them. We accept any formats and orders that describe the answer. 
    For example, “[ [1, 2, 1], [3]]” and “[[3], [1,2,1]]” are both OK if the answer is [[1,2,1],[3]].
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// 노드 구조체 정의
typedef struct Node {
    int data;           // char 대신 int로 변경
    struct Node* next;
} Node;

// 새 노드 생성 함수
Node* newNode(int data) {   // char 대신 int를 인자로 받도록 변경
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}
// (a) 연결 리스트를 순회하며 노드의 데이터를 출력하는 함수
// (a) linked list를 리스트 형식으로 출력
void print_list(Node* s) {
    while (s != NULL) {
        printf("%d ", s->data);  // %c 대신 %d로 변경
        s = s->next;
    }
    printf("\n");
}

// (b) 문자열이 회문인지 판단하는 함수
bool palindrome(char* s, int len) {
    for (int i = 0; i < len / 2; i++) {
        if (s[i] != s[len - i - 1])
            return false;   // 회문이 아니면 false 반환
    }
    return true;    // 회문이면 true 반환
}

// (c) t 문자열이 s 문자열의 부분 문자열인지 판단하는 함수
bool substring(char* s, char* t) {
    return strstr(s, t) != NULL;  // t가 s에 포함되면 true 반환
}

// (d) 연결 리스트에서 가능한 최대 회문들을 찾아 출력하는 함수
void max_palindromes(Node* s) {
    char str[100];
    int index = 0;

    // 연결 리스트를 문자열로 변환
    while (s) {
        str[index++] = s->data;
        s = s->next;
    }
    str[index] = '\0';

    char* max_pals[100];
    int count = 0;

    // 모든 부분 문자열에 대해 회문 여부 체크
    for (int i = 0; i < index; ++i) {
        for (int j = i; j < index; ++j) {
            int len = j - i + 1;
            char sub[100];
            strncpy(sub, str + i, len);
            sub[len] = '\0';

            // 부분 문자열이 회문일 경우
            if (palindrome(sub, len)) {
                bool is_maximal = true;
                for (int k = 0; k < count; k++) {
                    // 이미 발견된 최대 회문의 부분 문자열인지 체크
                    if (substring(max_pals[k], sub) && strcmp(max_pals[k], sub) != 0) {
                        is_maximal = false;
                        break;
                    }
                }
                // 최대 회문이면 배열에 추가
                if (is_maximal) {
                    max_pals[count] = (char*)malloc(len + 1);
                    strcpy(max_pals[count++], sub);
                }
            }
        }
    }

    // 중복되는 회문 제거
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (substring(max_pals[j], max_pals[i]) && strcmp(max_pals[j], max_pals[i]) != 0) {
                free(max_pals[i]);
                max_pals[i] = max_pals[--count];
                break;
            }
        }
    }

    // 최대 회문 출력
    for (int i = 0; i < count; i++) {
        printf("%s ", max_pals[i]);
    }
    printf("\n");

    // 동적 할당된 메모리 해제
    for (int i = 0; i < count; i++) {
        free(max_pals[i]);
    }
}

int main() {
    char input[1000];  // 사용자 입력을 받기 위한 문자열
    int data;

    printf("Enter the elements in list format (e.g., 1 2 3 4 5): ");
    fgets(input, sizeof(input), stdin);  // 한 줄로 입력받기

    Node* head = NULL;
    Node* temp = NULL;

    char* token = strtok(input, " ");  // 공백을 기준으로 문자열 분리
    while (token) {
        sscanf(token, "%d", &data);  // 분리된 문자열에서 숫자 읽기

        if (head == NULL) {
            head = newNode(data);
            temp = head;
        } else {
            temp->next = newNode(data);
            temp = temp->next;
        }

        token = strtok(NULL, " ");  // 다음 토큰 가져오기
    }

    print_list(head);
    max_palindromes(head);

    // 메모리 해제
    while (head) {
        Node* t = head;
        head = head->next;
        free(t);
    }

    return 0;
}