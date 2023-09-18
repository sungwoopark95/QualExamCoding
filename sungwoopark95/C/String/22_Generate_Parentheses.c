#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/* ======================= StringVector 선언 + 필요 함수 ======================= */
typedef struct {
    char** data;
    int size;
    int capacity;
} StringVector;

void initStringVector(StringVector* vec) {
    vec->data = malloc(10 * sizeof(char*));
    vec->size = 0;
    vec->capacity = 10;
}

void push_back(StringVector* vec, const char* s) {
    if (vec->size == vec->capacity) {
        vec->capacity *= 2;
        vec->data = realloc(vec->data, vec->capacity * sizeof(char*));
    }
    vec->data[vec->size++] = strdup(s);
}

bool contains(StringVector* vec, const char* s) {
    for (int i = 0; i < vec->size; i++) {
        if (strcmp(vec->data[i], s) == 0) {
            return true;
        }
    }
    return false;
}
/* ========================================================================== */

/* ========================= isValid + permutation ========================== */
bool isValid(const char* s) {
    if (strlen(s) % 2 == 1) {
        return false;
    }
    
    char stack[strlen(s)];
    int stackIndex = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
            stack[stackIndex++] = s[i];
        } else {
            if (stackIndex == 0 || 
                (s[i] == ')' && stack[stackIndex-1] != '(') ||
                (s[i] == '}' && stack[stackIndex-1] != '{') ||
                (s[i] == ']' && stack[stackIndex-1] != '[')) {
                return false;
            }
            stackIndex--;
        }
    }
    return stackIndex == 0;
}

void backtrack(char* s, int start, StringVector* permutation_lst) {
    if (start == strlen(s)) {
        if (!contains(permutation_lst, s)) {
            push_back(permutation_lst, s);
        }
        return;
    }
    for (int i = start; i < strlen(s); i++) {
        char temp = s[start];
        s[start] = s[i];
        s[i] = temp;

        backtrack(s, start + 1, permutation_lst);

        temp = s[start];
        s[start] = s[i];
        s[i] = temp;
    }
}

StringVector str_perm(char* s) {
    StringVector permutation_lst;
    initStringVector(&permutation_lst);
    backtrack(s, 0, &permutation_lst);
    return permutation_lst;
}

StringVector generateParenthesis(int n) {
    int len = 2 * n;
    char* candidate = malloc(len + 1); // +1 for null terminator
    for (int i = 0; i < n; i++) {
        candidate[i] = '(';
        candidate[n + i] = ')';
    }
    candidate[len] = '\0';

    StringVector perms = str_perm(candidate);
    free(candidate); // Don't forget to free memory once done

    StringVector ans;
    initStringVector(&ans);

    for (int i = 0; i < perms.size; i++) {
        if (isValid(perms.data[i])) {
            push_back(&ans, perms.data[i]);
        }
        free(perms.data[i]); // Freeing each string in perms
    }
    free(perms.data); // Freeing perms data array

    return ans;
}
/* ========================================================================== */

/* ================================ chatGPT ================================= */
// # generate 함수는 재귀적으로 괄호의 조합을 생성합니다.
// # p: 현재까지 만들어진 괄호의 조합 문자열
// # left: 사용할 수 있는 남은 여는 괄호의 수
// # right: 사용할 수 있는 남은 닫는 괄호의 수
// # parens: 지금까지 만들어진 모든 괄호의 조합 리스트
void generate(char* p, int left, int right, StringVector* parens) {
    // # 만약 남은 여는 괄호가 있다면, 현재의 조합 문자열에 여는 괄호를 추가합니다.
    // # 그리고 남은 여는 괄호의 수를 하나 줄입니다.
    if (left) {
        char* newStr = malloc(strlen(p) + 2); // +1 for '(' and +1 for null terminator
        strcpy(newStr, p);
        strcat(newStr, "(");
        generate(newStr, left - 1, right, parens);
        free(newStr);
    }
    // # 닫는 괄호의 남은 수가 여는 괄호의 남은 수보다 많다면,
    // # 현재의 조합 문자열에 닫는 괄호를 추가합니다.
    // # 그리고 남은 닫는 괄호의 수를 하나 줄입니다.
    if (right > left) {
        char* newStr = malloc(strlen(p) + 2); // +1 for ')' and +1 for null terminator
        strcpy(newStr, p);
        strcat(newStr, ")");
        generate(newStr, left, right - 1, parens);
        free(newStr);
    }
    // # 더 이상 사용할 닫는 괄호가 없다면, 현재 괄호 조합을 결과 목록에 추가합니다.
    // # 이는 올바른 괄호 조합이 완성된 경우입니다.
    if (!right) {
        push_back(parens, p);
    }
}

StringVector generateParenthesis(int n) {
    // # generate 함수를 호출하여 올바른 괄호의 조합을 생성하고 반환합니다.
    // # 처음에는 아무런 괄호도 없는 상태로 시작하며, n개의 여는 괄호와 n개의 닫는 괄호를 사용할 수 있습니다.
    StringVector parens;
    initStringVector(&parens);
    generate("", n, n, &parens);
    return parens;
}
/* ========================================================================== */

int main() {
    int n = 3;
    StringVector result = generateParenthesis(n);
    for (int i = 0; i < result.size; i++) {
        printf("%s\n", result.data[i]);
        free(result.data[i]);
    }
    free(result.data);
    return 0;
}
