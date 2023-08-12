/*
사용자로부터 영어 알파벳 대/소문자 10개를 입력 받은 후 이를 사전 기준 역순으로 출력하는 함수를 작성하여라. 
단, 동일 알파벳의 대/소문자가 같이 있는 경우 대문자가 앞에 출력되도록 한다. 

- 역순으로 정렬 시 Insertion Sort 알고리즘을 변형하여 사용하여라. 
- 동일 알파벳이 중복해서 입력으로 주어지지는 않는다고 가정한다. 단, 대/소문자로 구분되는 경우는 제외한다. 
예를 들어 A a 는 주어질 수 있지만 A A 또는 a a 는 주어지지 않는다. 
*/

#include <stdio.h>
#include <stdlib.h>

char case_convert(char c);

int main(int argc, char* argv[]) {
    int length = 0;
    int i = 1;
    while (argv[i]) {
        length++;
        i++;
    }

    char str[length];
    int is_upper[length];

    for (int j=0;j<length;j++) {
        char c = argv[j+1][0];
        if (c >= 'A' && c <= 'Z') { 
            str[j] = case_convert(c);
            is_upper[j] = 1; 
        }
        else { 
            str[j] = c;
            is_upper[j] = 0; 
        }
    }

    // insertion sort
    for (int i=1;i<length;i++) {
        for (int j=i;j>0;j--) {
            if (str[j-1] < str[j]) {
                // swap chars
                char temp;
                temp = str[j-1];
                str[j-1] = str[j];
                str[j] = temp;

                // swap the indicators
                int idx_temp;
                idx_temp = is_upper[j-1];
                is_upper[j-1] = is_upper[j];
                is_upper[j] = idx_temp; 
            }
        }
    }

    // print the result
    for (int i=0;i<length;i++) {
        if (is_upper[i]) {
            printf("%c", case_convert(str[i]));
        } else {
            printf("%c", str[i]);
        }
    }

    printf("\n");
    return 0;
}

char case_convert(char c) {
    int upper_start = 'A';
    int upper_end = 'Z';
    int lower_start = 'a';
    int lower_end = 'z';
    char converted;

    if (c >= upper_start && c <= upper_end) {
        // if c is an upper case, convert it to the corresponding lower case
        converted = lower_start + (c - upper_start);
    } else if (c >= lower_start && c <= lower_end) {
        // if c is a lower case, convert it to the corresponding upper case
        converted = upper_start + (c - lower_start);
    }
    return converted;
}
