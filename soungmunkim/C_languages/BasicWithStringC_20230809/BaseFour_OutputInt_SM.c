/*
임의의 자연수를 argument로 입력 받아 4진수로 변환하고, 변환된 4진수를 Return하는 base_four 함수를 작성하여라.

TestCase1)
>>> ./P3 10 
22

TestCase2)
>>> ./P3 4 
10
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverseString(char* str);
int strToint(char* str);

int main(int argc, char* argv[]){
    int m;
    int remainder;
    int size = 2;
    char* bit = (char*) malloc(size * sizeof(char));
    int idx = 0;

    if (argc > 1) {
        int n = atoi(argv[1]);
        m = n;
        while (m >= 4) {
            if (idx == size - 1) {
                size *= 2;
                bit = realloc(bit, size);
            }
            remainder = m % 4;
            bit[idx] = '0' + remainder; // ASCII 문자로 변환
            m /= 4;
            idx++;
        }
        bit[idx] = '0' + m; // 마지막 수 처리
        bit[idx + 1] = '\0'; // 문자열 종료
    }

    reverseString(bit);
    int num = strToint(bit);
    printf("%d\n", num);

    free(bit);
    return 0;
}

void reverseString(char* str) {
    int length = strlen(str);
    for (int i = 0; i < length/2; i++){
        char temp = str[i];
        str[i] = str[length - 1 - i];
        str[length - 1 - i] = temp;
    }
}

int strToint(char* str) {
    /*
    자세히 설명하자면, 문자열 "1234"에는 실제로 문자 '1', '2', '3', '4'가 들어있습니다. 각 문자는 ASCII 코드 값에 해당하는 정수로 표현될 수 있습니다. 예를 들면, ASCII에서 '0'은 48에 해당합니다. 따라서, '1'은 49, '2'는 50이 됩니다.

    그렇기 때문에 '1' - '0' 연산을 수행하면, 49(ASCII '1'의 값) - 48(ASCII '0'의 값) = 1의 결과가 나옵니다. 이런 원리로 각 문자를 해당하는 10진수 정수로 변환합니다.

    strToBase4 함수의 동작 원리를 살펴보면:

    문자열 "1234"를 순회하면서 각 문자를 순차적으로 방문합니다.
    base4 변수는 초기에 0으로 설정되어 있습니다.
    첫 번째 순회에서 '1'을 처리할 때, base4 = 0 * 10 + (49 - 48) = 1로 설정됩니다.
    두 번째 순회에서 '2'를 처리할 때, base4 = 1 * 10 + (50 - 48) = 12로 설정됩니다.
    세 번째와 네 번째 순회도 마찬가지 방식으로 동작하므로, 함수의 마지막에 base4 값은 1234가 됩니다.
    */
   
    int num = 0;
    for (int i = 0; i < strlen(str); i++) {
        num = num * 10 + (str[i] - '0');
    }
    return num;
}

