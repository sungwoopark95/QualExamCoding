#include <stdio.h>
#include <stdlib.h>

// 스택의 정의
typedef struct {
    int* p_list;
    int size;
    int MAX_SIZE;
} Stack;

// 스택 생성 함수
Stack createStack(int MAX_SIZE) {
    Stack s;
    s.size = 0;
    s.MAX_SIZE = MAX_SIZE;
    s.p_list = (int*)malloc(MAX_SIZE * sizeof(int));
    return s;
}

// 스택 메모리 해제 함수
void freeStack(Stack* s) {
    free(s->p_list);
}

// 항목의 인덱스 찾는 함수
int find_index(Stack* s, int item) {
    for (int i = 0; i < s->size; i++) {
        if (s->p_list[i] == item) {
            return i;
        }
    }
    return -1;
}

// 스택에 항목 추가 함수
void push(Stack* s, int item) {
    if (s->size == s->MAX_SIZE) {
        printf("Stack Overflow.\n");
        exit(1);
    }
    s->p_list[s->size++] = item;
}

// 스택에서 항목 제거 함수
int pop(Stack* s) {
    if (s->size == 0) {
        printf("Error: No item exists in the list\n");
        exit(1);
    }
    return s->p_list[--s->size];
}

// 스택 항목 출력 함수
void print(Stack* s) {
    for (int i = 0; i < s->size; i++) {
        if (i != 0) {
            printf(", ");
        }
        printf("%d", s->p_list[i]);
    }
    printf("\n");
}

// 스택 병합 함수 (중복 항목 제거)
void merge(Stack* s1, Stack* s2) {
    for (int i = 0; i < s2->size; i++) {
        int item = s2->p_list[i];
        if (find_index(s1, item) == -1) {
            push(s1, item);
        }
    }
}

/*------------------- temp로 따로 object 할당해서 진행한 것 ----------------*/
// 주어진 스택에 다른 스택의 항목들을 추가하는 함수
// Stack* mergeStacks(Stack* stack1, Stack* stack2) {
//     Stack* temp = (Stack*)malloc(sizeof(Stack));
//     initStack(temp);

//     // stack1의 항목들을 temp에 복사
//     for (int i = 0; i < stack1->size; i++) {
//         push(temp, stack1->p_list[i]);
//     }

//     // stack2의 항목들을 temp에 추가 (중복되지 않는 경우만)
//     for (int j = 0; j < stack2->size; j++) {
//         if (find_index(stack1, stack2->p_list[j]) == -1) {
//             push(temp, stack2->p_list[j]);
//         }
//     }

//     return temp;
// }

// 두 스택 비교 함수
int areEqual(Stack* s1, Stack* s2) {
    if (s1->size != s2->size) {
        return 0; // false
    }
    for (int i = 0; i < s1->size; i++) {
        if (s1->p_list[i] != s2->p_list[i]) {
            return 0; // false
        }
    }
    return 1; // true
}

int main() {
    Stack s1 = createStack(100);
    Stack s2 = createStack(100);

    push(&s1, 1);
    push(&s1, 2);
    push(&s1, 3);

    push(&s2, 1);
    push(&s2, 2);
    push(&s2, 5);

    print(&s1); // 출력: 1, 2, 3
    print(&s2); // 출력: 1, 2, 5

    merge(&s1, &s2);
    print(&s1); // 출력: 1, 2, 3, 5
    print(&s2); // 출력: 1, 2, 5

    printf("s1 == s2 ? %d\n", areEqual(&s1, &s2)); // 출력: s1 == s2 ? 0

    printf("%d\n", pop(&s1)); // 출력: 5
    printf("%d\n", pop(&s1)); // 출력: 3
    printf("%d\n", pop(&s2)); // 출력: 5
    printf("s1 == s2 ? %d\n", areEqual(&s1, &s2)); // 출력: s1 == s2 ? 1

    printf("%d\n", pop(&s2)); // 출력: 2
    printf("%d\n", pop(&s2)); // 출력: 1

    freeStack(&s1);
    freeStack(&s2);

    return 0;
}
