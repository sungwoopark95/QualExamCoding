// #include <stdio.h>
// #include <string.h>
// #include <stdbool.h>
// #define MAX_VAR_LEN 5
// #define MAX_VAR_NUM 40
// #define MAX_EQ_NUM 20

// struct Dictionary {
//     char keys[MAX_VAR_NUM][MAX_VAR_LEN];
//     int indices[MAX_VAR_NUM][MAX_EQ_NUM];
//     int num_keys;
//     int num_idx[MAX_VAR_NUM];
// };

// int main() {
//     struct Dictionary dd;

//     dd.num_keys = 5; // Setting the value of num_keys to 5
//     printf("%d\n",dd.num_keys);

//     return 0;
// }


// #include <stdio.h>
// #include <string.h>

// int main() {
//     char sourceArray[] = "Hello, World!";
//     char destinationArray[8]; // Array to copy the data into

//     int startIndex = 7; // Index of the first character to copy
//     int numCharacters = 5; // Number of characters to copy

//     memcpy(destinationArray, sourceArray + startIndex, numCharacters);

//     // Null-terminate the destination array to treat it as a string
//     destinationArray[numCharacters] = '\0';

//     printf("Copied string: %s\n", destinationArray);

//     return 0;
// }


#include <stdio.h>
#include <math.h>

int main() {
    long long a = 10;
    int b = 3;
    double result = ceil((double)a / b);
    int int_result = (int)result;
    printf("Result: %d\n", int_result);
    return 0;
}