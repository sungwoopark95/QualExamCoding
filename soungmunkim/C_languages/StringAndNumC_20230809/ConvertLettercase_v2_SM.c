/*
사용자로부터 10자 이내의 영어 알파벳으로 구성된 string을 입력 받아 대문자는 소문자로, 
소문자는 대문자로 바꾼 후 출력하는 함수

TestCase1)
./P2 ABCdef 
abcDEF
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 10

char *SwitchCase(char *s);
int main(int argc, char* argv[]) {
  char *str; //List of characters to be sorted

  str = argv[1];
  printf("%s", SwitchCase(str));

  return 0;
}
/* Do not modify above */
/* Write your code below */
char *SwitchCase(char *s) {
  int diff = 'a' - 'A';
  int i = 0;
  do {
    if (s[i] <= 90) {
      s[i] += diff;
    }
    else {
      s[i] -= diff;
    }
    i += 1;
  } while(s[i] != '\0');
  return s;
}