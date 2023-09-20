#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 10

char *SwitchCase(char *s);
int main(int argc, char* argv[]) {
  char *str; //List of characters to be sorted

  str = argv[1];
  printf("%s\n", SwitchCase(str));

  return 0;
}
/* Do not modify above */

char *SwitchCase(char *s) {
  int diff = 'a' - 'A';
  int i = 0;
  while (s[i] != '\0') {
    if (s[i] <= 90) {
      s[i] += diff;
    }
    else {
      s[i] -= diff;
    }
    i += 1;
  }
  return s;
}