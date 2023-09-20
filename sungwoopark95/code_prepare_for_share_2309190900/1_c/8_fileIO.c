#include <stdio.h>

int main(void){
    FILE *filePtr;
    filePtr = fopen("example.txt", "r");
    if (filePtr==NULL) {
        printf("fopen error!\n");
    }
    char contents[100];
    while (fscanf(filePtr, "%s", contents)!=EOF){
        printf("%s", contents);
    }


    // fscanf(filePtr, "%s", &contents);
    // printf("%s", contents);
}