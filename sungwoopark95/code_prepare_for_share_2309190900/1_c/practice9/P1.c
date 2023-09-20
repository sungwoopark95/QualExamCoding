#include <stdio.h>
#include <stdlib.h>
// #include <string.h> // strlen
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
  
  int idx=0;
  // char* res=(char*)malloc(sizeof(char)*strlen(s)); // CHECK : what if we can't use strlen?
  char* res=(char*)malloc(sizeof(char)*MAX_LEN);
  char curr_char;
  while (s[idx]!='\0') {
    curr_char=s[idx];
    if ((curr_char>=65)&&(curr_char<=90)){
      res[idx]=curr_char+32;
    }
    else if ((curr_char>=97)&&(curr_char<=122)){
      res[idx]=curr_char-32;
    }
    else {
      fprintf(stderr, "Entered string is not english.\n");
      exit(EXIT_FAILURE);
    }
    idx++;
  }
  res[idx]='\0';
  return res;
  
}