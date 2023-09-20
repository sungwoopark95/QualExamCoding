#include <stdio.h>
#include <string.h>

int main() {
    char str[15] = "Hello, World!";
    printf("Original String: %s\n", str);

    // Using memset to fill the string with 'A' characters
    memset(str, 'A', 10);

    printf("After memset: %s\n", str);

    return 0;
}