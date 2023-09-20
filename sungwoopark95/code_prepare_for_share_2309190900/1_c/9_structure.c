#include <stdio.h>


struct studentType{
    char name[10];
    int midterm;
    int final;
    int total;
};


typedef struct studentType Student;

int main(void){
    struct studentType studentA = {
        .name="Yongsang"
    };
    // studentA.name="Yongsang";
    studentA.midterm=10;
    studentA.final=10;
    studentA.total=studentA.midterm+studentA.final;
    printf("Student name: %s.\n", studentA.name);
    printf("Total score : %d.\n", studentA.total);


    Student studentB={
        .name="Jungeun"
    };
    studentB.midterm=10;
    studentB.final=10;
    studentB.total=studentB.midterm+studentB.final;
    printf("Student name: %s.\n", studentB.name);
    printf("Total score : %d.\n", studentB.total);
    
}