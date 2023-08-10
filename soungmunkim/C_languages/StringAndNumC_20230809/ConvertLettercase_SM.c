/*
사용자로부터 10자 이내의 영어 알파벳으로 구성된 string을 입력 받아 대문자는 소문자로, 
소문자는 대문자로 바꾼 후 출력하는 함수

TestCase1)
./P2 ABCdef 
abcDEF
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 10

char *SwitchCase(char *s);
int main(int argc, char* argv[]) {
  char *str; //List of characters to be sorted

  str = argv[1];
  printf("%s", SwitchCase(str));

  return 0;
}
/* Do not modify above */

char *SwitchCase(char *s) {
  /* Write your code below */
  int code;
  for(int i=0; i < strlen(s); i++){
    // lowercase일때
    if((int)s[i] >= 97)
        code = (int)s[i] - 32;
    
    // uppercase일때
    else if ((int)s[i] <= 90)
        code = (int)s[i] + 32;
    s[i] = (char)code;
  }
  return s;
}